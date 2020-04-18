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

class MockChatRoom : public ChatRoom<RoomTextBuilder, MongoConnector> {
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

    ChatRoom<MockRoomTextScheduler, MongoConnector> room;
    room.getText(&manager);
}

class MockMongoConnector : public MongoConnector {
public:
    MockMongoConnector(std::string db, std::string coll) : dbName(std::move(db)), collName(std::move(coll)) {};
    MOCK_METHOD0(getChunk, std::string());
    MOCK_METHOD0(getCurrText, std::string());
    MOCK_METHOD0(saveDiff, bool());
    MOCK_METHOD1(createRoomTable, bool(std::string tableName));
private:
    std::string dbName;
    std::string collName;
};


// Mock-test for MongoDB connection to fake connector's methods
TEST(MockTest, MongoConnectorTest) {
    std::string name = "testName";
    std::string table = "testTableName";
    MockMongoConnector dbConn(name, table);

    EXPECT_CALL(dbConn, getChunk()).Times(AtLeast(1));
    EXPECT_CALL(dbConn, getCurrText()).Times(AtLeast(1));
    EXPECT_CALL(dbConn, saveDiff()).Times(AtLeast(1));
    EXPECT_CALL(dbConn, createRoomTable(table)).Times(AtLeast(1));

    ChatRoom<MockRoomTextScheduler, MockMongoConnector> room(&dbConn);
    room.addUser();
}