#include "headers/NoteBook.h"
#include "ui_NoteBook.h"
#include "headers/TextEditor.h"
#include <QLineEdit>
#include <QTextStream>
#include <QMessageBox>
#include <QGraphicsOpacityEffect>
#include <QEvent>
#include <stdexcept>
#include <QMenu>
#include <QCursor>
#include <QShortcut>

using json = nlohmann::json;
typedef std::pair<int, int> pair_int;

NoteBook::NoteBook(ClientConnector *client, QWidget *parent) : QMainWindow(parent), UI(new Ui::NoteBook),
                                                               _client(client) {
    UI->setupUi(this);
    connect(_client, &ClientConnector::insertSymbol, this, &NoteBook::show_sym);
    connect(_client, &ClientConnector::eraseSymbols, this, &NoteBook::erase_sym);
    connect(_client, &ClientConnector::insertSymbols, this, &NoteBook::show_sym_in_pos);
//    connect(_client, &ClientConnector::removeRemoteCursor, UI->RealTextEdit, &TextEditor::removeRemoteCursor);
//    connect(_client, &ClientConnector::changeRemoteCursor, UI->RealTextEdit, &TextEditor::changeRemoteCursor);
    connect(&UI->RealTextEdit->timer, &QTimer::timeout, UI->RealTextEdit, &TextEditor::hideHorizontalRect);
    connect(_client, &ClientConnector::statusChanged, this, &NoteBook::end_session);

    setupFirstLetter();
    setupTextEdit();
    cursor_change_req(0);
    qRegisterMetaType<std::vector<Symbol>>("std::vector<Symbol>");
    qRegisterMetaType<myCollabColorsMap>("std::map<std::string,std::pair<std::string,bool>");
    show_sym_in_pos(0, _client->crdt.get_symbols());
    this->installEventFilter(this);
    UI->RealTextEdit->installEventFilter(this);
}

void NoteBook::setupTextEdit() {
    UI->RealTextEdit->setFontPointSize(14);
    UI->RealTextEdit->setFontFamily("Times New Roman");
    UI->RealTextEdit->setAcceptDrops(false);
    UI->RealTextEdit->setUndoRedoEnabled(false);
    UI->RealTextEdit->document()->setDocumentMargin(50);
}

void NoteBook::setupFirstLetter() {
    QString user = _client->get_username();
    UI->labelUser->setText(user);
    QChar firstLetter;
    for (int i = 0; i < user.length(); i++) {
        firstLetter = user.at(i);
        if (firstLetter.isLetter()) {
            break;
        }
    }
}

NoteBook::~NoteBook() {
    emit closeEditor();
    delete UI;
}

void NoteBook::on_RealTextEdit_textChanged() {
    int charCount = UI->RealTextEdit->toPlainText().count();
    int wordCount = UI->RealTextEdit->toPlainText().split(QRegExp("(\\s|\\n|\\r)+"), QString::SkipEmptyParts).count();
    int lineCount = UI->RealTextEdit->document()->blockCount();
    QString ZaChar = "Characters: " + QString::number(charCount);
    QString ZaLine;
    QString ZaWord = "Words: " + QString::number(wordCount);
    if (charCount == 0 && wordCount == 0) {
        ZaLine = "Lines: 0";
    } else {
        ZaLine = "Lines: " + QString::number(lineCount);
    }
    UI->label->setText(ZaChar);
    UI->label_2->setText(ZaWord);
    UI->label_3->setText(ZaLine);
}

