#include <iostream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Acceptor.hpp"
#include "Server.hpp"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

class MockAcceptor : public Acceptor {
public:
	MOCK_METHOD1(setOption, bool(int option));
	MOCK_METHOD0(open, void());
	MOCK_METHOD0(listen, void());
};

TEST(ServerTest, runWithOpen) {
	MockAcceptor acceptor;
	int option = 0;
	EXPECT_CALL(acceptor, setOption(option)).Times(AtLeast(1));
	EXPECT_CALL(acceptor, open()).Times(AtLeast(1));
	EXPECT_CALL(acceptor, listen()).Times(AtLeast(1));

	Server<MockAcceptor> server(&acceptor);
	server.run();
}

int main(int argc, char** argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}