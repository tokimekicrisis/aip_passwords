#ifndef TABLE_MODEL_H
#define TABLE_MODEL_H

#include "database/database.h"

#include <QAbstractTableModel>
#include <QVariant>
#include <QModelIndex>

#include <vector>
#include <string>


/**
 *Модель таблицы для отображения паролей.
*/
class TableModel : public QAbstractTableModel
{
  Q_OBJECT

public:
  /**
  * Конструктор модели таблицы.
  * @param parent Родительский виджет.
  */
  TableModel(QObject *parent = nullptr) : QAbstractTableModel(parent) {}

  /**
  * Ввод новых данных в таблицу.
  * @param new_data Новые данные.
  */
  void setData(const std::vector<std::vector<std::string>>& new_data) {
    beginResetModel();
    my_data = new_data;
    endResetModel();
  }

  /**
  * Подсчет количества строк в таблице.
  * @param parent Родитель.
  * @return int Количество строк.
  */
  int rowCount(const QModelIndex &parent = QModelIndex()) const override {
    return my_data.size();
  }

  /**
  * Подсчет количества столбцов в таблице.
  * @param parent Родитель.
  * @return int Количество столбцов.
  */
  int columnCount(const QModelIndex &parent = QModelIndex()) const override {
    return 5;
  }

  /**
  * Отображение данных в таблице.
  * @param index Индекс.
  * @param role Роль (элемент для отображения или нет).
  * @return QString Данные в данной ячейке.
  */
  QVariant data(const QModelIndex &index, int role) const override {
  if (role == Qt::DisplayRole) {
    return QString::fromStdString(my_data[index.row()][index.column()]);
  }
  else {return QVariant(); }
  }

  /**
  * Установка названий столбцов в таблице.
  * Названия строк задаются как номера строк.
  *
  * @param section Номер столбца.
  * @param orientation Ориентация (строка либо столбец).
  * @param role Роль (элемент для отображения или нет).
  * return QString Название столбца/строки.
  */
  QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
    if (role != Qt::DisplayRole)
      return QVariant();

    if (orientation == Qt::Horizontal) {
      static const QStringList headers = {"ID", "Сайт", "Пароль", "Категория", "Коммент"};
      if (section >= 0 && section < headers.size())
          return headers[section];
    }
    return QString::number(section + 1);
  }

public slots:
  /**
  * Загрузка новых данных из БД в таблицу.
  *
  * @param db База данных.
  * @param search_term Поисковой запрос.
  * @param cat Категория сортировки.
  */
  void updateFromDatabase(Database* db, const char* search_term = nullptr, const char* cat = nullptr) {
    auto data = db->extractData(search_term, cat);
    setData(data);
  }

private:
  std::vector<std::vector<std::string>> my_data;
};

#endif // TABLE_MODEL_H