bool NoteBook::eventFilter(QObject *obj, QEvent *ev) {
    if (ev->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(ev);
        qDebug() << "You Pressed Key " + keyEvent->text();
        int key = keyEvent->key();
        Qt::KeyboardModifiers modifiers = keyEvent->modifiers();

        /* Trigger these shortcuts only if you are inside doc */
        if (obj == UI->RealTextEdit) {
            if (!keyEvent->text().isEmpty()) {
                if (keyEvent->matches(QKeySequence::Cut)) {
                    QTextCursor cursor = UI->RealTextEdit->textCursor();
                    if (cursor.hasSelection()) {
                        int startIndex = cursor.selectionStart();
                        int endIndex = cursor.selectionEnd();

                        std::vector<pair_int> symbolsId = _client->crdt.localErase(startIndex, endIndex);

                        remove_req(symbolsId);
                    }
                    return QObject::eventFilter(obj, ev);
                } else if (keyEvent->matches(QKeySequence::Copy)) {
                    return false;  // let the original handler handle this sequence
                } else if (keyEvent->matches(QKeySequence::Paste)) {
            QTextCursor cursor = UI->RealTextEdit->textCursor();
            int pos;
            bool hasSelection = false;

            cursor.hasSelection() ? pos = cursor.selectionStart() : pos = cursor.position();
            try {
                if (cursor.hasSelection()) {
                    hasSelection = true;
                    int startIndex = cursor.selectionStart();
                    int endIndex = cursor.selectionEnd();
                    // Update symbols of the client
                    std::vector<pair_int> symbolsId = _client->crdt.localErase(startIndex, endIndex);
                    remove_req(symbolsId);
                }
                insert_range_req(pos, hasSelection);
            } catch(OperationNotSupported& ex) {
                qDebug() << ex.what();
                cursor.removeSelectedText();
                return true;  // not paste text
            }
            return QObject::eventFilter(obj, ev);
                }  else if (keyEvent->matches(QKeySequence::SelectAll)) {
                    return false;
                } else if ((modifiers & Qt::ControlModifier) && !(key == Qt::Key_BracketLeft) &&
                         !(key == Qt::Key_BracketRight)
                         && !(key == Qt::Key_BraceLeft) && !(key == Qt::Key_BraceRight) && !(key == Qt::Key_At) &&
                         !(key == Qt::Key_NumberSign)) {
                    qDebug() << "Operation Not Supported";
                    return true;
                } else if (!(key == Qt::Key_Backspace) && !(key == Qt::Key_Delete) && !(key == Qt::Key_Escape)) {
                    // Get data
                    std::pair<int, wchar_t> tuple;
                    QTextCursor cursor = UI->RealTextEdit->textCursor();
                    int pos;

                    if (cursor.hasSelection()) {  // Remove range of characters selected
                        pos = cursor.selectionStart();
                        int startIndex = cursor.selectionStart();
                        int endIndex = cursor.selectionEnd();
                        QTextCursor tempCursor = cursor;

                        // get properties of the first char of the selection
                        tempCursor.beginEditBlock();
                        tempCursor.setPosition(startIndex + 1, QTextCursor::MoveAnchor);
                        tempCursor.endEditBlock();

                        QTextCharFormat f;
                        QTextBlockFormat textBlockFormat;

                        // apply format
                        cursor.beginEditBlock();
                        cursor.setPosition(startIndex, QTextCursor::MoveAnchor);
                        cursor.setPosition(endIndex, QTextCursor::KeepAnchor);
                        cursor.mergeCharFormat(f);
                        cursor.mergeBlockFormat(textBlockFormat);
                        UI->RealTextEdit->mergeCurrentCharFormat(f);
                        UI->RealTextEdit->setTextCursor(cursor);
                        cursor.endEditBlock();

                        // update symbols of the client
                        std::vector<int_pair> symbolsId = _client->crdt.localErase(startIndex, endIndex);

                        // Serialize data
                        json j;
                        jsonTypes::to_json_removal_range(j, "REMOVAL_REQUEST", symbolsId,_client->get_room());
                        const std::string req = j.dump();

                        // Send data (header and body)
                        _client->send_req_msg(req);
                    } else {
                        pos = cursor.position();
                    }
                    // update textedit formats
                    wchar_t c = keyEvent->text().toStdWString().c_str()[0];
                    // update symbols of the client
                    Symbol s = _client->crdt.localInsert(pos, c);

                    // Serialize data
                    json j;
                    jsonTypes::to_json_insertion(j, "INSERTION_REQUEST", s, pos,_client->get_room());
                    const std::string req = j.dump();

                    _client->send_req_msg(req);
                    return QObject::eventFilter(obj, ev);
                } else if (key == Qt::Key_Backspace) {
                    QTextCursor cursor = UI->RealTextEdit->textCursor();
                    int pos = cursor.position();

                    if (cursor.hasSelection()) {
                        int startIndex = cursor.selectionStart();
                        int endIndex = cursor.selectionEnd();

                        /* Update new alignment */
                        cursor.setPosition(startIndex);
                        QTextBlockFormat textBlockFormat;
                        cursor.mergeBlockFormat(textBlockFormat);
                        UI->RealTextEdit->setAlignment(textBlockFormat.alignment());
                        cursor.setPosition(pos);

                        std::vector<pair_int> symbolsId = _client->crdt.localErase(startIndex, endIndex);

                        remove_req(symbolsId);
                    } else if (pos > 0) {
                        std::vector<pair_int> symbolsId = _client->crdt.localErase(pos - 1, pos);
                        remove_req(symbolsId);
                    }
                    return QObject::eventFilter(obj, ev);
                } else if (key == Qt::Key_Delete) {
                    QTextCursor cursor = UI->RealTextEdit->textCursor();
                    int pos = cursor.position();

                    if (cursor.hasSelection()) {
                        int startIndex = cursor.selectionStart();
                        int endIndex = cursor.selectionEnd();

                        /* Update new alignment */
                        cursor.setPosition(cursor.selectionStart());
                        QTextBlockFormat textBlockFormat;
                        cursor.mergeBlockFormat(textBlockFormat);
                        UI->RealTextEdit->setAlignment(textBlockFormat.alignment());
                        cursor.setPosition(pos);
                        // Update symbols of the client
                        std::vector<pair_int> symbolsId = _client->crdt.localErase(startIndex, endIndex);

                        remove_req(symbolsId);
                    } else if (pos >= 0 && pos < UI->RealTextEdit->toPlainText().size()) {
                        std::vector<pair_int> symbolsId = _client->crdt.localErase(pos, pos + 1);

                        remove_req(symbolsId);
                    }
                    return QObject::eventFilter(obj, ev);
                } else if (key == Qt::Key_Escape) {
                    return true;  // do not handle ESC
                }
            } else {
                return QObject::eventFilter(obj, ev);
            }
        }
    }
    return false;  // or return QObject::eventFilter(obj, ev);
}

