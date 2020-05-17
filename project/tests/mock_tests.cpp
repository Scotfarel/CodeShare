#include <iostream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "boost/asio.hpp"

#include "Acceptor.hpp"
#include "Server.hpp"
#include "Connection.hpp"
#include "ConnectionManager.hpp"
#include "RequestHandler.hpp"
#include "RoomScheduler.hpp"

using ::testing::AtLeast;

class MockAcceptor : public Acceptor {
public:
	using Acceptor::Acceptor;
	MOCK_METHOD1(setOption, void(bool option));
	MOCK_METHOD0(open, void());
	MOCK_METHOD0(bind, void());
	MOCK_METHOD0(listen, void());
};

TEST(ServerTest, runCallOpen) {
	boost::asio::io_service service;
	boost::asio::ip::tcp::endpoint endpoint;
	MockAcceptor acceptor(service, endpoint);
	EXPECT_CALL(acceptor, open()).Times(AtLeast(1));

	Server<MockAcceptor> server(&service, &acceptor);
	server.run();
}

TEST(ServerTest, runCallBind) {
	boost::asio::io_service service;
	boost::asio::ip::tcp::endpoint endpoint;
	MockAcceptor acceptor(service, endpoint);
	EXPECT_CALL(acceptor, bind()).Times(AtLeast(1));

	Server<MockAcceptor> server(&service, &acceptor);
	server.run();
}

TEST(ServerTest, runCallListen) {
	boost::asio::io_service service;
	boost::asio::ip::tcp::endpoint endpoint;
	MockAcceptor acceptor(service, endpoint);
	EXPECT_CALL(acceptor, listen()).Times(AtLeast(1));

	Server<MockAcceptor> server(&service, &acceptor);
	server.run();
}

TEST(ServerTest, runCallSetOption) {
	boost::asio::io_service service;
	boost::asio::ip::tcp::endpoint endpoint;
	MockAcceptor acceptor(service, endpoint);
	bool option = true;
	EXPECT_CALL(acceptor, setOption(option)).Times(AtLeast(1));

	Server<MockAcceptor> server(&service, &acceptor);
	server.run();
}

class MockConnection : public Connection<RequestHandler<RoomScheduler> > {
public:
	MockConnection(RequestHandler<RoomScheduler>* handler): Connection<RequestHandler<RoomScheduler> >(handler) {}
	MOCK_METHOD0(start, void());
	MOCK_METHOD0(stop, void());
};

TEST(ConnectionManagerTest, startCallConnectionStart) {
	RoomScheduler scheduler;
	RequestHandler<RoomScheduler> handler(&scheduler);
	MockConnection connection(&handler);
	EXPECT_CALL(connection, start()).Times(AtLeast(1));

	ConnectionManager<MockConnection> manager;
	manager.start(&connection);
}

TEST(ConnectionManagerTest, stopCallConnectionStop) {
	RoomScheduler scheduler;
	RequestHandler<RoomScheduler> handler(&scheduler);
	MockConnection connection(&handler);
	EXPECT_CALL(connection, stop()).Times(AtLeast(1));

	ConnectionManager<MockConnection> manager;
	manager.stop(&connection);
}

class MockRequestHandler : public RequestHandler<RoomScheduler> {
public:
	MockRequestHandler(RoomScheduler* scheduler) : RequestHandler<RoomScheduler>(scheduler) {}
	MOCK_METHOD1(handleRequest, void(int request));
};

TEST(ConnectionTest, startCallHandleRequest) {
	RoomScheduler scheduler;
	MockRequestHandler handler(&scheduler);
	int request = 0;
	EXPECT_CALL(handler, handleRequest(request)).Times(AtLeast(1));

	Connection<MockRequestHandler> connection(&handler);
	connection.start();
}

class MockRoomScheduler : public RoomScheduler {
public:
	MOCK_METHOD0(createRoom, void());
	MOCK_METHOD0(getRoom, void());
	MOCK_METHOD0(connectToRoom, void());
	MOCK_METHOD0(deleteRoom, void());
};

TEST(RequestHandlerTest, handlerRequestCallRoomSchedulersMethods) {
	MockRoomScheduler scheduler;
	EXPECT_CALL(scheduler, createRoom()).Times(AtLeast(1));
	EXPECT_CALL(scheduler, getRoom()).Times(AtLeast(1));
	EXPECT_CALL(scheduler, connectToRoom()).Times(AtLeast(1));
	EXPECT_CALL(scheduler, deleteRoom()).Times(AtLeast(1));

	RequestHandler<MockRoomScheduler> handler(&scheduler);
	for (int request = 0; request <= 3; request++) {
		handler.handleRequest(request);
	}
}

int main(int argc, char** argv) {
	::testing::InitGoogleMock(&argc, argv);
  	return RUN_ALL_TESTS();
}