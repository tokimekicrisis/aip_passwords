#include "ui/main_window.h"
#include "ui/pw_dialog.h"
#include "database/database.h"

#include <QApplication>
#include <QCryptographicHash>
#include <QMessageBox>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Database db("passwords.db");
    bool first_run = db.isFirstRun();
    bool logged_in = false;

    while (!logged_in) {
        PwDialog dialog(first_run);

        if (dialog.exec() == QDialog::Accepted) {
            QString password = dialog.getPassword();
            if (first_run) {
                if (db.setMaster(password)) {
                    logged_in = true;
                    QMessageBox::information(nullptr, "Успех", "Пароль успешно установлен!");
                }
            } else {
                if (db.verifyMaster(password)) {
                    logged_in = true;
                } else {
                    QMessageBox::warning(nullptr, "Ошибка", "Неверный пароль!");
                }
            }
        } else {
            return 0;
        }
    }

    MainWindow w(&db);
    w.show();
    return a.exec();
}
