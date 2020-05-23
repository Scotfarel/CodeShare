#ifndef PROJECT_INCLUDE_CONNECTION_H_
#define PROJECT_INCLUDE_CONNECTION_H_

#include <iostream>
#include <boost/beast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

template<class HandlerType>
class Connection {
public:
    Connection(HandlerType* handler, boost::asio::io_service& ioService) :
        requestHandler(handler),
        socket_(ioService) {}

    void start() {
        socket_.async_read_some(boost::asio::buffer(data_, maxLength),
            boost::bind(&Connection::handle_read, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }

    void stop() {
        std::cout << "stop" << std::endl;
    }

    boost::asio::ip::tcp::socket& getSocket() {
        return socket_;
    }
private:
    HandlerType* requestHandler;
    boost::asio::ip::tcp::socket socket_;
    enum { maxLength = 2048 };
    char data_[maxLength];

    void read() {
        requestHandler->handleRequest(0);
    }

    void write() {
        std::cout << "write" << std::endl;
    }

    void handle_read(const boost::system::error_code& error, size_t bytes_transferred) {
        if (!error) {
            // boost::asio::async_write(socket_, boost::asio::buffer(data_, bytes_transferred),
            //     boost::bind(&Connection::handle_write, this,boost::asio::placeholders::error));

            boost::system::error_code ec;
            boost::beast::http::request_parser<boost::beast::http::string_body> parser;
            parser.eager(true);
            parser.put(boost::asio::buffer(data_, bytes_transferred), ec);

            boost::beast::http::request<boost::beast::http::string_body> request = parser.get();
            auto body = request.body();

            if (request.method() == boost::beast::http::verb::post) {
                std::stringstream jsonEncoded(body);
                boost::property_tree::ptree root;
                boost::property_tree::read_json(jsonEncoded, root);

                std::cout << root.get<std::string>("value") << std::endl;
            }

            boost::property_tree::ptree responseData;
            responseData.put("roomId", 1);
            std::stringstream response;
            boost::property_tree::write_json(response, responseData);

            boost::asio::async_write(socket_, boost::asio::buffer(response.str()),
                boost::bind(&Connection::handle_write, this,boost::asio::placeholders::error));
        }
    }

    void handle_write(const boost::system::error_code& error) {
        if (!error) {
            socket_.async_read_some(boost::asio::buffer(data_, maxLength),
                boost::bind(&Connection::handle_read, this, boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
        }
    }
};

#endif  //  PROJECT_INCLUDE_CONNECTION_H_