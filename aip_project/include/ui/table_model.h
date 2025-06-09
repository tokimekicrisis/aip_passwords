#ifndef TABLE_MODEL_H
#define TABLE_MODEL_H

#include "database/database.h"

#include <QAbstractTableModel>
#include <QVariant>
#include <QModelIndex>

#include <vector>
#include <string>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    TableModel(QObject *parent = nullptr) : QAbstractTableModel(parent) {}
    void setData(const std::vector<std::vector<std::string>>& new_data) {
        beginResetModel();
        my_data = new_data;
        endResetModel();
    }
    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return my_data.size();
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        return 5;
    }

    QVariant data(const QModelIndex &index, int role) const override {
        if (role == Qt::DisplayRole) {
                return QString::fromStdString(my_data[index.row()][index.column()]);
            }
        else {return QVariant();}
    }

    // QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

public slots:
    void updateFromDatabase(Database* db, const char* search_term = nullptr, const char* cat = nullptr) {
        auto data = db->extractData(search_term, cat);
        setData(data);
    }

private:
    std::vector<std::vector<std::string>> my_data;
};

#endif // TABLE_MODEL_H
