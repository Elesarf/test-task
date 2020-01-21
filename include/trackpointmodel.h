#ifndef TRACKPOINTMODEL_H
#define TRACKPOINTMODEL_H

#include <QAbstractListModel>

class TrackPointModel : public QAbstractListModel
{
    Q_OBJECT
public:

    struct TrackPoint
    {
        TrackPoint(const qreal _lat, const qreal _lon, const QString &_color) :
            lat(_lat),
            lon(_lon),
            color(_color)
        {}

        TrackPoint(const QVariantMap &map) :
            lat(map["latitude"].toReal()),
            lon(map["longitude"].toReal()),
            color(map["color"].toString())
        {}

        QVariantMap toVariantMap() const
        {
            return
            {
                {"latitude", lat},
                {"longitude", lon},
                {"color", color}
            };
        }

        qreal lat;
        qreal lon;
        QString color;
    };

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
