#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <boost/asio.hpp>
#include <QString>
#include <QDataStream>
#include <QTimer>
#include <thread>
#include <memory>
#include "headers/message.h"
#include <deque>
#include "headers/jsonUtility.h"
#include "headers/symbol.h"
#include "headers/File.h"
#include <QDebug>
#include <iostream>
#include "headers/CRDT.h"

using boost::asio::ip::tcp;
typedef std::deque<message> message_queue;
typedef std::pair<int,int> sId;

class myClient : public QObject
{
    Q_OBJECT

public:
    myClient();
    virtual ~myClient();
    CRDT Crdt;
    void do_connect();
    bool getStatus();
    QString getUsername();
    QString getFileURI();
    void setFileURI(QString uri);
    void close();
    void write(const message& msg);
    void sendRequestMsg(std::string request);

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
    message read_msg_;
    message_queue write_msgs_;
    void do_read_header();
    void do_read_body();
    void do_write();
    void closeConnection();
    void emitMsgInCorrectWindow();
    bool status{};
    QString username_;
    QString uri_;
    std::vector<File> fileVector_;
};

#endif // MYCLIENT_H
