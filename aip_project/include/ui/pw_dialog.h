#ifndef PW_DIALOG_H
#define PW_DIALOG_H

#include "ui_pw_dialog.h"

#include <QDialog>

/**
 * Диалоговое окно для ввода пароля.
 * В зависимости от того, первый это вход или нет,
 * устанавливает пароль либо совершает вход в приложение.
 */
class PwDialog : public QDialog
{
  Q_OBJECT

public:
  PwDialog(bool first_run, QWidget *parent = nullptr);
  ~PwDialog();

  QString getPassword() const;

private slots:
  void onSetPwClicked();

private:
  Ui::PwDialog *ui;
  bool first_run;
};

#endif // PW_DIALOG_H
