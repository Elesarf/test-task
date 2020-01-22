#ifndef TYPES_H
#define TYPES_H

#include <QObject>
#include <QMetaType>
#include <QtDBus/QDBusArgument>

struct GeoRectangle
{
    Q_GADGET
    Q_PROPERTY(double topLeftLon MEMBER topLeftLon)
    Q_PROPERTY(double topLeftLat MEMBER topLeftLat)
    Q_PROPERTY(double bottomRightLon MEMBER bottomRightLon)
    Q_PROPERTY(double bottomRightLat MEMBER bottomRightLat)
public:
    GeoRectangle(){}
    GeoRectangle(double _topLeftLat, double _topLeftLon, double _bottomRightLat, double _bottomRightLon):
        topLeftLon(_topLeftLon),
        topLeftLat(_topLeftLat),
        bottomRightLon(_bottomRightLon),
        bottomRightLat(_bottomRightLat)
    {}

    double topLeftLon{0};
    double topLeftLat{0};
    double bottomRightLon{0};
    double bottomRightLat{0};
};

static QDBusArgument& operator <<(QDBusArgument &argument, const GeoRectangle & arg)
{
    argument.beginStructure();
    argument << arg.topLeftLat << arg.topLeftLon << arg.bottomRightLat << arg.bottomRightLon;
    argument.endStructure();
    return argument;
}

static const QDBusArgument& operator >>(const QDBusArgument &argument, GeoRectangle & arg)
{
    argument.beginStructure();
    argument >> arg.topLeftLat >> arg.topLeftLon >> arg.bottomRightLat >> arg.bottomRightLon;
    argument.endStructure();
    return argument;
}
Q_DECLARE_METATYPE(GeoRectangle)

struct TrackPoint
{
    TrackPoint(const double _lat, const double _lon, const QString &_color) :
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

    double lat;
    double lon;
    QString color;
};

#endif // TYPES_H
