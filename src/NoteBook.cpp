#include "headers/NoteBook.h"
#include "headers/ui_NoteBook.h"
#include "headers/MyQTextEdit.h"
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
typedef std::pair<int, int> sId;

NoteBook::NoteBook(myClient *client, QWidget *parent) : QMainWindow(parent), ui(new Ui::NoteBook),
                                                        _client(client) {
    ui->setupUi(this);
    connect(_client, &myClient::insertSymbol, this, &NoteBook::showSymbol);
    connect(_client, &myClient::eraseSymbols, this, &NoteBook::eraseSymbols);
    connect(_client, &myClient::insertSymbols, this, &NoteBook::showSymbolsAt);
    connect(_client, &myClient::removeRemoteCursor, ui->RealTextEdit, &MyQTextEdit::removeRemoteCursor);
    connect(_client, &myClient::changeRemoteCursor, ui->RealTextEdit, &MyQTextEdit::changeRemoteCursor);
    connect(&ui->RealTextEdit->timer, &QTimer::timeout, ui->RealTextEdit, &MyQTextEdit::hideHorizontalRect);
    connect(_client, &myClient::statusChanged, this, &NoteBook::goodbyeClient);

    setupFirstLetter();
    setupTextEdit();
    cursorChangeRequest(0);
    qRegisterMetaType<std::vector<symbol>>("std::vector<symbol>");
    qRegisterMetaType<myCollabColorsMap>("std::map<std::string,std::pair<std::string,bool>");
    showSymbolsAt(0, _client->Crdt.getSymbols());
    this->installEventFilter(this);
    ui->RealTextEdit->installEventFilter(this);
}

void NoteBook::setupTextEdit() {
    ui->RealTextEdit->setFontPointSize(14);
    ui->RealTextEdit->setFontFamily("Times New Roman");
    ui->RealTextEdit->setAcceptDrops(false);
    ui->RealTextEdit->setUndoRedoEnabled(false);
    ui->RealTextEdit->document()->setDocumentMargin(50);
}

void NoteBook::setupFirstLetter() {
    QString user = _client->getUsername();
    ui->labelUser->setText(user);

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
    delete ui;
}

void NoteBook::on_RealTextEdit_textChanged() {
    int charCount = ui->RealTextEdit->toPlainText().count();
    int wordCount = ui->RealTextEdit->toPlainText().split(QRegExp("(\\s|\\n|\\r)+"), QString::SkipEmptyParts).count();
    int lineCount = ui->RealTextEdit->document()->blockCount();
    QString ZaChar = "Characters: " + QString::number(charCount);
    QString ZaLine;
    QString ZaWord = "Words: " + QString::number(wordCount);
    if (charCount == 0 && wordCount == 0) {
        ZaLine = "Lines: 0";
    } else {
        ZaLine = "Lines: " + QString::number(lineCount);
    }
    ui->label->setText(ZaChar);
    ui->label_2->setText(ZaWord);
    ui->label_3->setText(ZaLine);
}

