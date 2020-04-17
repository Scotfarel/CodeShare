#include <iostream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Acceptor.hpp"
#include "Server.hpp"
#include "Connection.hpp"
#include "ConnectionManager.hpp"
#include "RequestHandler.hpp"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

class MockAcceptor : public Acceptor {
public:
	MOCK_METHOD1(setOption, void(int option));
	MOCK_METHOD0(open, void());
	MOCK_METHOD0(listen, void());
};

TEST(ServerTest, runCallOpen) {
	MockAcceptor acceptor;
	int option = 0;
	EXPECT_CALL(acceptor, setOption(option)).Times(AtLeast(1));
	EXPECT_CALL(acceptor, open()).Times(AtLeast(1));
	EXPECT_CALL(acceptor, listen()).Times(AtLeast(1));

	Server<MockAcceptor> server(&acceptor);
	server.run();
}

class MockConnection : public Connection<RequestHandler> {
public:
	MockConnection(RequestHandler* handler): Connection<RequestHandler>(handler) {}
	MOCK_METHOD0(start, void());
	MOCK_METHOD0(stop, void());
};

TEST(ConnectionManagerTest, startCallConnectionStart) {
	RequestHandler handler;
	MockConnection connection(&handler);
	EXPECT_CALL(connection, start()).Times(AtLeast(1));

	ConnectionManager<MockConnection> manager;
	manager.start(&connection);
}

TEST(ConnectionManagerTest, stopCallConnectionStop) {
	RequestHandler handler;
	MockConnection connection(&handler);
	EXPECT_CALL(connection, stop()).Times(AtLeast(1));

	ConnectionManager<MockConnection> manager;
	manager.stop(&connection);
}

class MockRequestHandler : public RequestHandler {
public:
	MOCK_METHOD1(handleRequest, void(int request));
};

TEST(ConnectionTest, startCallHandleRequest) {
	MockRequestHandler handler;
	int request = 0;
	EXPECT_CALL(handler, handleRequest(request)).Times(AtLeast(1));

	Connection<MockRequestHandler> connection(&handler);
	connection.start();
}

int main(int argc, char** argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}