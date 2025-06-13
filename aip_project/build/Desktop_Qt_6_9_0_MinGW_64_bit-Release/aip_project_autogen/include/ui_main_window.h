/********************************************************************************
** Form generated from reading UI file 'main_window.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_WINDOW_H
#define UI_MAIN_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTableView *pws_table;
    QPushButton *edit_btn;
    QPushButton *search_btn;
    QCheckBox *num_cb;
    QCheckBox *punct_cb;
    QLabel *gen_label;
    QLineEdit *search_bar;
    QLineEdit *gen_display;
    QPushButton *generate_btn;
    QPushButton *add_btn;
    QSpinBox *pw_len;
    QLabel *label;
    QPushButton *del_btn;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(806, 568);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        pws_table = new QTableView(centralwidget);
        pws_table->setObjectName("pws_table");
        pws_table->setGeometry(QRect(20, 90, 461, 401));
        edit_btn = new QPushButton(centralwidget);
        edit_btn->setObjectName("edit_btn");
        edit_btn->setGeometry(QRect(190, 500, 141, 31));
        search_btn = new QPushButton(centralwidget);
        search_btn->setObjectName("search_btn");
        search_btn->setGeometry(QRect(390, 50, 91, 31));
        num_cb = new QCheckBox(centralwidget);
        num_cb->setObjectName("num_cb");
        num_cb->setGeometry(QRect(510, 190, 201, 20));
        punct_cb = new QCheckBox(centralwidget);
        punct_cb->setObjectName("punct_cb");
        punct_cb->setGeometry(QRect(510, 220, 231, 20));
        gen_label = new QLabel(centralwidget);
        gen_label->setObjectName("gen_label");
        gen_label->setGeometry(QRect(580, 150, 151, 16));
        search_bar = new QLineEdit(centralwidget);
        search_bar->setObjectName("search_bar");
        search_bar->setGeometry(QRect(20, 50, 361, 31));
        gen_display = new QLineEdit(centralwidget);
        gen_display->setObjectName("gen_display");
        gen_display->setGeometry(QRect(500, 360, 281, 31));
        generate_btn = new QPushButton(centralwidget);
        generate_btn->setObjectName("generate_btn");
        generate_btn->setGeometry(QRect(580, 310, 131, 28));
        add_btn = new QPushButton(centralwidget);
        add_btn->setObjectName("add_btn");
        add_btn->setGeometry(QRect(20, 500, 101, 31));
        pw_len = new QSpinBox(centralwidget);
        pw_len->setObjectName("pw_len");
        pw_len->setGeometry(QRect(730, 260, 42, 26));
        pw_len->setMaximum(30);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(510, 260, 171, 31));
        del_btn = new QPushButton(centralwidget);
        del_btn->setObjectName("del_btn");
        del_btn->setGeometry(QRect(340, 500, 141, 31));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        edit_btn->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214...", nullptr));
        search_btn->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272", nullptr));
        num_cb->setText(QCoreApplication::translate("MainWindow", "\320\230\321\201\320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\321\214 \321\206\320\270\321\204\321\200\321\213", nullptr));
        punct_cb->setText(QCoreApplication::translate("MainWindow", "\320\230\321\201\320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\321\214 \321\201\320\277\320\265\321\206\321\201\320\270\320\274\320\262\320\276\320\273\321\213", nullptr));
        gen_label->setText(QCoreApplication::translate("MainWindow", "\320\223\320\265\320\275\320\265\321\200\320\260\321\202\320\276\321\200 \320\277\320\260\321\200\320\276\320\273\320\265\320\271", nullptr));
        generate_btn->setText(QCoreApplication::translate("MainWindow", "\320\241\320\263\320\265\320\275\320\265\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        add_btn->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214...", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \321\201\320\270\320\274\320\262\320\276\320\273\320\276\320\262", nullptr));
        del_btn->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW_H
