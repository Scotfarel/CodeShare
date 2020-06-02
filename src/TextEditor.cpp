#include "headers/TextEditor.h"
#include <QMimeData>
#include <qdebug.h>
#include <QContextMenuEvent>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QRegularExpression>
#include <QPainter>

void TextEditor::insertFromMimeData(const QMimeData* source) {
    if (source->hasText() && !source->hasImage() && !source->hasUrls() && !source->html().contains("<a href")) {
        QString text = source->text();
        QTextCursor cursor = textCursor();
        int startIndex;
        cursor.hasSelection() ? startIndex = cursor.selectionStart() : startIndex = cursor.position();
        cursor.beginEditBlock();
        QString html;
        cursor.insertHtml(html);

        /* Update each block with correct alignment */
        int numChars = source->text().size();

        for (int i = 0; i < numChars; i++) {
            QTextBlockFormat textBlockFormat;
            cursor.setPosition(startIndex++);
            cursor.mergeBlockFormat(textBlockFormat);
        }
        cursor.endEditBlock();
    }
}

void TextEditor::paintEvent(QPaintEvent *event) {
    QTextEdit::paintEvent(event);
    QPainter painter(viewport());
    painter.setRenderHint(QPainter::Antialiasing, true);

    QHash<QString, std::pair<QString, int>>::iterator i;
    for (i = remoteCursors.begin(); i != remoteCursors.end(); ++i) {
        /* Get current info */
        QTextCursor cursor = this->textCursor();
        cursor.setPosition(i.value().second);
        int curFontSize = static_cast<int>(cursor.charFormat().fontPointSize());
        if (cursor.position() == 0) {
            if (this->toPlainText().size() > 0) {
                cursor.movePosition(QTextCursor::Right);
                curFontSize = static_cast<int>(cursor.charFormat().fontPointSize());
                cursor.movePosition(QTextCursor::Left);
            } else {
                curFontSize = static_cast<int>(this->font().pointSize());
            }
        }
        int rectHeight = (curFontSize*30)/14;
        QString username = i.key();
        QColor color = i.value().first;
        QPen pen;
        pen.setColor(color);
        pen.setWidth(2);
        painter.setPen(pen);
        QFontMetrics metrics(cursor.charFormat().font());

        /* Rect for remote line cursor */
        QRect rect = cursorRect(cursor);
        QPoint center = rect.center();
        int offsetHeight = calculateOffsetHeight(curFontSize);
        int offsetY = calculateOffsetY(curFontSize);
        int y = rect.bottom()-(rect.height()/4)-metrics.ascent()+(metrics.descent()/2)*(cursor.charFormat().font().pointSize()/50);
        painter.drawRect(center.x(), y-offsetY, 1, (rectHeight-offsetHeight));

        /* Horizontal rect for username */
        if (showHorizontalRect) {
            QPainterPath path;
            int widthViewport = viewport()->rect().width();
            int finalX = center.x()-2;
            int widthRect = calculateWidthForUsername(username);

            if ((center.x()-2) >= (widthViewport-widthRect))
                finalX = center.x()-2 - (widthRect-5);
            QRectF rectUsername(finalX, y-offsetY-1, widthRect, -19);
            path.addRoundedRect(rectUsername, 2, 2);
            painter.fillPath(path, color);
            painter.drawPath(path);

            /* text for username inside rect */
            QFont font("Helvetica", 10, QFont::Bold, false);
            painter.setPen(QColor(255, 255, 255));
            painter.setFont(font);
            painter.drawText(finalX+1, y-offsetY-6, QString::fromUtf8(qPrintable(username)));
        } else {
            /* Small Rect above cursor */
            QRectF smallRect(center.x()-4, y-offsetY-7, 9, 7);
            painter.fillRect(smallRect, color);
        }
    }
}

int TextEditor::calculateWidthForUsername(QString& username) {
    int startWidth = username.contains('w', Qt::CaseInsensitive) ? 95 : 80;
    int length = username.length();
    int finalVal = (length*startWidth)/8;
    if (finalVal < 22) {
        finalVal += 10;
    } else if (finalVal > 150) {
        finalVal = 150;
        username = username.mid(0, (finalVal*8)/startWidth);
        username.insert(username.length(), "...");
    }
    return finalVal;
}

int TextEditor::calculateOffsetY(int curFontSize) {
    int retVal = 0;
    if (curFontSize > 0 && curFontSize <= 96)
        retVal = 0;
    else if (curFontSize > 96 && curFontSize <= 140)
        retVal = 10;
    else if (curFontSize > 140 && curFontSize <= 160)
        retVal = 40;
    else if (curFontSize > 160 && curFontSize <= 180)
        retVal = 45;
    else if (curFontSize > 180 && curFontSize <= 190)
        retVal = 48;
    else if (curFontSize > 190 && curFontSize <= 199)
        retVal = 51;
    else if (curFontSize == 200)
        retVal = 80;
    return retVal;
}

int TextEditor::calculateOffsetHeight(int curFontSize) {
    int retVal;
    int base = (curFontSize*3)/14;
    if (curFontSize > 0 && curFontSize <= 30)
        retVal = base-2;
    else if (curFontSize > 30 && curFontSize <= 48)
        retVal = base;
    else if (curFontSize > 48 && curFontSize <= 60)
        retVal = base+10;
    else if (curFontSize > 60 && curFontSize <= 78)
        retVal = base+17;
    else if (curFontSize > 78 && curFontSize <= 96)
        retVal = base+22;
    else if (curFontSize > 96 && curFontSize <= 99)
        retVal = base+9;
    else if (curFontSize > 99 && curFontSize <= 116)
        retVal = base+25;
    else if (curFontSize > 116 && curFontSize <= 136)
        retVal = base+35;
    else if (curFontSize > 136 && curFontSize <= 140)
        retVal = base+45;
    else if (curFontSize > 140 && curFontSize <= 149)
        retVal = base+19;
    else if (curFontSize > 149 && curFontSize <= 170)
        retVal = base+40;
    else if (curFontSize > 170 && curFontSize <= 190)
        retVal = base+48;
    else if (curFontSize > 190 && curFontSize <= 199)
        retVal = base+54;
    else if (curFontSize == 200)
        retVal = base+62;
    else
        retVal = 0;
    return retVal;
}

void TextEditor::addRemoteCursor(QString username, std::pair<QString, int> colorAndPos) {
    this->remoteCursors.insert(username, std::make_pair(colorAndPos.first, colorAndPos.second));
}

void TextEditor::removeRemoteCursor(std::string username) {
    remoteCursors.remove(QString::fromStdString(username));
    this->viewport()->update();
}

void TextEditor::changeRemoteCursor(std::string username, std::string color, int pos) {
    QString col = QString::fromStdString(color);
    col[1] = 'f';
    col[2] = 'f';
    addRemoteCursor(QString::fromStdString(username), std::make_pair(col, pos));
    showHorizontalRect = true;
    timer.setSingleShot(true);
    timer.start(3000);
    this->viewport()->update();
}

void TextEditor::hideHorizontalRect() {
    showHorizontalRect = false;
    this->viewport()->update();
}
