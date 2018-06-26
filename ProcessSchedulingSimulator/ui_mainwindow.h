/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include "scheduleview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTableWidget *dataTable;
    QTableWidget *resultTable;
    QLabel *label;
    QLabel *label_5;
    QPushButton *deleteTask;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *taskName;
    QLabel *label_3;
    QLineEdit *createdTime;
    QLabel *label_4;
    QLineEdit *serveTime;
    QPushButton *addTask;
    ScheduleView *widget;
    QLabel *label_7;
    QSpinBox *slice;
    QLabel *label_6;
    QRadioButton *FCFS;
    QRadioButton *SJF;
    QRadioButton *HRN;
    QPushButton *run;
    QRadioButton *RR;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1010, 614);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        dataTable = new QTableWidget(centralWidget);
        if (dataTable->columnCount() < 3)
            dataTable->setColumnCount(3);
        dataTable->setObjectName(QStringLiteral("dataTable"));
        dataTable->setGeometry(QRect(10, 30, 451, 141));
        dataTable->setSortingEnabled(false);
        dataTable->setColumnCount(3);
        dataTable->horizontalHeader()->setCascadingSectionResizes(false);
        resultTable = new QTableWidget(centralWidget);
        if (resultTable->columnCount() < 4)
            resultTable->setColumnCount(4);
        resultTable->setObjectName(QStringLiteral("resultTable"));
        resultTable->setGeometry(QRect(10, 241, 451, 151));
        resultTable->setColumnCount(4);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 60, 16));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 220, 60, 16));
        deleteTask = new QPushButton(centralWidget);
        deleteTask->setObjectName(QStringLiteral("deleteTask"));
        deleteTask->setGeometry(QRect(470, 90, 71, 32));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 180, 451, 33));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        taskName = new QLineEdit(layoutWidget);
        taskName->setObjectName(QStringLiteral("taskName"));

        horizontalLayout->addWidget(taskName);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        createdTime = new QLineEdit(layoutWidget);
        createdTime->setObjectName(QStringLiteral("createdTime"));

        horizontalLayout->addWidget(createdTime);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout->addWidget(label_4);

        serveTime = new QLineEdit(layoutWidget);
        serveTime->setObjectName(QStringLiteral("serveTime"));

        horizontalLayout->addWidget(serveTime);

        addTask = new QPushButton(layoutWidget);
        addTask->setObjectName(QStringLiteral("addTask"));

        horizontalLayout->addWidget(addTask);

        widget = new ScheduleView(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 420, 451, 151));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 400, 60, 16));
        slice = new QSpinBox(centralWidget);
        slice->setObjectName(QStringLiteral("slice"));
        slice->setGeometry(QRect(520, 290, 48, 20));
        slice->setMinimum(1);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(476, 242, 52, 19));
        FCFS = new QRadioButton(centralWidget);
        FCFS->setObjectName(QStringLiteral("FCFS"));
        FCFS->setGeometry(QRect(475, 260, 58, 20));
        SJF = new QRadioButton(centralWidget);
        SJF->setObjectName(QStringLiteral("SJF"));
        SJF->setGeometry(QRect(480, 311, 48, 20));
        HRN = new QRadioButton(centralWidget);
        HRN->setObjectName(QStringLiteral("HRN"));
        HRN->setGeometry(QRect(480, 330, 53, 20));
        run = new QPushButton(centralWidget);
        run->setObjectName(QStringLiteral("run"));
        run->setGeometry(QRect(470, 360, 68, 32));
        RR = new QRadioButton(centralWidget);
        RR->setObjectName(QStringLiteral("RR"));
        RR->setGeometry(QRect(480, 290, 42, 20));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(560, 10, 431, 571));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1010, 22));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\350\277\233\347\250\213\350\260\203\345\272\246\346\250\241\346\213\237\345\231\250", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\344\273\273\345\212\241\345\272\217\345\210\227", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "\346\211\247\350\241\214\347\273\223\346\236\234", Q_NULLPTR));
        deleteTask->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\350\277\233\347\250\213\345\220\215", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "\345\210\233\345\273\272\346\227\266\351\227\264", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "\346\234\215\345\212\241\346\227\266\351\227\264", Q_NULLPTR));
        addTask->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240\344\273\273\345\212\241", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "\350\260\203\345\272\246\345\233\276", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "\350\260\203\345\272\246\346\226\271\345\274\217", Q_NULLPTR));
        FCFS->setText(QApplication::translate("MainWindow", "FCFS", Q_NULLPTR));
        SJF->setText(QApplication::translate("MainWindow", "SJF", Q_NULLPTR));
        HRN->setText(QApplication::translate("MainWindow", "HRN", Q_NULLPTR));
        run->setText(QApplication::translate("MainWindow", "\350\277\220\350\241\214", Q_NULLPTR));
        RR->setText(QApplication::translate("MainWindow", "RR", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
