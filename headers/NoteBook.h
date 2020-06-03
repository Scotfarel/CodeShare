#ifndef HEADERS_NOTEBOOK_H_
#define HEADERS_NOTEBOOK_H_

#include <QMainWindow>
#include <QTextCursor>
#include <QComboBox>
#include <QMetaType>
#include "headers/jsonTypes.h"
#include "headers/Message.h"
#include "ClientConnector.h"
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
    explicit NoteBook(ClientConnector* client, QWidget *parent = nullptr);
    ~NoteBook();
private slots:
    void on_RealTextEdit_textChanged();
    bool eventFilter(QObject *obj, QEvent *ev);
    void end_session();

 signals:
    void closeEditor();

public slots:
    /* Отображение символа */
    void show_sym(std::pair<int, wchar_t> tuple);
    /* Удаление видимого символа */
    void erase_sym(int startIndex, int endIndex);
    /* Отображение символа на конкретной позиции */
    void show_sym_in_pos(int startIndex, std::vector<Symbol> symbols);

 private:
    Ui::NoteBook *UI;
    ClientConnector *_client;
    /* Настройки QT редактора */
    void setupTextEdit();
    void setupFirstLetter();
    /* Отправка запроса на вставку нескольких символов */
    void insert_range_req(int pos, bool cursorHasSelection);
    /* Отправка запроса на изменение курсора */
    void cursor_change_req(int pos);
    /* Отправка запроса на удаление символа */
    void remove_req(const std::vector<int_pair>& symbolsId);

};
#endif  // HEADERS_NOTEBOOK_H_
