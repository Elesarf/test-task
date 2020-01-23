#ifndef DBUSCONTROLLER_H
#define DBUSCONTROLLER_H

#include <QObject>
#include <QMetaType>
#include <QPointF>
#include <QtDBus/QDBusAbstractAdaptor>
#include <QtDBus/QDBusVariant>

#include "types.h"

class TrackPointModel;

class DBusController : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "ass.home.QtDBus.testtask.MapController")

    Q_PROPERTY(TrackPointModel *trackPointsModel READ trackPointsModel)
    Q_PROPERTY(GeoRectangle geoCoordViewport READ geoCoordViewport WRITE setGeoCoordViewport NOTIFY geoCoordViewportChanged)
    Q_PROPERTY(QPointF geoCoordMapCenter READ geoCoordMapCenter WRITE setGeoCoordMapCenter NOTIFY geoCoordMapCenterChanged)
    Q_PROPERTY(double zoom READ zoom WRITE setZoom NOTIFY zoomChanged)

public:
    explicit DBusController(QObject *parent);
    ~DBusController();

    TrackPointModel * trackPointsModel();
    GeoRectangle geoCoordViewport() const;
    QPointF geoCoordMapCenter() const;
    double zoom() const;

    Q_INVOKABLE void setGeoCoordViewport(double topLeftLat, double topLeftLon, double bottomRightLat, double bottomRightLon);

public slots:
    Q_NOREPLY void addTrackPoint(double lat, double lon, const QString &color);
    Q_NOREPLY void setNewRect(double topLeftLat, double topLeftLon, double bottomRightLat, double bottomRightLon);

    void setGeoCoordViewport(GeoRectangle geoCoordViewport);
    void setGeoCoordMapCenter(QPointF geoCoordMapCenter);
    void setZoom(double zoom);

signals:
    void newTrackPoint();
    void drawRect();
    void mapRectangleChanged(const GeoRectangle &mapRectangle);

    void geoCoordViewportChanged(GeoRectangle geoCoordViewport);
    void geoCoordMapCenterChanged(QPointF geoCoordMapCenter);
    void zoomChanged(double zoom);

private:
    TrackPointModel *m_trackPointsModel;
    GeoRectangle m_geoCoordViewport;
    QPointF m_geoCoordMapCenter;
    double m_zoom;
};

#endif // DBUSCONTROLLER_H