bool NoteBook::eventFilter(QObject *obj, QEvent *ev) {

    if (ev->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(ev);
        qDebug() << "You Pressed Key " + keyEvent->text();
        int key = keyEvent->key();
        Qt::KeyboardModifiers modifiers = keyEvent->modifiers();
        QList<Qt::Key> modifiersList;

if ((key == Qt::Key_Q) && (modifiers == Qt::ControlModifier) && QApplication::keyboardModifiers()) {
            on_actionClose_triggered();
            return true;
        }
        /* Trigger these shortcuts only if you are inside doc */
        if (obj == ui->RealTextEdit) {
            if (!keyEvent->text().isEmpty()) { //to ignore chars like "CAPS_LOCK", "SHIFT", "CTRL", etc...
                //************************************************* CTRL-X *************************************************
                if (keyEvent->matches(QKeySequence::Cut)) {
                    QTextCursor cursor = ui->RealTextEdit->textCursor();
                    if (cursor.hasSelection()) {
                        int startIndex = cursor.selectionStart();
                        int endIndex = cursor.selectionEnd();

                        std::vector<sId> symbolsId = _client->Crdt.localErase(startIndex, endIndex);

                        removeCharRequest(symbolsId);
                    }
                    return QObject::eventFilter(obj, ev);
                } //*********************************************** CTRL-C *************************************************
                else if (keyEvent->matches(QKeySequence::Copy)) {
                    return false; //let the original handler handle this sequence
                } //*********************************************** CTRL-V *************************************************
                else if (keyEvent->matches(QKeySequence::Paste)) {
            QTextCursor cursor = ui->RealTextEdit->textCursor();
            int pos;
            bool hasSelection = false;

            cursor.hasSelection() ? pos = cursor.selectionStart() : pos = cursor.position();
            try {
                if(cursor.hasSelection()) {
                    hasSelection = true;
                    int startIndex = cursor.selectionStart();
                    int endIndex = cursor.selectionEnd();

                    //Update symbols of the client
                    std::vector<sId> symbolsId = _client->Crdt.localErase(startIndex, endIndex);

                    removeCharRequest(symbolsId);
                }
                insertCharRangeRequest(pos, hasSelection);
            } catch(OperationNotSupported& ex) {
                qDebug() << ex.what();
                cursor.removeSelectedText();
                return true; //not paste text
            }
            return QObject::eventFilter(obj, ev);
                } //*********************************************** CTRL-A *************************************************
                else if (keyEvent->matches(QKeySequence::SelectAll)) {
                    return false;
                }
                    // ******************************************** ALL THE OTHER CTRL COMBINATION ****************************
                else if ((modifiers & Qt::ControlModifier) && !(key == Qt::Key_BracketLeft) &&
                         !(key == Qt::Key_BracketRight)
                         && !(key == Qt::Key_BraceLeft) && !(key == Qt::Key_BraceRight) && !(key == Qt::Key_At) &&
                         !(key == Qt::Key_NumberSign)) {
                    qDebug() << "Operation Not Supported";
                    return true;
                } //******************************************** ANY DIGIT *************************************************
                else if (!(key == Qt::Key_Backspace) && !(key == Qt::Key_Delete) && !(key == Qt::Key_Escape)) {
                    //Get data
                    std::pair<int, wchar_t> tuple;
                    QTextCursor cursor = ui->RealTextEdit->textCursor();
                    int pos;

                    if (cursor.hasSelection()) { //Remove range of characters selected
                        pos = cursor.selectionStart();
                        int startIndex = cursor.selectionStart();
                        int endIndex = cursor.selectionEnd();
                        QTextCursor tempCursor = cursor;

                        //get properties of the first char of the selection
                        tempCursor.beginEditBlock();
                        tempCursor.setPosition(startIndex + 1, QTextCursor::MoveAnchor);
                        tempCursor.endEditBlock();

                        QTextCharFormat f;
                        QTextBlockFormat textBlockFormat;

                        //apply format
                        cursor.beginEditBlock();
                        cursor.setPosition(startIndex, QTextCursor::MoveAnchor);
                        cursor.setPosition(endIndex, QTextCursor::KeepAnchor);
                        cursor.mergeCharFormat(f);
                        cursor.mergeBlockFormat(textBlockFormat);
                        ui->RealTextEdit->mergeCurrentCharFormat(f);
                        ui->RealTextEdit->setTextCursor(cursor);
                        cursor.endEditBlock();

                        //update symbols of the client
                        std::vector<sId> symbolsId = _client->Crdt.localErase(startIndex, endIndex);

                        //Serialize data
                        json j;
                        jsonUtility::to_json_removal_range(j, "REMOVAL_REQUEST", symbolsId);
                        const std::string req = j.dump();

                        //Send data (header and body)
                        _client->sendRequestMsg(req);
                    } else {
                        pos = cursor.position();
                    }

                    //update textedit formats
                    wchar_t c = keyEvent->text().toStdWString().c_str()[0];



                    //update symbols of the client
                    symbol s = _client->Crdt.localInsert(pos, c);

                    //Serialize data
                    json j;
                    jsonUtility::to_json_insertion(j, "INSERTION_REQUEST", s, pos);
                    const std::string req = j.dump();

                    _client->sendRequestMsg(req);
                    return QObject::eventFilter(obj, ev);
                } //******************************************** BACKSPACE *************************************************
                else if (key == Qt::Key_Backspace) {
                    QTextCursor cursor = ui->RealTextEdit->textCursor();
                    int pos = cursor.position();

                    if (cursor.hasSelection()) {
                        int startIndex = cursor.selectionStart();
                        int endIndex = cursor.selectionEnd();

                        /* Update new alignment */
                        cursor.setPosition(startIndex);
                        QTextBlockFormat textBlockFormat;
                        cursor.mergeBlockFormat(textBlockFormat);
                        ui->RealTextEdit->setAlignment(textBlockFormat.alignment());
                        cursor.setPosition(pos);

                        std::vector<sId> symbolsId = _client->Crdt.localErase(startIndex, endIndex);

                        removeCharRequest(symbolsId);
                    } else if (pos > 0) {

                        std::vector<sId> symbolsId = _client->Crdt.localErase(pos - 1, pos);

                        removeCharRequest(symbolsId);
                    }
                    return QObject::eventFilter(obj, ev);
                }
                else if (key == Qt::Key_Delete) {
                    QTextCursor cursor = ui->RealTextEdit->textCursor();
                    int pos = cursor.position();

                    if (cursor.hasSelection()) {
                        int startIndex = cursor.selectionStart();
                        int endIndex = cursor.selectionEnd();

                        /* Update new alignment */
                        cursor.setPosition(cursor.selectionStart());
                        QTextBlockFormat textBlockFormat;
                        cursor.mergeBlockFormat(textBlockFormat);
                        ui->RealTextEdit->setAlignment(textBlockFormat.alignment());
                        cursor.setPosition(pos);


                        //Update symbols of the client
                        std::vector<sId> symbolsId = _client->Crdt.localErase(startIndex, endIndex);

                        removeCharRequest(symbolsId);
                    } else if (pos >= 0 && pos < ui->RealTextEdit->toPlainText().size()) {
                        std::vector<sId> symbolsId = _client->Crdt.localErase(pos, pos + 1);

                        removeCharRequest(symbolsId);
                    }
                    return QObject::eventFilter(obj, ev);
                } //********************************************* ESC ******************************************************
                else if (key == Qt::Key_Escape) {
                    return true; //do not handle ESC
                }
            } else
                return QObject::eventFilter(obj, ev);
            return false; //or return QObject::eventFilter(obj, ev);
        }
    }
    return false; //or return QObject::eventFilter(obj, ev);
}

