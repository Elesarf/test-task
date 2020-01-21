#include <QDebug>
#include "trackpointmodel.h"
#include "dbuscontroller.h"

DBusController::DBusController(QObject *parent) : QDBusAbstractAdaptor(parent),
    m_trackPointsModel(new TrackPointModel(this))
{
}

DBusController::~DBusController()
{
    if (m_trackPointsModel != nullptr)
        delete m_trackPointsModel;
}

TrackPointModel *DBusController::trackPointsModel()
{
    return m_trackPointsModel;
}

void DBusController::addTrackPoint(double lon, double lat, const QString &color)
{
    qDebug() << "lon" << lon << "lat" << lat << "color" << color;

    m_trackPointsModel->add({lon, lat, color});
    emit newTrackPoint();
    qDebug() << "model size" << m_trackPointsModel->rowCount(QModelIndex());
}
