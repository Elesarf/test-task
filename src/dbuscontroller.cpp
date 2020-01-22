#include <QDebug>
#include <QColor>
#include <QtDBus/QtDBus>
#include <QDBusMetaType>
#include "types.h"
#include "trackpointmodel.h"
#include "dbuscontroller.h"

DBusController::DBusController(QObject *parent) : QDBusAbstractAdaptor(parent),
    m_trackPointsModel(new TrackPointModel(this))
{
    qRegisterMetaType<GeoRectangle>("GeoRectangle");
    qDBusRegisterMetaType<GeoRectangle>();
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

static inline bool isGeoCoordinateValid(double lat, double lon)
{
    if (-90 > lat && lat > 90)
        return false;

    if (-180 > lon && lon > 180)
        return false;

    return true;
}

void DBusController::addTrackPoint(double lat, double lon, const QString &color)
{
    if (!isGeoCoordinateValid(lon, lat))
        return;

    if (!QColor::isValidColor(color))
        return;

    m_trackPointsModel->add({lon, lat, color});
    emit newTrackPoint();
}

void DBusController::setNewRect(double topLeftLat, double topLeftLon, double bottomRightLat, double bottomRightLon)
{
    if (!isGeoCoordinateValid(topLeftLon, topLeftLat))
        return;

    if (!isGeoCoordinateValid(bottomRightLon, bottomRightLat))
        return;

    emit mapRectangleChanged(GeoRectangle(topLeftLon, topLeftLat, bottomRightLon, bottomRightLat));
}
