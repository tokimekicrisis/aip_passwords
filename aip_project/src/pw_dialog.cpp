#include "ui/pw_dialog.h"
#include <QMessageBox>

PwDialog::PwDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PwDialog) {
    ui->setupUi(this);

    ui->pw_text->setEchoMode(QLineEdit::Password);
    connect(ui->set_pw, &QPushButton::clicked, this, &PwDialog::onSetPwClicked);
}

PwDialog::~PwDialog()
{
    delete ui;
}

QString PwDialog::getPassword() const {
    return ui->pw_text->text();
}

void PwDialog::onSetPwClicked() {
    if (ui->pw_text->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пароль не может быть пустым.");
        return;
    }
    accept();
}
