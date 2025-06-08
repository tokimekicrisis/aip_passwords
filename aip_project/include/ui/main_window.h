#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "ui_main_window.h"
#include <string>
#include <QMainWindow>

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);

  std::string genPassword(const int len, const bool digits, const bool punct);

private slots:
  void onGenerateBtnClicked();

private:
  Ui::MainWindow *ui;
};

#endif // MAIN_WINDOW_H
