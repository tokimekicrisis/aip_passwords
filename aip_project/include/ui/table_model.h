#ifndef TABLE_MODEL_H
#define TABLE_MODEL_H

#include <QAbstractTableModel>
#include <vector>
#include <string>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    TableModel(QObject *parent = nullptr);
    void setData(const std::vector<std::vector<std::string>>& data);

    // QAbstractTableModel overrides
    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return data.size();
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        return 5;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        return QString::fromStdString(data[index.row()][index.column()]);
    }

    // QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
    std::vector<std::vector<std::string>> data;
};

#endif // TABLE_MODEL_H
