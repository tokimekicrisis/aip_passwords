#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "ui_main_window.h"
#include "ui_edit_pw.h"
#include "ui_delete.h"
#include "table_model.h"

#include <QMainWindow>
#include <QItemSelection>

#include <string>

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);

  std::string genPassword(const int len, const bool digits, const bool punct);

  TableModel* getTableModel() const { return table_model; }

private slots:
  void onGenerateBtnClicked();
  void onAddBtnClicked();
  void onEditBtnClicked();
  void onDelBtnClicked();
  void onSearchBtnClicked();
  void onCategoryClicked(const QString& cat);

private:
  Ui::MainWindow *ui;
  TableModel *table_model;
  Database *db;
};

#endif // MAIN_WINDOW_H