void NoteBook::show_sym_in_pos(int startIndex, std::vector<Symbol> symbols) {
    wchar_t letter;
    int index = startIndex;
    QTextCursor c = UI->RealTextEdit->textCursor();

    c.beginEditBlock();
            foreach(Symbol s, symbols) {
            letter = s.get_letter();

            int endIndex;
            int pos = index++;
            c.hasSelection() ? endIndex = c.selectionEnd() : endIndex = -90;
            int oldPos = pos < c.position() ? c.position() + 1 : c.position();

            // if user2 insert a char at the end of the selection of user1 -> this can cause extension of user1's selection (that is wrong)
            if (c.hasSelection() && pos == endIndex) {
                int startIndex = c.selectionStart();

                /* Insert (formatted) char */
                c.setPosition(pos);
                c.insertText(static_cast<QString>(letter));
                c.movePosition(QTextCursor::Right);
                c.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor);

                /* Keep current selection */
                c.setPosition(oldPos == startIndex ? endIndex : startIndex, QTextCursor::MoveAnchor);
                c.setPosition(oldPos == startIndex ? startIndex : endIndex, QTextCursor::KeepAnchor);
            } else {
                /* Insert (formatted) char */
                c.setPosition(pos);
                c.insertText(static_cast<QString>(letter));
                c.movePosition(QTextCursor::Right);
                c.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor);
                c.setPosition(oldPos);
            }
        }
    c.endEditBlock();
    UI->RealTextEdit->setTextCursor(c);
}