void NoteBook::on_actionClose_triggered() {
    CloseDocumentRequest();
}

void NoteBook::CloseDocumentRequest() {

    //Get data from the form
    QString user = this->_client->getUsername();
    QByteArray ba_user = user.toLocal8Bit();
    const char *c_user = ba_user.data();
    QString uri = this->_client->getFileURI();
    QByteArray ba_uri = uri.toLocal8Bit();
    const char *c_uri = ba_uri.data();

    //Serialize data
    json j;
    jsonUtility::to_jsonUri(j, "LOGOUTURI_REQUEST", c_user, c_uri);
    const std::string req = j.dump();

    //Send data (header and body)
    _client->sendRequestMsg(req);
}

void NoteBook::showSymbolsAt(int firstIndex, std::vector<symbol> symbols) {
    wchar_t letter;
    int index = firstIndex;
    QTextCursor c = ui->RealTextEdit->textCursor();

    c.beginEditBlock();
            foreach (symbol s, symbols) {
            letter = s.getLetter();
            QTextCharFormat newFormat;
            QTextBlockFormat newBlockFormat;

            int endIndex;
            int pos = index++;
            c.hasSelection() ? endIndex = c.selectionEnd() : endIndex = -90;
            int oldPos = pos < c.position() ? c.position() + 1 : c.position();

            //if user2 insert a char at the end of the selection of user1 -> this can cause extension of user1's selection (that is wrong)
            if (c.hasSelection() && pos == endIndex) {
                int startIndex = c.selectionStart();

                /* Insert (formatted) char */
                c.setPosition(pos);
                c.setCharFormat(newFormat);
                c.insertText(static_cast<QString>(letter));
                c.movePosition(QTextCursor::Right);
                c.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor);
                c.setBlockFormat(newBlockFormat);

                /* Keep current selection */
                c.setPosition(oldPos == startIndex ? endIndex : startIndex, QTextCursor::MoveAnchor);
                c.setPosition(oldPos == startIndex ? startIndex : endIndex, QTextCursor::KeepAnchor);
            } else {
                /* Insert (formatted) char */
                c.setPosition(pos);
                c.setCharFormat(newFormat);
                c.insertText(static_cast<QString>(letter));
                c.movePosition(QTextCursor::Right);
                c.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor);
                c.setBlockFormat(newBlockFormat);
                c.setPosition(oldPos);
            }
        }
    c.endEditBlock();
    ui->RealTextEdit->setTextCursor(c);
}

