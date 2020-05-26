#ifndef HEADERS_MYQTEXTEDIT_H_
#define HEADERS_MYQTEXTEDIT_H_
#include <QTextEdit>
#include <QTimer>

class MyQTextEdit : public QTextEdit {
    Q_OBJECT
 public:
    explicit MyQTextEdit(QWidget* parent) : QTextEdit(parent) {}
    void insertFromMimeData(const QMimeData * source) override;
    void addRemoteCursor(QString username, std::pair<QString, int> colorAndPos);
    QTimer timer;

 private:
    QVector<std::pair<int, int>> alignments;
    bool showHorizontalRect = false;
    QHash<QString, std::pair<QString, int>> remoteCursors;
    int calculateOffsetHeight(int curFontSize);
    int calculateOffsetY(int curFontSize);
    int calculateWidthForUsername(QString& username);

 protected:
    void paintEvent(QPaintEvent * event);

 public slots:
    void removeRemoteCursor(std::string username);
    void changeRemoteCursor(std::string username, std::string color, int pos);
    void hideHorizontalRect();
};
#endif  // HEADERS_MYQTEXTEDIT_H_
