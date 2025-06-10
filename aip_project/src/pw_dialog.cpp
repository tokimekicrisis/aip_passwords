#include "ui/pw_dialog.h"

#include <QMessageBox>
#include <QSettings>
#include <QCryptographicHash>

PwDialog::PwDialog(bool first_run, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PwDialog),
    first_run(first_run) {
    ui->setupUi(this);

    setWindowTitle("Вход");
    if (!first_run) {
        ui->label->setText("Введите пароль:");
    }

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
