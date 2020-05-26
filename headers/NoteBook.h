#ifndef HEADERS_NOTEBOOK_H_
#define HEADERS_NOTEBOOK_H_

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
namespace Ui {class NoteBook;}

struct OperationNotSupported : public std::exception {
    const char * what() const noexcept override {
        return "Operation not supported";
    }
};
typedef std::map<std::string, std::pair<std::string, bool>> myCollabColorsMap;

class NoteBook : public QMainWindow {
    Q_OBJECT

 public:
    explicit NoteBook(myClient* client, QWidget *parent = nullptr);
    ~NoteBook();

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

 private:
    Ui::NoteBook *ui;
    myClient *_client;
    void setupTextEdit();
    void setupFirstLetter();
    void insertCharRangeRequest(int pos, bool cursorHasSelection);
    void cursorChangeRequest(int pos);
    void removeCharRequest(const std::vector<sId>& symbolsId);
};
#endif  // HEADERS_NOTEBOOK_H_
