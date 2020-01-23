#include <QDebug>
#include <QColor>
#include <QtDBus/QtDBus>
#include <QDBusMetaType>

#include "trackpointmodel.h"
#include "dbuscontroller.h"

DBusController::DBusController(QObject *parent) : QDBusAbstractAdaptor(parent)
{
    qRegisterMetaType<GeoRectangle>("GeoRectangle");
    qDBusRegisterMetaType<GeoRectangle>();

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

static inline bool isGeoCoordinateValid(double lat, double lon)
{
    if (-90 > lat && lat > 90)
        return false;

    if (-180 > lon && lon > 180)
        return false;

    return true;
}

void DBusController::setGeoCoordViewport(double topLeftLat, double topLeftLon, double bottomRightLat, double bottomRightLon)
{
    setGeoCoordViewport(GeoRectangle(topLeftLon, topLeftLat, bottomRightLon, bottomRightLat));
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
    qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_zoom, zoom))
        return;

    m_zoom = zoom;
    emit zoomChanged(m_zoom);
}
