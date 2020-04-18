//
// Created by ivan on 4/15/20.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <cstdlib>

#include "ChatRoom.h"
#include "MongoConnector.h"
#include "RoomManager.h"
#include "RoomTextManager.h"
#include "TextManger.h"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

using namespace std;

class MockChatRoom : public ChatRoom<RoomTextManager> {
public:
    MockChatRoom()= default;
    MOCK_METHOD0(addUser, std::string());
    MOCK_METHOD0(getText, std::string());
    MOCK_METHOD0(createDbTask, bool());
};

TEST(MockTest, RoomManagerTest) {
    MockChatRoom room;
    EXPECT_CALL(room, addUser()).Times(AtLeast(1));

    RoomManager<MockChatRoom> manager;
    manager.connectToRoom(&room);
}

class MockRoomTextManager : public RoomTextManager {
public:
    MockRoomTextManager()= default;
    MOCK_METHOD0(getString, std::string());
};

TEST(MockTest, TextManagerTest) {
    MockRoomTextManager manager;
    EXPECT_CALL(manager, getString()).Times(AtLeast(1));

    ChatRoom<MockRoomTextManager> room;
    room.getText(&manager);
}