void NoteBook::show_sym(std::pair<int, wchar_t> tuple) {
    int pos = tuple.first;
    wchar_t c = tuple.second;
    QTextCharFormat format;
    QTextBlockFormat newBlockFormat;

    QTextCursor cursor = UI->RealTextEdit->textCursor();
    cursor.beginEditBlock();

    int endIndex;
    cursor.hasSelection() ? endIndex = cursor.selectionEnd() : endIndex = -90;
    int oldPos = pos < cursor.position() ? cursor.position() + 1 : cursor.position();

    // if user2 insert a char at the end of the selection of user1 -> this can cause extension of user1's selection (that is wrong)
    if (cursor.hasSelection() && pos == endIndex) {
        int startIndex = cursor.selectionStart();

        /* Insert (formatted) char */
        cursor.setPosition(pos);
        cursor.setCharFormat(format);
        cursor.insertText(static_cast<QString>(c));
        cursor.movePosition(QTextCursor::Right);
        cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor);
        cursor.setBlockFormat(newBlockFormat);

        /* Keep current selection */
        cursor.setPosition(oldPos == startIndex ? endIndex : startIndex, QTextCursor::MoveAnchor);
        cursor.setPosition(oldPos == startIndex ? startIndex : endIndex, QTextCursor::KeepAnchor);
    } else {
        cursor.setPosition(pos);
        cursor.setCharFormat(format);
        cursor.insertText(static_cast<QString>(c));
        cursor.movePosition(QTextCursor::Right);
        cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor);
        cursor.setBlockFormat(newBlockFormat);
        cursor.setPosition(oldPos);
    }
    cursor.endEditBlock();
    UI->RealTextEdit->setTextCursor(cursor);

    qDebug() << "Written in pos: " << pos << endl;
    UI->RealTextEdit->setFocus();
}

void NoteBook::erase_sym(int startIndex, int endIndex) {
    QTextCursor cursor = UI->RealTextEdit->textCursor();
    cursor.beginEditBlock();
    cursor.setPosition(startIndex);
    int startAlignment = cursor.blockFormat().alignment();
    cursor.setPosition(endIndex);
    cursor.setPosition(startIndex + 1, QTextCursor::KeepAnchor);
    cursor.removeSelectedText();
    cursor.setPosition(startIndex, QTextCursor::KeepAnchor);
    cursor.removeSelectedText();
    QTextBlockFormat textBlockFormat;
    textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(static_cast<Qt::AlignmentFlag>(startAlignment));
    cursor.mergeBlockFormat(textBlockFormat);

    cursor.endEditBlock();

    qDebug() << "Deleted char range" << endl;
    UI->RealTextEdit->setFocus();
}
void NoteBook::remove_req(const std::vector<pair_int> &symbolsId) {
    json j;
    jsonTypes::to_json_removal_range(j, "REMOVAL_REQUEST", symbolsId,_client->get_room());
    const std::string req = j.dump();
    _client->send_req_msg(req);
}
void NoteBook::cursor_change_req(int pos) {
    json j;
    jsonTypes::to_json_cursor_change_req(j, "CURSOR_CHANGE_REQUEST", pos,_client->get_room());
    const std::string req = j.dump();
    _client->send_req_msg(req);
}

void NoteBook::insert_range_req(int pos, bool cursorHasSelection) noexcept(false) {
    QClipboard *clipboard = QApplication::clipboard();
    const QMimeData *mimeData = clipboard->mimeData();
    QTextCursor cursor = UI->RealTextEdit->textCursor();

    if (mimeData->hasText() && !mimeData->hasImage() && !mimeData->hasUrls() && !mimeData->html().contains("<a href")) {
        /* Get chars from clipboard mimeData */
        int numChars = mimeData->text().size();  // number of chars = number of iterations
        std::wstring str_to_paste = mimeData->text().toStdWString();

        std::vector<Symbol> infoSymbols;  // temporary vector without symbol pos (it will be used by the process)
        int index;
        wchar_t c;
        int initialPos = pos;
        std::vector<Symbol> symbols = _client->crdt.localInsert(initialPos, infoSymbols);
        // Serialize data
        json j;
        std::vector<json> symFormattingVectorJSON = jsonTypes::fromFormattingSymToJson(symbols);
        jsonTypes::to_json_insertion_range(j, "INSERTIONRANGE_REQUEST", symFormattingVectorJSON,
                initialPos,_client->get_room());
        const std::string req = j.dump();
        _client->send_req_msg(req);
    } else {
        qDebug() << "Cannot paste this." << endl;
    }
}
void NoteBook::end_session() {
    if (!_client->get_status()) {
        QMessageBox::warning(nullptr, "Attention",
                             "Cant reach server \n\nApplication needs to be closed");
    }
}
