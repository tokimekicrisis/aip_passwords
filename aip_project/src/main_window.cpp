#include "database/database.h"
#include "ui/main_window.h"
#include "ui/table_model.h"

#include <QString>
#include <QRandomGenerator>
#include <QStyledItemDelegate>

/**
 * Конструктор главного окна приложения.
 * Инициализирует пользовательский интерфейс, модель таблицы и БД.
 * Устанавливает соединения кнопок интерфейса.
 * Настраивает модель данных для таблицы и обновляет её из БД.
 *
 * @param db База данных.
 * @param parent Родительский виджет.
 */
MainWindow::MainWindow(Database *db, QWidget *parent) :  QMainWindow(parent),
                                           ui(new Ui::MainWindow),
                                           table_model(new TableModel(this)),
                                           db(db) {
  ui->setupUi(this);
  connect(ui->generate_btn, &QPushButton::clicked,
          this, &MainWindow::onGenerateBtnClicked);
  connect(ui->add_btn, &QPushButton::clicked,
          this, &MainWindow::onAddBtnClicked);
  connect(ui->edit_btn, &QPushButton::clicked,
          this, &MainWindow::onEditBtnClicked);
  connect(ui->del_btn, &QPushButton::clicked,
          this, &MainWindow::onDelBtnClicked);
  connect(ui->search_btn, &QPushButton::clicked,
          this, &MainWindow::onSearchBtnClicked);
  ui->pws_table->setModel(table_model);
  table_model->updateFromDatabase(db);
  connect(ui->pws_table, &QTableView::clicked, this, [this](const QModelIndex &index) {
      if (index.isValid() && index.column() == 3) {
          QString category = table_model->data(index, Qt::DisplayRole).toString();
          onCategoryClicked(category);
      }
  });
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

/**
 * Открывает окно редактирования записи по нажатию кнопки.
 * Обновляет БД и модель таблицы согласно введенным данным.
 */
void MainWindow::onEditBtnClicked() {
  QModelIndexList selected = ui->pws_table->selectionModel()->selectedRows();
  if (selected.isEmpty()) { return; }

  int row = selected.first().row();

  QString id = table_model->data(table_model->index(row, 0), Qt::DisplayRole).toString();
  QString site = table_model->data(table_model->index(row, 1), Qt::DisplayRole).toString();
  QString password = table_model->data(table_model->index(row, 2), Qt::DisplayRole).toString();
  QString category = table_model->data(table_model->index(row, 3), Qt::DisplayRole).toString();
  QString comment = table_model->data(table_model->index(row, 4), Qt::DisplayRole).toString();

  QDialog editDialog;
  Ui::Dialog2 editUi;
  editUi.setupUi(&editDialog);

  editUi.site->setText(site);
  editUi.pw->setText(password);
  editUi.cat->setText(category);
  editUi.comm->setText(comment);

  if (editDialog.exec() == QDialog::Accepted) {
    bool success = db->updateData(
      id.toStdString().c_str(),
      editUi.site->text().toStdString().c_str(),
      editUi.pw->text().toStdString().c_str(),
      editUi.cat->text().toStdString().c_str(),
      editUi.comm->text().toStdString().c_str()
    );
    table_model->updateFromDatabase(db);
  }
}

/**
 * Открывает окно добавления записи по нажатию кнопки.
 * Обновляет БД и модель таблицы согласно введенным данным.
 */
void MainWindow::onAddBtnClicked() {
  QDialog addDialog;
  Ui::Dialog2 addUi;
  addUi.setupUi(&addDialog);

  if (addDialog.exec() == QDialog::Accepted) {
      bool success = db->insertData(
          addUi.site->text().toStdString().c_str(),
          addUi.pw->text().toStdString().c_str(),
          addUi.cat->text().toStdString().c_str(),
          addUi.comm->text().toStdString().c_str()
          );
      table_model->updateFromDatabase(db);
  }
}

/**
 * Открывает окно удаления записи по нажатию кнопки.
 * Удаляет запись с соответствующим ID из БД и обновляет модель таблицы.
 */
void MainWindow::onDelBtnClicked() {
  QModelIndexList selected = ui->pws_table->selectionModel()->selectedRows();
  if (selected.isEmpty()) { return; }

  int row = selected.first().row();

  QString id = table_model->data(table_model->index(row, 0), Qt::DisplayRole).toString();

  QDialog deleteDialog;
  Ui::Dialog deleteUi;
  deleteUi.setupUi(&deleteDialog);

  if (deleteDialog.exec() == QDialog::Accepted) {
    bool success = db->deleteData(id.toStdString().c_str());
    table_model->updateFromDatabase(db);
  }
}

/**
 * Производит поиск по БД по нажатию кнопки.
 * Для большей информации по алгоритму поиска смотреть Database::extractData.
 */
void MainWindow::onSearchBtnClicked() {
  QString search = ui->search_bar->text();
  table_model->updateFromDatabase(db, search.toStdString().c_str(), nullptr);
}

/**
 * Фильтрует таблицу по категории по нажатию ячейки с категорией.
 *
 * @param cat Название категории для фильтрации.
 */
void MainWindow::onCategoryClicked(const QString& cat) {
  table_model->updateFromDatabase(db, nullptr, cat.toStdString().c_str());
}
