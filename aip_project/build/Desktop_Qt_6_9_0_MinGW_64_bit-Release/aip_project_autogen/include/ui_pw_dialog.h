/********************************************************************************
** Form generated from reading UI file 'pw_dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PW_DIALOG_H
#define UI_PW_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_PwDialog
{
public:
    QPushButton *set_pw;
    QLineEdit *pw_text;
    QLabel *label;

    void setupUi(QDialog *PwDialog)
    {
        if (PwDialog->objectName().isEmpty())
            PwDialog->setObjectName("PwDialog");
        PwDialog->resize(400, 300);
        set_pw = new QPushButton(PwDialog);
        set_pw->setObjectName("set_pw");
        set_pw->setGeometry(QRect(130, 240, 131, 29));
        pw_text = new QLineEdit(PwDialog);
        pw_text->setObjectName("pw_text");
        pw_text->setGeometry(QRect(90, 180, 211, 26));
        label = new QLabel(PwDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 60, 351, 81));

        retranslateUi(PwDialog);

        QMetaObject::connectSlotsByName(PwDialog);
    } // setupUi

    void retranslateUi(QDialog *PwDialog)
    {
        PwDialog->setWindowTitle(QCoreApplication::translate("PwDialog", "Dialog", nullptr));
        set_pw->setText(QCoreApplication::translate("PwDialog", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\264\320\270\321\202\321\214", nullptr));
        label->setText(QCoreApplication::translate("PwDialog", "\320\224\320\276\320\261\321\200\320\276 \320\277\320\276\320\266\320\260\320\273\320\276\320\262\320\260\321\202\321\214! \320\227\320\260\320\264\320\260\320\271\321\202\320\265 \320\277\320\260\321\200\320\276\320\273\321\214 \320\264\320\273\321\217 \320\262\321\205\320\276\320\264\320\260.\n"
"\320\236\320\261\321\217\320\267\320\260\321\202\320\265\320\273\321\214\320\275\320\276 \320\267\320\260\320\277\320\276\320\274\320\275\320\270\321\202\320\265 \320\270\320\273\320\270 \320\267\320\260\320\277\320\270\321\210\320\270\321\202\320\265 \320\265\320\263\320\276.\n"
"\320\222 \320\261\321\203\320\264\321\203\321\211\320\265\320\274 \320\222\321\213 \320\275\320\265 \321\201\320\274\320\276\320\266\320\265\321\202\320\265 \320\265\320\263\320\276 \320\270\320\267\320\274\320\265\320\275\320\270\321\202\321\214 \320\270\320\273\320\270\n"
"\320\262\320\276\321\201\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PwDialog: public Ui_PwDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PW_DIALOG_H
