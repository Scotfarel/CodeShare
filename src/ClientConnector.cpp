#include "headers/ClientConnector.h"
#include <qtextcodec.h>
#include <QMessageBox>
#include <QtWidgets/QApplication>
#include <utility>
typedef std::deque<Message> message_queue;
ClientConnector::ClientConnector(QString nickname)
        : work_(new boost::asio::io_context::work(io_context_)),
          resolver_(io_context_),
          socket_(io_context_),
          username_(std::move(nickname)),
          fullBody(""),
          crdt(),
          room_id_() {
    worker_ = std::thread([&](){io_context_.run();});
    do_connect();
}
void ClientConnector::room_choice() {
   int choice,id;
    std::cout<<"Enter 1 to create room or enter  2  to join existing room:"<<std::endl;
    std::cin>>choice;
    switch (choice) {
        case 1: {
            this->create_room();
            break;
        }
        case 2: {
            std::cout << "Enter room id to join existing room:" << std::endl;
            std::cin >> id;
            this->join_room(id);
            break;
        }
    }
}
void ClientConnector::create_room(){
    //Serialize data
    json j;
    jsonTypes::to_json(j, "CREATE_ROOM_REQUEST");
    const std::string req = j.dump();
    //Send data (header and body)
    this->send_req_msg(req);
}
void ClientConnector::join_room(int id){
    //Serialize data
    json j;
    jsonTypes::to_json_join_room(j, "JOIN_ROOM_REQUEST", id);
    const std::string req = j.dump();
    //Send data (header and body)
    this->send_req_msg(req);
}
ClientConnector::~ClientConnector() {
    work_.reset();
    this->close();
    worker_.join();
}
int ClientConnector::get_room() const {
    return room_id_;
}
void ClientConnector::do_connect() {
    auto endpoints = resolver_.resolve("127.0.0.1", "63506");
    room_choice();
    boost::asio::async_connect(socket_, endpoints,
                               [this](boost::system::error_code ec, const tcp::endpoint&) {
       if (!ec) {
           status = true;
           emit statusChanged(status);
           do_read_header();
       } else {
           qDebug() << ec.message().c_str();
           status = false;
           emit statusChanged(status);
       }
     });
}

void ClientConnector::do_read_header() {
    memset(read_msg_.data(), 0, read_msg_.length() + 1);  // VERY IMPORTANT, otherwise rubbish remains inside socket!
    boost::asio::async_read(socket_,
                            boost::asio::buffer(read_msg_.data(), Message::header_length + 1),
                            [this](boost::system::error_code ec, std::size_t) {
        if (!ec) {
            read_msg_.decode_header();
            do_read_body();
        } else {
            qDebug() << ec.message().c_str() << endl;
            close_connection();
        }
    });
}

