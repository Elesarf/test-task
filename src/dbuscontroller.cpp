#include <QDebug>
#include <QColor>
#include <QtDBus/QtDBus>
#include <QDBusMetaType>

#include "trackpointmodel.h"
#include "dbuscontroller.h"

DBusController::DBusController(QObject *parent) : QDBusAbstractAdaptor(parent),
    m_geoCoordViewport(0.0, 0.0, 0.0, 0.0),
    m_geoCoordMapCenter(0.0, 0.0),
    m_zoom(0.0)
{
    // register GeoRectangle type for qt
    qRegisterMetaType<GeoRectangle>("GeoRectangle");
    // register GeoRectangle type for dbus
    qDBusRegisterMetaType<GeoRectangle>();
    // reset model
    m_trackPointsModel = QSharedPointer<TrackPointModel>(new TrackPointModel);
}

DBusController::~DBusController(){}

TrackPointModel *DBusController::trackPointsModel()
{
    return m_trackPointsModel.data();
}

GeoRectangle DBusController::geoCoordViewport() const
{
    return m_geoCoordViewport;
}

QPointF DBusController::geoCoordMapCenter() const
{
    return m_geoCoordMapCenter;
}

double DBusController::zoom() const
{
    return m_zoom;
}

void DBusController::addTrackPoint(double lat, double lon, const QString &color)
{
    /*
     * Check coordinates and color.
     * If all right, add new track point to model
     */

    if (!isGeoCoordinateValid(lon, lat))
        return;

    if (!QColor::isValidColor(color))
        return;

    m_trackPointsModel->add({lon, lat, color});
    emit newTrackPoint();
}

void DBusController::setGeoCoordViewport(double topLeftLat, double topLeftLon,
                                         double bottomRightLat, double bottomRightLon)
{
    setGeoCoordViewport(GeoRectangle(topLeftLon, topLeftLat, bottomRightLon, bottomRightLat));
}

void DBusController::setNewRect(double topLeftLat, double topLeftLon,
                                double bottomRightLat, double bottomRightLon)
{
    if (!isGeoCoordinateValid(topLeftLon, topLeftLat))
        return;

    if (!isGeoCoordinateValid(bottomRightLon, bottomRightLat))
        return;

    emit mapRectangleChanged(GeoRectangle(topLeftLon, topLeftLat, bottomRightLon, bottomRightLat));
}

void DBusController::setGeoCoordViewport(GeoRectangle geoCoordViewport)
{
    m_geoCoordViewport = geoCoordViewport;
    emit geoCoordViewportChanged(m_geoCoordViewport);
}

void DBusController::setGeoCoordMapCenter(QPointF geoCoordMapCenter)
{
    m_geoCoordMapCenter = geoCoordMapCenter;
    emit geoCoordMapCenterChanged(m_geoCoordMapCenter);
}

void DBusController::setZoom(double zoom)
{
    if (qFuzzyCompare(m_zoom, zoom))
        return;

    m_zoom = zoom;
    emit zoomChanged(m_zoom);
}

bool DBusController::isGeoCoordinateValid(double lat, double lon)
{
    if (-90 > lat && lat > 90)
        return false;

    if (-180 > lon && lon > 180)
        return false;

    return true;
}
