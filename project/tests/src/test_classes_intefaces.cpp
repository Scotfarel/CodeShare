//
// Created by ivan on 4/15/20.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <cstdlib>

#include "ChatRoom.h"
#include "MongoConnector.h"
#include "RoomScheduler.h"
#include "RoomTextBuilder.h"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

using namespace std;

class MockChatRoom : public ChatRoom<RoomTextBuilder> {
public:
    MockChatRoom()= default;
    MOCK_METHOD0(addUser, std::string());
    MOCK_METHOD0(getText, std::string());
    MOCK_METHOD0(createDbTask, bool());
};

// Mock-tests for ChatRoom and RoomScheduler
TEST(MockTest, RoomSchedulerTest) {
    MockChatRoom room;
    EXPECT_CALL(room, addUser()).Times(AtLeast(1));

    RoomScheduler<MockChatRoom> manager;
    manager.connectToRoom(&room);
}

class MockRoomTextScheduler : public RoomTextBuilder {
public:
    MockRoomTextScheduler()= default;
    MOCK_METHOD0(getString, std::string());
};

// Mock-tests for RoomTextBuilder and ChatRoom
TEST(MockTest, TextBuilderTest) {
    MockRoomTextScheduler manager;
    EXPECT_CALL(manager, getString()).Times(AtLeast(1));

    ChatRoom<MockRoomTextScheduler> room;
    room.getText(&manager);
}

class MockMongoConnector : public MongoConnector {
public:
    MockMongoConnector() = default;
    MOCK_METHOD0(getChunk, std::string());
    MOCK_METHOD0(getCurrText, std::string());
    MOCK_METHOD0(saveDiff, bool());
    MOCK_METHOD0(createRoomTable, bool());
};