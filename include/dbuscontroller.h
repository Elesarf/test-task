#ifndef DBUSCONTROLLER_H
#define DBUSCONTROLLER_H

#include <QObject>
#include <QtDBus/QDBusAbstractAdaptor>
#include <QtDBus/QDBusVariant>

class TrackPointModel;
class DBusController : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "ass.home.QtDBus.testtask.MapController")
    Q_PROPERTY(TrackPointModel *trackPointsModel READ trackPointsModel)

public:
    explicit DBusController(QObject *parent = nullptr);
    ~DBusController();

    TrackPointModel * trackPointsModel();

public slots:
    Q_NOREPLY void addTrackPoint(double lon, double lat, const QString &color);

signals:
    void newTrackPoint();

private:
    TrackPointModel *m_trackPointsModel;
};

#endif // DBUSCONTROLLER_H
