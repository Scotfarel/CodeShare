#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>
#include <QTextCursor>
#include <QComboBox>
#include <QMetaType>
#include "headers/jsonUtility.h"
#include "headers/message.h"
#include "myClient.h"
#include "qlistwidget.h"
#include <QtGui>
#include <QWidget>
class QEvent;
namespace Ui {class EditorWindow;}

struct OperationNotSupported : public std::exception {
    const char * what () const noexcept override {
        return "Operation not supported";
    }
};
typedef std::map<std::string, std::pair<std::string,bool>> myCollabColorsMap;

class EditorWindow : public QMainWindow {
    Q_OBJECT

public:
    EditorWindow(myClient* client, QWidget *parent = nullptr);
    ~EditorWindow();

private slots:
    void on_RealTextEdit_textChanged();


    bool eventFilter(QObject *obj, QEvent *ev);

    void on_actionClose_triggered();
    void CloseDocumentRequest();

    void goodbyeClient();

signals:
    void closeEditor();

public slots:
    void showSymbol(std::pair<int, wchar_t> tuple);
    void eraseSymbols(int startIndex, int endIndex);
    void showSymbolsAt(int startIndex, std::vector<symbol> symbols);
    void LoginProcedure();

private:
    Ui::EditorWindow *ui;
    myClient *_client;
    QString docName = _client->getFilename().toLatin1(); //toLatin1 accept accented chars
    void setupTextEdit();
    void setupFirstLetter();
    /* Requests */
    void insertCharRangeRequest(int pos, bool cursorHasSelection);
    void cursorChangeRequest(int pos);
    void removeCharRequest(const std::vector<sId>& symbolsId);
};
#endif // EDITORWINDOW_H
