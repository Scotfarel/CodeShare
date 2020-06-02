#ifndef HEADERS_MYCLIENT_H_
#define HEADERS_MYCLIENT_H_

#include <boost/asio.hpp>
#include <QString>
#include <QDataStream>
#include <QTimer>
#include <thread>
#include <memory>
#include "headers/Message.h"
#include <deque>
#include "headers/jsonTypes.h"
#include "headers/symbol.h"
#include "headers/File.h"
#include <QDebug>
#include <iostream>
#include "headers/CRDT.h"

using boost::asio::ip::tcp;
typedef std::deque<Message> message_queue;
typedef std::pair<int, int> sId;

class ClientConnector : public QObject {
    Q_OBJECT

 public:
    ClientConnector(QString);
    virtual ~ClientConnector();
    CRDT Crdt;
    void do_connect();
    void room_choice();
    void create_room();
    void join_room(int);
    bool get_status();
    QString get_username();
    void set_room(int room_id);
    int get_room();
    void close();
    void write(const Message& msg);
    void send_req_msg(std::string request);

 signals:
    void statusChanged(bool);
    void formResultSuccess(QString result);
    void formResultFailure(QString result);
    void opResultSuccess(QString result);
    void opResultFailure(QString result);
    void editorResultSuccess(QString result, std::string filename = "");
    void editorResultFailure(QString result);
    void listFileResult(std::vector<File> files);
    void insertSymbol(std::pair<int, wchar_t> tuple);
    void insertSymbols(int firstIndex, std::vector<symbol> symbols);
    void eraseSymbols(int startIndex, int endIndex);
    void jsonMsgFailure(QString windowName, QString msg);
    void removeRemoteCursor(std::string username);
    void changeRemoteCursor(std::string username, std::string color, int pos);

 private:
    boost::asio::io_context io_context_;
    std::shared_ptr<boost::asio::io_context::work> work_;
    std::thread worker_;
    tcp::resolver resolver_;
    tcp::socket socket_;
    std::string fullBody;
    Message read_msg_;
    message_queue write_msgs_;
    void do_read_header();
    void do_read_body();
    void do_write();
    void close_connection();
    void emitMsgInCorrectWindow();
    bool status{};
    QString username_;
    int room_id_;
};

#endif  // HEADERS_MYCLIENT_H_
