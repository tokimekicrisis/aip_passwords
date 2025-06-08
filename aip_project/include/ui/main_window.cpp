#include "main_window.h"
#include <QString>
#include <QRandomGenerator>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->generate_btn, &QPushButton::clicked,
            this, &MainWindow::onGenerateBtnClicked);
}

/**
 * Генерирует случайный пароль данной длины.
 * По желанию пользователя может включать или не включать цифры и спецсимволы.
 *
 * @param len Длина пароля.
 * @param digits Включение цифр (да/нет).
 * @param punct Включение цифр (да/нет).
 * @return std::string Пароль.
 */
std::string MainWindow::genPassword(const int len, const bool digits, const bool punct)
{
    std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                             "abcdefghijklmnopqrstuvwxyz";

    if (digits) {
        characters += "0123456789";
    }
    if (punct) {
        characters += "!@#$^&*()_-+=%:;/.,?";
    }

    std::string pw;
    pw.reserve(len);

    QRandomGenerator *generator = QRandomGenerator::global();

    for (int i = 0; i < len; ++i) {
        pw += characters[generator->bounded(characters.length())];
    }

    return pw;
}

/**
 * Связывает genPassword и нажатие соответствующей кнопки.
 */
void MainWindow::onGenerateBtnClicked()
{
    int length = ui->pw_len->value();
    bool digits = ui->num_cb->isChecked();
    bool punct = ui->punct_cb->isChecked();
    std::string password = genPassword(length, digits, punct);
    ui->gen_display->setText(QString::fromStdString(password));
}