void NoteBook::showSymbol(std::pair<int, wchar_t> tuple) {
    int pos = tuple.first;
    wchar_t c = tuple.second;
    QTextCharFormat format;
    QTextBlockFormat newBlockFormat;

    QTextCursor cursor = ui->RealTextEdit->textCursor();
    cursor.beginEditBlock();

    int endIndex;
    cursor.hasSelection() ? endIndex = cursor.selectionEnd() : endIndex = -90;
    int oldPos = pos < cursor.position() ? cursor.position() + 1 : cursor.position();

    //if user2 insert a char at the end of the selection of user1 -> this can cause extension of user1's selection (that is wrong)
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
    ui->RealTextEdit->setTextCursor(cursor);

    qDebug() << "Written in pos: " << pos << endl;
    ui->RealTextEdit->setFocus();
}

void NoteBook::eraseSymbols(int startIndex, int endIndex) {
    QTextCursor cursor = ui->RealTextEdit->textCursor();
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
    ui->RealTextEdit->setFocus();
}
void NoteBook::removeCharRequest(const std::vector<sId> &symbolsId) {
    json j;
    jsonUtility::to_json_removal_range(j, "REMOVAL_REQUEST", symbolsId);
    const std::string req = j.dump();
    _client->sendRequestMsg(req);
}
void NoteBook::cursorChangeRequest(int pos) {
    json j;
    jsonUtility::to_json_cursor_change_req(j, "CURSOR_CHANGE_REQUEST", pos);
    const std::string req = j.dump();
    _client->sendRequestMsg(req);
}

void NoteBook::insertCharRangeRequest(int pos, bool cursorHasSelection) noexcept(false) {
    QClipboard *clipboard = QApplication::clipboard();
    const QMimeData *mimeData = clipboard->mimeData();
    QTextCursor cursor = ui->RealTextEdit->textCursor();

    if (mimeData->hasText() && !mimeData->hasImage() && !mimeData->hasUrls() && !mimeData->html().contains("<a href")) {
        /* Get chars from clipboard mimeData */
        int numChars = mimeData->text().size(); //number of chars = number of iterations
        std::wstring str_to_paste = mimeData->text().toStdWString();

        std::vector<symbol> infoSymbols; //temporary vector without symbol pos (it will be used by the process)
        int index;
        wchar_t c;
        int initialPos = pos;
        std::vector<symbol> symbols = _client->Crdt.localInsert(initialPos, infoSymbols);

        //Serialize data
        json j;
        std::vector<json> symFormattingVectorJSON = jsonUtility::fromFormattingSymToJson(symbols);
        jsonUtility::to_json_insertion_range(j, "INSERTIONRANGE_REQUEST", symFormattingVectorJSON, initialPos);
        const std::string req = j.dump();
        _client->sendRequestMsg(req);
    } else {
        qDebug() << "Cannot paste this." << endl;
    }
}
void NoteBook::goodbyeClient() {
    if (_client->getStatus() == false) {
        QMessageBox::warning(nullptr, "Attention",
                             "Cant reach server \n\nApplication needs to be closed");
//        QApplication::exit(-1000);
    }
}