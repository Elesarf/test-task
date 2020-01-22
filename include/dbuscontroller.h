#ifndef DBUSCONTROLLER_H
#define DBUSCONTROLLER_H

#include <QObject>
#include <QMetaType>
#include <QtDBus/QDBusAbstractAdaptor>
#include <QtDBus/QDBusVariant>

class TrackPointModel;
struct GeoRectangle;

class DBusController : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "ass.home.QtDBus.testtask.MapController")
    Q_PROPERTY(TrackPointModel *trackPointsModel READ trackPointsModel)

public:
    explicit DBusController(QObject *parent);
    ~DBusController();

    TrackPointModel * trackPointsModel();

public slots:
    Q_NOREPLY void addTrackPoint(double lat, double lon, const QString &color);
    Q_NOREPLY void setNewRect(double topLeftLat, double topLeftLon, double bottomRightLat, double bottomRightLon);

signals:
    void newTrackPoint();
    void drawRect();
    void mapRectangleChanged(const GeoRectangle &mapRectangle);

private:
    TrackPointModel *m_trackPointsModel;
};

#endif // DBUSCONTROLLER_H
