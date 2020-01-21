#include "trackpointmodel.h"

TrackPointModel::TrackPointModel(QObject *parent) : QAbstractListModel(parent){}

int TrackPointModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;

    return m_data.size();
}

QVariant TrackPointModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() > m_data.size())
            return QVariant();

    const auto item = m_data.at(index.row());

    switch (role)
    {
    case Latitude:
        return QVariant::fromValue(item.lat);
    case Longitude:
        return QVariant::fromValue(item.lon);
    case Color:
        return QVariant::fromValue(item.color);
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> TrackPointModel::roleNames() const
{
    return
    {
        {Latitude, "latitudeValue"},
        {Longitude, "longitudeValue"},
        {Color, "colorString"}
    };
}

bool TrackPointModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    for (int i = (row + count - 1); i >= row; i-- )
        m_data.removeAt(i);
    endRemoveRows();
    return true;
}

bool TrackPointModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    for ( int i = row; i < (row + count - 1); i++ )
        m_data.append(TrackPoint{0.0, 0.0, ""});
    endInsertRows();
    return true;
}

bool TrackPointModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() > m_data.size())
           return false;

       auto row = index.row();

       switch (role)
       {
       case Latitude:
           m_data[row].lat = value.toReal();
           break;
       case Longitude:
           m_data[row].lon = value.toReal();
           break;
       case Color:
           m_data[row].color = value.toString();
           break;
       }

       emit dataChanged(index, index, {role});
       return true;
}

void TrackPointModel::add()
{
    beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.append(TrackPoint{0.0, 0.0, ""});
    endInsertRows();
}

void TrackPointModel::add(const TrackPoint &p)
{
    beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.append(p);
    endInsertRows();
}

void TrackPointModel::clear()
{
    beginResetModel();
    m_data.clear();
    endResetModel();
}
