/********************************************************************************
** Form generated from reading UI file 'NoteBook.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef HEADERS_UI_NOTEBOOK_H_
#define HEADERS_UI_NOTEBOOK_H_

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <headers/MyQTextEdit.h>

QT_BEGIN_NAMESPACE

class Ui_NoteBook {
 public:
    QAction *actionNew;
    QAction *actionSave;
    QAction *actionFullscreen;
    QAction *actionAbout;
    QAction *actionClose;
    QAction *actionInvita_tramite_URI;
    QAction *actionEsporta_come_PDF;
    QAction *actionRinomina;
    QAction *actionDark_Mode;
    QAction *actionCollaboratori;
    QAction *actionGrassetto;
    QAction *actionCorsivo;
    QAction *actionSottolineato;
    QAction *actionEsci;
    QAction *actionSeleziona_Tutto;
    QAction *actionToolbar;
    QAction *actionOpzioni;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QFrame *editorFrame;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *verticalLayout_5;
    MyQTextEdit *RealTextEdit;
    QFrame *line;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_7;
    QLabel *labelUser;
    QSpacerItem *horizontalSpacer;
    QFrame *line_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_7;
    QFrame *line_3;
    QSpacerItem *verticalSpacer_8;
    QSpacerItem *verticalSpacer_9;

    void setupUi(QMainWindow *NoteBook) {
        if (NoteBook->objectName().isEmpty())
            NoteBook->setObjectName(QString::fromUtf8("NoteBook"));
        NoteBook->resize(950, 604);
        NoteBook->setMinimumSize(QSize(950, 500));
        actionNew = new QAction(NoteBook);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionSave = new QAction(NoteBook);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/Editor/save(1).png"), QSize(), QIcon::Normal, QIcon::On);
        actionSave->setIcon(icon);
        actionFullscreen = new QAction(NoteBook);
        actionFullscreen->setObjectName(QString::fromUtf8("actionFullscreen"));
        actionFullscreen->setCheckable(true);
        actionAbout = new QAction(NoteBook);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionClose = new QAction(NoteBook);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        actionInvita_tramite_URI = new QAction(NoteBook);
        actionInvita_tramite_URI->setObjectName(QString::fromUtf8("actionInvita_tramite_URI"));
        actionEsporta_come_PDF = new QAction(NoteBook);
        actionEsporta_come_PDF->setObjectName(QString::fromUtf8("actionEsporta_come_PDF"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/image/Editor/save(1).png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEsporta_come_PDF->setIcon(icon1);
        actionRinomina = new QAction(NoteBook);
        actionRinomina->setObjectName(QString::fromUtf8("actionRinomina"));
        actionDark_Mode = new QAction(NoteBook);
        actionDark_Mode->setObjectName(QString::fromUtf8("actionDark_Mode"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/image/Editor/DarkMoon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDark_Mode->setIcon(icon2);
        actionCollaboratori = new QAction(NoteBook);
        actionCollaboratori->setObjectName(QString::fromUtf8("actionCollaboratori"));
        actionGrassetto = new QAction(NoteBook);
        actionGrassetto->setObjectName(QString::fromUtf8("actionGrassetto"));
        actionGrassetto->setCheckable(false);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/image/Editor/v2bold.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionGrassetto->setIcon(icon3);
        actionCorsivo = new QAction(NoteBook);
        actionCorsivo->setObjectName(QString::fromUtf8("actionCorsivo"));
        actionCorsivo->setCheckable(false);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/image/Editor/v2italic.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCorsivo->setIcon(icon4);
        actionSottolineato = new QAction(NoteBook);
        actionSottolineato->setObjectName(QString::fromUtf8("actionSottolineato"));
        actionSottolineato->setCheckable(false);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/image/Editor/v2underline.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSottolineato->setIcon(icon5);
        actionEsci = new QAction(NoteBook);
        actionEsci->setObjectName(QString::fromUtf8("actionEsci"));
        actionSeleziona_Tutto = new QAction(NoteBook);
        actionSeleziona_Tutto->setObjectName(QString::fromUtf8("actionSeleziona_Tutto"));
        actionToolbar = new QAction(NoteBook);
        actionToolbar->setObjectName(QString::fromUtf8("actionToolbar"));
        actionOpzioni = new QAction(NoteBook);
        actionOpzioni->setObjectName(QString::fromUtf8("actionOpzioni"));
        centralwidget = new QWidget(NoteBook);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setMinimumSize(QSize(950, 500));
        centralwidget->setStyleSheet(QString::fromUtf8("#centralwidget{\n"
"background: url(:/image/Editor/sfondo.png);\n"
"}"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetFixedSize);
        editorFrame = new QFrame(centralwidget);
        editorFrame->setObjectName(QString::fromUtf8("editorFrame"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(editorFrame->sizePolicy().hasHeightForWidth());
        editorFrame->setSizePolicy(sizePolicy);
        editorFrame->setMinimumSize(QSize(821, 20));
        QFont font;
        font.setFamily(QString::fromUtf8("Calibri"));
        font.setPointSize(14);
        editorFrame->setFont(font);
        editorFrame->setStyleSheet(QString::fromUtf8(""));
        editorFrame->setFrameShape(QFrame::StyledPanel);
        editorFrame->setFrameShadow(QFrame::Raised);
        editorFrame->setMidLineWidth(0);
        verticalLayout_3 = new QVBoxLayout(editorFrame);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayout_5->setContentsMargins(0, -1, -1, -1);

        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(5);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_10->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout_10->setContentsMargins(40, 5, 0, 10);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(14);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 5, 35, -1);
        RealTextEdit = new MyQTextEdit(editorFrame);
        RealTextEdit->setObjectName(QString::fromUtf8("RealTextEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(RealTextEdit->sizePolicy().hasHeightForWidth());
        RealTextEdit->setSizePolicy(sizePolicy1);
        RealTextEdit->setMinimumSize(QSize(500, 0));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Times New Roman"));
        font1.setPointSize(14);
        font1.setBold(false);
        font1.setWeight(50);
        font1.setStrikeOut(false);
        RealTextEdit->setFont(font1);
        RealTextEdit->setContextMenuPolicy(Qt::CustomContextMenu);
        RealTextEdit->setStyleSheet(QString::fromUtf8(" #RealTextEdit{  \n"
"background: #FFFFFF; \n"
"border-left: 2px solid #404040\n"
";}"));

        verticalLayout_5->addWidget(RealTextEdit);


        horizontalLayout_10->addLayout(verticalLayout_5);

        line = new QFrame(editorFrame);
        line->setObjectName(QString::fromUtf8("line"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy2);
        line->setMinimumSize(QSize(5, 0));
        line->setMaximumSize(QSize(5, 16777215));
        line->setStyleSheet(QString::fromUtf8("border:none;\n"
"background-color: lightgrey;\n"
"\n"
""));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_10->addWidget(line);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, -1, 0, -1);
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(10);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        labelUser = new QLabel(editorFrame);
        labelUser->setObjectName(QString::fromUtf8("labelUser"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(labelUser->sizePolicy().hasHeightForWidth());
        labelUser->setSizePolicy(sizePolicy3);
        labelUser->setMinimumSize(QSize(0, 40));
        labelUser->setMaximumSize(QSize(16777215, 40));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Calibri"));
        font2.setPointSize(18);
        font2.setBold(true);
        font2.setWeight(75);
        labelUser->setFont(font2);
        labelUser->setLayoutDirection(Qt::LeftToRight);
        labelUser->setStyleSheet(QString::fromUtf8("#labelCollab{\n"
"	background-color:transparent;\n"
"	color: #505050;\n"
"	border-bottom: 2px solid lightgrey;\n"
"}"));
        labelUser->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(labelUser);

        horizontalSpacer = new QSpacerItem(50, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_7);

        line_2 = new QFrame(editorFrame);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setMinimumSize(QSize(0, 1));
        line_2->setMaximumSize(QSize(16777215, 1));
        line_2->setStyleSheet(QString::fromUtf8("border:none;\n"
"background-color: lightgrey;\n"
"\n"
""));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        label = new QLabel(editorFrame);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Calibri"));
        font3.setPointSize(12);
        font3.setBold(true);
        font3.setWeight(75);
        label->setFont(font3);
        label->setStyleSheet(QString::fromUtf8("color:grey;"));

        verticalLayout->addWidget(label);

        label_2 = new QLabel(editorFrame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font3);
        label_2->setStyleSheet(QString::fromUtf8("color:grey;"));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(editorFrame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font3);
        label_3->setStyleSheet(QString::fromUtf8("color:grey;"));

        verticalLayout->addWidget(label_3);

        verticalSpacer_3 = new QSpacerItem(20, 6, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer_3);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout->addItem(verticalSpacer_5);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer);

        verticalSpacer_7 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer_7);

        line_3 = new QFrame(editorFrame);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setMinimumSize(QSize(0, 1));
        line_3->setMaximumSize(QSize(16777215, 1));
        line_3->setStyleSheet(QString::fromUtf8("border:none;\n"
"background-color: lightgrey;\n"
"\n"
""));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);

        verticalSpacer_8 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer_8);

        verticalSpacer_9 = new QSpacerItem(20, 6, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer_9);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_4->addLayout(horizontalLayout);


        horizontalLayout_10->addLayout(verticalLayout_4);


        verticalLayout_3->addLayout(horizontalLayout_10);


        horizontalLayout_2->addWidget(editorFrame);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        NoteBook->setCentralWidget(centralwidget);

        retranslateUi(NoteBook);

        QMetaObject::connectSlotsByName(NoteBook);
    }  // setupUi

    void retranslateUi(QMainWindow *NoteBook) {
        NoteBook->setWindowTitle(QApplication::translate("NoteBook", "MainWindow", nullptr));
        actionNew->setText(QApplication::translate("NoteBook", "Nuovo Documento", nullptr));
#ifndef QT_NO_SHORTCUT
        actionNew->setShortcut(QApplication::translate("NoteBook", "Ctrl+N", nullptr));
#endif  // QT_NO_SHORTCUT
        actionSave->setText(QApplication::translate("NoteBook", "Salva", nullptr));
#ifndef QT_NO_SHORTCUT
        actionSave->setShortcut(QApplication::translate("NoteBook", "Ctrl+S", nullptr));
#endif  // QT_NO_SHORTCUT
        actionFullscreen->setText(QApplication::translate("NoteBook", "Schermo Intero", nullptr));
#ifndef QT_NO_TOOLTIP
        actionFullscreen->setToolTip(QApplication::translate("NoteBook", "Schermo Intero", nullptr));
#endif  // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionFullscreen->setShortcut(QApplication::translate("NoteBook", "Ctrl+F11", nullptr));
#endif  // QT_NO_SHORTCUT
        actionAbout->setText(QApplication::translate("NoteBook", "?", nullptr));
#ifndef QT_NO_SHORTCUT
        actionAbout->setShortcut(QApplication::translate("NoteBook", "Ctrl+H", nullptr));
#endif  // QT_NO_SHORTCUT
        actionClose->setText(QApplication::translate("NoteBook", "Chiudi Documento", nullptr));
#ifndef QT_NO_SHORTCUT
        actionClose->setShortcut(QApplication::translate("NoteBook", "Ctrl+Q", nullptr));
#endif  // QT_NO_SHORTCUT
        actionInvita_tramite_URI->setText(QApplication::translate("NoteBook", "Invita tramite URI", nullptr));
        actionEsporta_come_PDF->setText(QApplication::translate("NoteBook", "Esporta come PDF", nullptr));
#ifndef QT_NO_SHORTCUT
        actionEsporta_come_PDF->setShortcut(QApplication::translate("NoteBook", "Ctrl+S", nullptr));
#endif  // QT_NO_SHORTCUT
        actionRinomina->setText(QApplication::translate("NoteBook", "Rinomina", nullptr));
#ifndef QT_NO_SHORTCUT
        actionRinomina->setShortcut(QApplication::translate("NoteBook", "Ctrl+R", nullptr));
#endif  // QT_NO_SHORTCUT
        actionDark_Mode->setText(QApplication::translate("NoteBook", "Modalit\303\240 Notte", nullptr));
#ifndef QT_NO_TOOLTIP
        actionDark_Mode->setToolTip(QApplication::translate("NoteBook", "Modalit\303\240 Notte", nullptr));
#endif  // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionDark_Mode->setShortcut(QApplication::translate("NoteBook", "Ctrl+D", nullptr));
#endif  // QT_NO_SHORTCUT
        actionCollaboratori->setText(QApplication::translate("NoteBook", "Nascondi Collaboratori", nullptr));
        actionGrassetto->setText(QApplication::translate("NoteBook", "Grassetto", nullptr));
#ifndef QT_NO_SHORTCUT
        actionGrassetto->setShortcut(QApplication::translate("NoteBook", "Ctrl+B", nullptr));
#endif  // QT_NO_SHORTCUT
        actionCorsivo->setText(QApplication::translate("NoteBook", "Corsivo", nullptr));
#ifndef QT_NO_SHORTCUT
        actionCorsivo->setShortcut(QApplication::translate("NoteBook", "Ctrl+I", nullptr));
#endif  // QT_NO_SHORTCUT
        actionSottolineato->setText(QApplication::translate("NoteBook", "Sottolineato", nullptr));
#ifndef QT_NO_SHORTCUT
        actionSottolineato->setShortcut(QApplication::translate("NoteBook", "Ctrl+U", nullptr));
#endif  // QT_NO_SHORTCUT
        actionEsci->setText(QApplication::translate("NoteBook", "Esci", nullptr));
#ifndef QT_NO_SHORTCUT
        actionEsci->setShortcut(QApplication::translate("NoteBook", "Ctrl+Shift+Q", nullptr));
#endif  // QT_NO_SHORTCUT
        actionSeleziona_Tutto->setText(QApplication::translate("NoteBook", "Seleziona Tutto", nullptr));
#ifndef QT_NO_SHORTCUT
        actionSeleziona_Tutto->setShortcut(QApplication::translate("NoteBook", "Ctrl+A", nullptr));
#endif  // QT_NO_SHORTCUT
        actionToolbar->setText(QApplication::translate("NoteBook", "Toolbar", nullptr));
#ifndef QT_NO_SHORTCUT
        actionToolbar->setShortcut(QApplication::translate("NoteBook", "Ctrl+M", nullptr));
#endif  // QT_NO_SHORTCUT
        actionOpzioni->setText(QApplication::translate("NoteBook", "Opzioni", nullptr));
#ifndef QT_NO_SHORTCUT
        actionOpzioni->setShortcut(QApplication::translate("NoteBook", "Ctrl+O", nullptr));
#endif  // QT_NO_SHORTCUT
        labelUser->setText(QApplication::translate("NoteBook", "CURRENT USER", nullptr));
        label->setText(QApplication::translate("NoteBook", "Caratteri: 0", nullptr));
        label_2->setText(QApplication::translate("NoteBook", "Parole: 0", nullptr));
        label_3->setText(QApplication::translate("NoteBook", "Linee: 0", nullptr));
    }  // retranslateUi
};

namespace Ui {
    class NoteBook: public Ui_NoteBook {};
}  // namespace Ui

QT_END_NAMESPACE

#endif  // HEADERS_UI_NOTEBOOK_H_
