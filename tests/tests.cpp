#include "gmock/gmock.h"
#include "../headers/ClientConnector.h"
#include "../headers/CRDT.h"
#include "../headers/NoteBook.h"
#include "../headers/TextEditor.h"
#include "../headers/jsonTypes.h"

using ::testing::AtLeast;

class MockClientConnector : public ClientConnector {
public:
    MOCK_METHOD2(updateText, bool(std::string a, std::string diff));
    MOCK_METHOD0(getString, void());
    MOCK_METHOD2(formDiff, std::map<std::string, int>(std::string cur, std::string prev));
};
class MockCRDT : public CRDT {
public:
    MOCK_METHOD1(addDiff, bool(std::string a));
    MOCK_METHOD0(getString, void());
    MOCK_METHOD0(getDiff, std::string());
    MOCK_METHOD2(formDiff, std::map<std::string, int>(std::string cur, std::string prev));
};
class MockNoteBook : public NoteBook {
public:
    MOCK_METHOD1(addDiff, bool(std::string a));
    MOCK_METHOD0(getString, void());
    MOCK_METHOD0(getDiff, std::string());
    MOCK_METHOD2(formDiff, std::map<std::string, int>(std::string cur, std::string prev));
};
class MockTextEditor : public TextEditor {
public:
    MOCK_METHOD1(addDiff, bool(std::string a));
    MOCK_METHOD0(getString, void());
    MOCK_METHOD0(getDiff, std::string());
    MOCK_METHOD2(formDiff, std::map<std::string, int>(std::string cur, std::string prev));
};
class MockjsonTypes : public jsonTypes {
public:
    MOCK_METHOD1(addDiff, bool(std::string a));
    MOCK_METHOD0(getString, void());
    MOCK_METHOD0(getDiff, std::string());
    MOCK_METHOD2(formDiff, std::map<std::string, int>(std::string cur, std::string prev));
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
TEST(RoomText, IsCalled) {
    MockRoomTextManager textManager;
    EXPECT_CALL(textManager, addDiff(" ")).Times(AtLeast(1));
    EXPECT_CALL(textManager, getString()).Times(AtLeast(1));
    EXPECT_CALL(textManager, formDiff(" "," ")).Times(AtLeast(1));
    GUI<MockRoomTextManager> chat(&textManager);
    chat.displayContentToTextbox();
}

TEST(ClientText, IsCalled) {
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
