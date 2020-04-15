#include "gmock/gmock.h"
#include "headers/RoomTextManager.h"
#include "headers/ClientTextManager.h"
#include "headers/TextDiff.h"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;



class MockRoomTextManager : public RoomTextManager<std::string> {
public:
    MOCK_METHOD1(addDiff, bool(std::string a));
    MOCK_METHOD0(getString, void());
    MOCK_METHOD0(getDiff, std::string());
    MOCK_METHOD2(formDiff, std::map<std::string, int>(std::string cur, std::string prev));
};


class MockClientTextManager : public ClientTextManager<std::string> {
public:
    MOCK_METHOD2(updateText, bool(std::string a, std::string diff));
    MOCK_METHOD0(getString, void());
    MOCK_METHOD2(formDiff, std::map<std::string, int>(std::string cur, std::string prev));
};

template<class ManagerType>
class GUI {
private:
    std::string current;
    ManagerType *manager_;
public:
    GUI(ManagerType *manager) : manager_(manager) {
        current = " ";
    }
    void displayContentToTextbox() {
        std::map<std::string,int> a = {{" ",1}};
        manager_->addDiff(" ");
        manager_->getString();
        manager_->getDiff();
        manager_->formDiff(current, current);
    }
};
template<class ManagerType>
class ChatRoom {
private:
    std::string current;
    ManagerType *manager_;
public:
    ChatRoom(ManagerType *manager):manager_(manager) {
        current = " ";
    }
std::string getText() {
    std::map<std::string,int> a = {{" ",1}};
    manager_->updateText(current,current);
    manager_->formDiff(current,current);
    return current;
    }
};

TEST(RoomText, Test1) {
    MockRoomTextManager textManager;
    EXPECT_CALL(textManager, addDiff(" ")).Times(AtLeast(1));
    EXPECT_CALL(textManager, getString()).Times(AtLeast(1));
    EXPECT_CALL(textManager, formDiff(" "," ")).Times(AtLeast(1));
    GUI<RoomTextManager<std::string>> chat(&textManager);
    chat.displayContentToTextbox();
}

TEST(ClientText, Test1) {
    MockClientTextManager textManager;
    EXPECT_CALL(textManager, formDiff(" "," ")).Times(AtLeast(1));
    EXPECT_CALL(textManager, updateText(" "," ")).Times(AtLeast(1));
    ChatRoom<MockClientTextManager> chat(&textManager);
    chat.getText();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}