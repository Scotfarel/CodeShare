#include <iostream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "boost/asio.hpp"

#include "RequestHandler.h"
#include "RoomScheduler.h"
#include "ConnectionManager.h"
#include "Connection.h"

using ::testing::AtLeast;

class MockRoomScheduler : public RoomScheduler {
public:
	static MockRoomScheduler& getInstance() {
        static MockRoomScheduler instance;
        return instance;
    }
	MOCK_METHOD0(createRoom, std::shared_ptr<ChatRoom>());
	MOCK_METHOD1(getRoom, std::shared_ptr<ChatRoom>(int id));
};

TEST(RequestHandlerTest, handlerRequestCallGetRoom) {
	MockRoomScheduler& scheduler = MockRoomScheduler::getInstance();
	EXPECT_CALL(scheduler, getRoom(0)).Times(AtLeast(1));

	RequestHandler<MockRoomScheduler> handler(scheduler);
	std::string type = "INSERTION_REQUEST";
	json j = json{
            {"operation", "operation"},
        	{"id", std::make_pair(0, 0)},
        	{"pos", std::vector<int>()},
        	{"letter", 0},
        	{"indexInEditor", 0},
			{"room_id", 0}
    };
	int id = 0;
	scheduler.createRoom();
	handler.handleRequest(type, j, id);
}

TEST(RequestHandlerTest, newRoomCallCreateRoom) {
	MockRoomScheduler& scheduler = MockRoomScheduler::getInstance();
	EXPECT_CALL(scheduler, createRoom()).Times(AtLeast(1));

	RequestHandler<MockRoomScheduler> handler(scheduler);
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::socket socket(io_service);
	std::shared_ptr<Connection> connection = std::make_shared<Connection>(std::move(socket));
	handler.newRoom(connection);
}

class MockConnection : public Connection {
public:
	using Connection::Connection;
	MOCK_METHOD1(start, void(int clientId));
	MOCK_METHOD0(stop, void());
	MOCK_METHOD0(readHeader, void());
	MOCK_METHOD0(writeClient, void());

	void mockStart() {
		Connection::start(0);
	}

	void mockDeliver() {
		MsgContext msg;
		Connection::deliver(msg);
	}
};

TEST(ConnectionManagerTest, StartCallStart) {
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::socket socket(io_service);
	std::shared_ptr<MockConnection> connection = std::make_shared<MockConnection>(std::move(socket));
	EXPECT_CALL(*connection, start(0)).Times(AtLeast(1));

	ConnectionManager<MockConnection>::getInstance().start(connection, 0);
}

TEST(ConnectionManagerTest, StopCallStop) {
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::socket socket(io_service);
	std::shared_ptr<MockConnection> connection = std::make_shared<MockConnection>(std::move(socket));
	EXPECT_CALL(*connection, stop()).Times(AtLeast(1));

	ConnectionManager<MockConnection>::getInstance().stop(connection);
}

TEST(ConnectionManagerTest, StopAllCallStop) {
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::socket socket(io_service);
	std::shared_ptr<MockConnection> connection = std::make_shared<MockConnection>(std::move(socket));
	EXPECT_CALL(*connection, stop()).Times(AtLeast(1));

	ConnectionManager<MockConnection>::getInstance().start(connection, 0);
	ConnectionManager<MockConnection>::getInstance().stopAll();
}

TEST(ConnectionTest, StartCallReadHeader) {
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::socket socket(io_service);
	std::shared_ptr<MockConnection> connection = std::make_shared<MockConnection>(std::move(socket));
	EXPECT_CALL(*connection, readHeader()).Times(AtLeast(1));

	connection->mockStart();
}

TEST(ConnectionTest, DeliverCallWriteClient) {
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::socket socket(io_service);
	std::shared_ptr<MockConnection> connection = std::make_shared<MockConnection>(std::move(socket));
	EXPECT_CALL(*connection, writeClient()).Times(AtLeast(1));

	connection->mockDeliver();
}

int main(int argc, char** argv) {
	::testing::InitGoogleMock(&argc, argv);
  	return RUN_ALL_TESTS();
}