#include "myClient.h"
#include <qtextcodec.h>
#include <QMessageBox>
#include <QtWidgets/QApplication>

typedef std::deque<message> message_queue;

myClient::myClient()
        : work_(new boost::asio::io_context::work(io_context_)),
          resolver_(io_context_),
          socket_(io_context_),
          username_(""),
          fullBody(""),
          Crdt(),
          fileVector_(std::vector<File>())
{
    worker_= std::thread([&](){io_context_.run();}); //boost thread loop start
    do_connect();
}

myClient::~myClient() {
    work_.reset();
    this->close();
    worker_.join();
}

void myClient::do_connect() {
    auto endpoints = resolver_.resolve("127.0.0.1", "63505");
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

void myClient::do_read_header() {
    memset(read_msg_.data(), 0, read_msg_.length()+1); //VERY IMPORTANT, otherwise rubbish remains inside socket!
    boost::asio::async_read(socket_,
                            boost::asio::buffer(read_msg_.data(), message::header_length+1),
                            [this](boost::system::error_code ec, std::size_t /*length*/) {
        if (!ec) {
            read_msg_.decode_header();
            do_read_body();
        }
        else {
            qDebug() << ec.message().c_str() << endl;
            closeConnection();
        }
    });
}

void myClient::do_read_body() {
    boost::asio::async_read(socket_,
                            boost::asio::buffer(read_msg_.body()+1, read_msg_.body_length()),
                            [this](boost::system::error_code ec, std::size_t /*length*/)
    {
        if (!ec) {
            read_msg_.data()[read_msg_.length()+1] = '\0';  //VERY IMPORTANT: this removes any possible letters after data
            fullBody.append(read_msg_.body()+1);

            if(read_msg_.isThisLastChunk()=='0') {
                do_read_header();
                return;
            }
            std::string opJSON;
            try {
                json jdata_in = json::parse(fullBody);
                jsonUtility::from_json(jdata_in, opJSON);

                 if(opJSON == "DISCONNECT_RESPONSE") {
                    std::string db_responseJSON;
                    jsonUtility::from_json_resp(jdata_in, db_responseJSON);

                    if(db_responseJSON == "LOGOUT_OK")
                        emit opResultSuccess("DISCONNECT_SUCCESS");
                    else
                        emit opResultFailure("DISCONNECT_FAILURE");
                } else if(opJSON == "LOGOUTURI_RESPONSE") {
                    std::string db_responseJSON;
                    jsonUtility::from_json_resp(jdata_in, db_responseJSON);

                    if(db_responseJSON == "LOGOUTURI_OK") {
                        emit editorResultSuccess("LOGOUTURI_SUCCESS");
                    } else
                        emit editorResultFailure("LOGOUTURI_FAILURE");
                } else if(opJSON == "NEWFILE_RESPONSE") {
                    std::string db_responseJSON;
                    jsonUtility::from_json_resp(jdata_in, db_responseJSON);

                    if(db_responseJSON == "NEWFILE_OK") {
                        std::string uriJSON;
                        jsonUtility::from_jsonUri(jdata_in, uriJSON); //get json value and put into JSON variables
                        QString uriQString = QString::fromUtf8(uriJSON.data(), uriJSON.size());

                        //Update client data
                        this->setFileURI(uriQString);
                        this->Crdt.setSymbols(std::vector<symbol>());
                        emit opResultSuccess("NEWFILE_SUCCESS");
                    } else
                        emit opResultFailure("NEWFILE_FAILURE");
                } else if(opJSON == "OPENFILE_RESPONSE") {

                    std::string db_responseJSON;
                    jsonUtility::from_json_resp(jdata_in, db_responseJSON);

                    if(db_responseJSON == "OPENFILE_OK") {
                        std::vector<symbol> symbolsJSON;
                        jsonUtility::from_json_symbols(jdata_in, symbolsJSON);

                        //Update client data
                        this->Crdt.setSymbols(symbolsJSON);

                        emit opResultSuccess("OPENFILE_SUCCESS");
                    } else if(db_responseJSON == "OPENFILE_FILE_EMPTY") {
                        //Update client data
                        this->Crdt.setSymbols(std::vector<symbol>());
                        emit opResultSuccess("OPENFILE_SUCCESS");
                    } else
                        emit opResultFailure("OPENFILE_FAILURE");
                }  else if(opJSON == "INSERTION_RESPONSE") {
                    symbol symbolJSON;
                    int indexEditorJSON;
                    jsonUtility::from_json_insertion(jdata_in, symbolJSON, indexEditorJSON);

                    //process received symbol and retrieve new calculated index
                    int newIndex = this->Crdt.process(0, indexEditorJSON, symbolJSON);

                    std::pair<int, wchar_t> tuple = std::make_pair(newIndex, symbolJSON.getLetter());
                    emit insertSymbol(tuple);
                } else if(opJSON == "INSERTIONRANGE_RESPONSE") {
                    int firstIndexJSON;
                    std::vector<json> jsonSymbols;
                    jsonUtility::from_json_insertion_range(jdata_in, firstIndexJSON, jsonSymbols);
                    std::vector<symbol> symbols;
                    int newIndex = firstIndexJSON;

                    //generate symbols vector from json vector
                    for(const auto& j: jsonSymbols) {
                        symbol *s = nullptr; //do not remember to delete it! (keyword 'delete')
                        s = jsonUtility::from_json_symbol(j);
                        if(s==nullptr) {
                            emitMsgInCorrectWindow(); //show error
                            do_read_header();
                        }
                        symbols.push_back(*s);

                        //process received symbol and retrieve new calculated index
                        newIndex = this->Crdt.process(0, newIndex, *s);

                        std::pair<int, wchar_t> tuple = std::make_pair(newIndex, s->getLetter());
                        emit insertSymbol(tuple);

                        delete s;
                    }
                } else if(opJSON == "CURSOR_CHANGE_RESPONSE") {
                    std::string usernameJSON;
                    std::string colorJSON;
                    int posJSON;
                    jsonUtility::from_json_cursor_change(jdata_in, usernameJSON, colorJSON, posJSON);
                    emit changeRemoteCursor(usernameJSON, colorJSON, posJSON);
                }  else if(opJSON == "REMOVAL_RESPONSE") {
                    std::vector<sId> symbolsId;
                    jsonUtility::from_json_removal_range(jdata_in, symbolsId);

                    int newIndex;
                    for(const sId& id : symbolsId) {
                        //process received symbol and retrieve new calculated index
                        newIndex = this->Crdt.processErase(id);
                        if(newIndex != -1) {
                            emit eraseSymbols(newIndex, newIndex+1);
                        }
                    }
                } else {
                    qDebug() << "Something went wrong" << endl;
                    emit opResultFailure("RESPONSE_FAILURE");
                }
                fullBody = "";
                do_read_header(); //continue reading loop
            } catch (json::exception& e) {
                std::cerr << "message: " << e.what() << '\n' << "exception id: " << e.id << std::endl;
                emitMsgInCorrectWindow();
                fullBody = "";
                do_read_header();
            }
        }
        else {
            qDebug() << ec.message().c_str() << endl;
            closeConnection();
        }
    });

}

void myClient::emitMsgInCorrectWindow(){
    emit jsonMsgFailure("StartWindow","Cant parse json");
}

void myClient::do_write() {
    boost::asio::async_write(socket_,
                             boost::asio::buffer(write_msgs_.front().data(), write_msgs_.front().length()+1),
                             [this](boost::system::error_code ec, std::size_t /*length*/) {
         if (!ec) {
             qDebug() << "Sent:" << write_msgs_.front().data() << "END" << endl;
             write_msgs_.pop_front();
             if (!write_msgs_.empty()) {
                 do_write();
             }
         }
         else {
             qDebug() << ec.message().c_str() << endl;
             closeConnection();
         }
     });
}

bool myClient::getStatus() {
    return status;
}

void myClient::closeConnection() {
    status = false;
    emit statusChanged(status);
    socket_.close();
}

void myClient::write(const message& msg) {
    boost::asio::post(io_context_, [this, msg]() {
      bool write_in_progress = !write_msgs_.empty();
      write_msgs_.push_back(msg);
      if (!write_in_progress) {
          do_write();
      }
  });
}

void myClient::close() {
    boost::asio::post(io_context_, [this]() {
        closeConnection();
    });
}

void myClient::setUsername(QString name) {
    this->username_ = name;
}

QString myClient::getUsername() {
    return this->username_;
}

void myClient::setVectorFile(std::vector<File> files){
    this->fileVector_ = files;
}

QString myClient::getFilename() {
    return this->filename_;
}

void myClient::setFileURI(QString uri) {
    this->uri_ = uri;
}

QString myClient::getFileURI() {
    return this->uri_;
}

void myClient::sendRequestMsg(std::string request) {
    int mod = (request.length()%MAX_CHUNK_LENGTH==0) ? 1 : 0;
    int numChanks = (int)((request.length() / MAX_CHUNK_LENGTH) + 1 - mod);
    int chunkSize = MAX_CHUNK_LENGTH;
    char isLastChunk = '0';
    std::string chunkResponse = request;
    for(int i=0; i<numChanks; i++) {
        if(i == numChanks-1) {
            chunkSize = (int)(request.length() % MAX_CHUNK_LENGTH);
            isLastChunk = '1';
        }
        message msg = message::constructMsg(std::string(chunkResponse.begin(),
                chunkResponse.begin() + chunkSize), isLastChunk);
        chunkResponse.erase(0, chunkSize);
        this->write(msg); //deliver msg to the server
    }
}
