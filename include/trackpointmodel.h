#ifndef TRACKPOINTMODEL_H
#define TRACKPOINTMODEL_H

#include <QAbstractListModel>

#include "types.h"

class TrackPointModel : public QAbstractListModel
{
    Q_OBJECT
public:

    using TrackPointList = QList<TrackPoint>;

    explicit TrackPointModel(QObject *parent = nullptr);

    enum trackPointRoles{
            Latitude = Qt::UserRole + 1,
            Longitude,
            Color
        };

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    Q_INVOKABLE bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex()) override;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Q_INVOKABLE void add();
    Q_INVOKABLE void add(const TrackPoint &p);
    Q_INVOKABLE void clear();

private:
    TrackPointList m_data;
};

#endif // TRACKPOINTMODEL_H