void ClientConnector::do_read_body() {
    boost::asio::async_read(socket_,
                            boost::asio::buffer(read_msg_.body()+1, read_msg_.body_length()),
                            [this](boost::system::error_code ec, std::size_t /*length*/) {
        if (!ec) {
            read_msg_.data()[read_msg_.length()+1] = '\0';
            fullBody.append(read_msg_.body()+1);

            if (read_msg_.is_last_chunk() == '0') {
                do_read_header();
                return;
            }
            std::string operation_JSON;
            try {
                json jdata_in = json::parse(fullBody);
                jsonTypes::from_json(jdata_in, operation_JSON);

                 if (operation_JSON == "DISCONNECT_RESPONSE") {
                    std::string response_JSON;
                    jsonTypes::from_json_resp(jdata_in, response_JSON);

                    if (response_JSON == "LOGOUT_OK") {
                        emit opResultSuccess("DISCONNECT_SUCCESS");
                    } else {
                        emit opResultFailure("DISCONNECT_FAILURE");
                    }
                } else if (operation_JSON == "INSERTION_RESPONSE") {
                    Symbol symbolJSON;
                    int indexEditorJSON;
                    jsonTypes::from_json_insertion(jdata_in, symbolJSON, indexEditorJSON);
                    int newIndex = this->crdt.process(0, indexEditorJSON, symbolJSON);

                    std::pair<int, wchar_t> tuple = std::make_pair(newIndex, symbolJSON.get_letter());
                    emit insertSymbol(tuple);
                } else if (operation_JSON == "CREATE_ROOM_RESPONSE") {  // CREATE ROOM
                     std::string response_JSON;
                     jsonTypes::from_json_resp(jdata_in, response_JSON);

                     if(response_JSON == "CREATE_ROOM_OK") {
                         int room_id;
                         jsonTypes::from_jsonUri(jdata_in, room_id);  // get json value and put into JSON variables
                         // Update client data
                         this->set_room(room_id);
                         this->crdt.set_symbols(std::vector<Symbol>());
                         emit opResultSuccess("CREATE_ROOM_SUCCESS");
                     } else
                             emit opResultFailure("CREATE_ROOM_FAILURE");
                 } else if (operation_JSON == "JOIN_ROOM_RESPONSE") {  // JOIN ROOM
                     std::string responseJson;
                     int room_id;
                     jsonTypes::from_json_resp(jdata_in, responseJson);

                     if(responseJson == "JOIN_ROOM_OK") {
                         std::vector<Symbol> symbolsJSON;
                         jsonTypes::from_json_symbols(jdata_in, symbolsJSON);
                         jsonTypes::from_json_join(jdata_in, room_id);
                         this->set_room(room_id);
                         //Update client data
                         this->crdt.set_symbols(symbolsJSON);
                         emit opResultSuccess("JOIN_ROOM_SUCCESS");
                     } else if(responseJson == "JOIN_ROOM_EMPTY") {
                         jsonTypes::from_json_join(jdata_in, room_id);
                         this->set_room(room_id);
                         //Update client data
                         this->crdt.set_symbols(std::vector<Symbol>());
                         emit opResultSuccess("JOIN_ROOM_SUCCESS");
                     } else
                             emit opResultFailure("JOIN_ROOM_FAILURE");
                 } else if (operation_JSON == "INSERTIONRANGE_RESPONSE") {
                    int firstIndexJSON;
                    std::vector<json> jsonSymbols;
                    jsonTypes::from_json_insertion_range(jdata_in, firstIndexJSON, jsonSymbols);
                    std::vector<Symbol> symbols;
                    int newIndex = firstIndexJSON;
                    for (const auto& j :  jsonSymbols) {
                        Symbol *s = nullptr;  // do not remember to delete it! (keyword 'delete')
                        s = jsonTypes::from_json_symbol(j);
                        if (!s) {
                            emitMsgInCorrectWindow();  // show error
                            do_read_header();
                        }
                        symbols.push_back(*s);
                        newIndex = this->crdt.process(0, newIndex, *s);
                        std::pair<int, wchar_t> tuple = std::make_pair(newIndex, s->get_letter());
                        emit insertSymbol(tuple);
                        delete s;
                    }
                } else if (operation_JSON == "CURSOR_CHANGE_RESPONSE") {
                    std::string usernameJSON;
                    std::string colorJSON;
                    int posJSON;
                    jsonTypes::from_json_cursor_change(jdata_in, usernameJSON, colorJSON, posJSON);
                    emit changeRemoteCursor(usernameJSON, colorJSON, posJSON);
                }  else if (operation_JSON == "REMOVAL_RESPONSE") {
                    std::vector<int_pair> symbolsId;
                    jsonTypes::from_json_removal_range(jdata_in, symbolsId);

                    int newIndex;
                    for (const int_pair& id : symbolsId) {
                        // process received Symbol and retrieve new calculated index
                        newIndex = this->crdt.processErase(id);
                        if (newIndex != -1) {
                            emit eraseSymbols(newIndex, newIndex+1);
                        }
                    }
                } else {
                    qDebug() << "Something went wrong" << endl;
                    emit opResultFailure("RESPONSE_FAILURE");
                }
                fullBody = "";
                do_read_header();
            } catch (json::exception& e) {
                std::cerr << "Message: " << e.what() << '\n' << "exception id: " << e.id << std::endl;
                emitMsgInCorrectWindow();
                fullBody = "";
                do_read_header();
            }
        } else {
            qDebug() << ec.message().c_str() << endl;
            close_connection();
        }
    });
}

void ClientConnector::emitMsgInCorrectWindow() {
    emit jsonMsgFailure("NoteBook", "Cant parse json");
}

void ClientConnector::do_write() {
    boost::asio::async_write(socket_,
                             boost::asio::buffer(write_msgs_.front().data(),
                                     write_msgs_.front().length() + 1),
                             [this](boost::system::error_code ec, std::size_t /*length*/) {
         if (!ec) {
             qDebug() << "Sent:" << write_msgs_.front().data() << "END" << endl;
             write_msgs_.pop_front();
             if (!write_msgs_.empty()) {
                 do_write();
             }
         } else {
             qDebug() << ec.message().c_str() << endl;
             close_connection();
         }
     });
}

bool ClientConnector::get_status() {
    return status;
}
void ClientConnector::set_room(int room_id) {
    this->room_id_=room_id;
}
void ClientConnector::close_connection() {
    status = false;
    emit statusChanged(status);
    socket_.close();
}

void ClientConnector::write(const Message& msg) {
    boost::asio::post(io_context_, [this, msg]() {
      bool write_in_progress = !write_msgs_.empty();
      write_msgs_.push_back(msg);
      if (!write_in_progress) {
          do_write();
      }
  });
}

void ClientConnector::close() {
    boost::asio::post(io_context_, [this]() {
        close_connection();
    });
}

QString ClientConnector::get_username() {
    return this->username_;
}

void ClientConnector::send_req_msg(std::string request) {
    int mod = (request.length() % MAX_CHUNK_LENGTH == 0) ? 1 : 0;
    int numChanks = (int)((request.length() / MAX_CHUNK_LENGTH) + 1 - mod);
    int chunkSize = MAX_CHUNK_LENGTH;
    char isLastChunk = '0';
    std::string chunkResponse = request;
    for (int i = 0; i < numChanks; i++) {
        if (i == numChanks-1) {
            chunkSize = (int)(request.length() % MAX_CHUNK_LENGTH);
            isLastChunk = '1';
        }
        Message msg = Message::construct_msg(std::string(chunkResponse.begin(),
                                                         chunkResponse.begin() + chunkSize), isLastChunk);
        chunkResponse.erase(0, chunkSize);
        this->write(msg);  // deliver msg to the server
    }
}
