#include "gmock/gmock.h"
#include "headers/RoomTextManager.h"
#include "headers/ClientTextManager.h"
#include "headers/TextDiff.h"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;



class MockRoomTextManager : public RoomTextManager {
public:
    MOCK_METHOD1(addDiff, bool(TextDiff a));
    MOCK_METHOD0(getString, void());
    MOCK_METHOD0(getDiff, TextDiff());
    MOCK_METHOD2(formDiff, std::map<TextDiff, int>(std::string cur, std::string prev));
};


class MockClientTextManager : public ClientTextManager {
    MOCK_METHOD2(updateText, bool(std::string a, std::map<TextDiff, int>));
    MOCK_METHOD0(getString, void());
    MOCK_METHOD2(formDiff, std::map<TextDiff, int>(std::string cur, std::string prev));
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
        TextDiff diff;
        std::map<TextDiff,int> a = {{diff,1}};
        manager_->addDiff(diff);
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
    struct TextDiff diff = {0, 0, " ", " "};
    std::map<TextDiff,int> a = {{diff,1}};
    manager_->updateText(current,a);
    manager_->formDiff(current,current);
    return current;
    }

};

TEST(RoomText, Test1) {
    MockRoomTextManager textManager;
    struct TextDiff diff = {0, 0, " ", " "};
    EXPECT_CALL(textManager, addDiff(diff)).Times(AtLeast(1));
    EXPECT_CALL(textManager, getString()).Times(AtLeast(1));
    EXPECT_CALL(textManager, formDiff(" "," ")).Times(AtLeast(1));
    GUI<RoomTextManager> chat(&textManager);
    chat.displayContentToTextbox();

}

TEST(ClientText, Test1) {
    EXPECT_TRUE(1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}