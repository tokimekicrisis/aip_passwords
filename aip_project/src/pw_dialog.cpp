#include "ui/pw_dialog.h"

#include <QMessageBox>
#include <QSettings>
#include <QCryptographicHash>

/**
 * Конструктор диалога входа в приложение.
 * Если вход не первый, текст диалога меняется
 * на "Введите пароль", иначе - как в .ui файле.
 *
 * @param first_run Первый/не первый запуск приложения.
 * @param parent Родительский виджет.
 */
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

/**
 * Деструктор диалога.
 */
PwDialog::~PwDialog()
{
  delete ui;
}

/**
 * Возвращает введенный пользователем пароль.
 *
 * @return QString Пароль.
 */
QString PwDialog::getPassword() const {
  return ui->pw_text->text();
}

/**
 * Принимает введенный пользователем пароль,
 * если он не пустой.
 */
void PwDialog::onSetPwClicked() {
  if (ui->pw_text->text().isEmpty()) {
    QMessageBox::warning(this, "Ошибка", "Пароль не может быть пустым.");
    return;
  }
  accept();
}
