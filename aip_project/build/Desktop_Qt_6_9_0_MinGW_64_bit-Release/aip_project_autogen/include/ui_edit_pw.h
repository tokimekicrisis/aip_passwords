/********************************************************************************
** Form generated from reading UI file 'edit_pw.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDIT_PW_H
#define UI_EDIT_PW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_Dialog2
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *site;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *pw;
    QLabel *label_3;
    QLineEdit *cat;
    QLabel *label_4;
    QLineEdit *comm;

    void setupUi(QDialog *Dialog2)
    {
        if (Dialog2->objectName().isEmpty())
            Dialog2->setObjectName("Dialog2");
        Dialog2->resize(465, 276);
        buttonBox = new QDialogButtonBox(Dialog2);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(100, 230, 341, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        site = new QLineEdit(Dialog2);
        site->setObjectName("site");
        site->setGeometry(QRect(240, 20, 201, 31));
        label = new QLabel(Dialog2);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 25, 81, 21));
        label_2 = new QLabel(Dialog2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 75, 81, 21));
        pw = new QLineEdit(Dialog2);
        pw->setObjectName("pw");
        pw->setGeometry(QRect(240, 70, 201, 31));
        label_3 = new QLabel(Dialog2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 125, 81, 21));
        cat = new QLineEdit(Dialog2);
        cat->setObjectName("cat");
        cat->setGeometry(QRect(240, 120, 201, 31));
        label_4 = new QLabel(Dialog2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(30, 175, 121, 21));
        comm = new QLineEdit(Dialog2);
        comm->setObjectName("comm");
        comm->setGeometry(QRect(240, 170, 201, 31));

        retranslateUi(Dialog2);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Dialog2, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Dialog2, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Dialog2);
    } // setupUi

    void retranslateUi(QDialog *Dialog2)
    {
        Dialog2->setWindowTitle(QCoreApplication::translate("Dialog2", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        label->setText(QCoreApplication::translate("Dialog2", "\320\241\320\260\320\271\321\202", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog2", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        label_3->setText(QCoreApplication::translate("Dialog2", "\320\232\320\260\321\202\320\265\320\263\320\276\321\200\320\270\321\217", nullptr));
        label_4->setText(QCoreApplication::translate("Dialog2", "\320\232\320\276\320\274\320\274\320\265\320\275\321\202\320\260\321\200\320\270\320\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog2: public Ui_Dialog2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDIT_PW_H
