#ifndef TYPES_H
#define TYPES_H

#include <QObject>
#include <QMetaType>
#include <QtDBus/QDBusArgument>

/*!
 * \brief The GeoRectangle struct represent rectangle with
 * a geographic coordinate system.
 *
 * |[top left lat][top left lon] -------------------------|
 * |                                                      |
 * |-----------------[bottom right lat] [bottom right lon]|
 */
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

    GeoRectangle &operator= (const GeoRectangle &other)
    {
        topLeftLon = other.topLeftLon;
        topLeftLat = other.topLeftLat;
        bottomRightLon = other.bottomRightLon;
        bottomRightLat = other.bottomRightLat;
        return *this;
    }

    double topLeftLon{0};
    double topLeftLat{0};
    double bottomRightLon{0};
    double bottomRightLat{0};
};

/*!
 * \brief operator << marshalling GeoRectangle
 * \param argument QDBusArgument
 * \param arg GeoRectangle to marhalling
 * \return
 */
static QDBusArgument& operator <<(QDBusArgument &argument, const GeoRectangle & arg)
{
    argument.beginStructure();
    argument << arg.topLeftLat << arg.topLeftLon << arg.bottomRightLat << arg.bottomRightLon;
    argument.endStructure();
    return argument;
}

/*!
 * \brief operator >> demarshalling GeoRectangle
 * \param argument QDBusArgument
 * \param arg GeoRectangle to demarhalling
 * \return
 */
static const QDBusArgument& operator >>(const QDBusArgument &argument, GeoRectangle & arg)
{
    argument.beginStructure();
    argument >> arg.topLeftLat >> arg.topLeftLon >> arg.bottomRightLat >> arg.bottomRightLon;
    argument.endStructure();
    return argument;
}
Q_DECLARE_METATYPE(GeoRectangle)

/*!
 * \brief The TrackPoint struct represent one point to draw on map.
 *
 * Point use geographic coordinate system, and string representation
 * of QColor
 */
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

    /*!
     * \brief toVariantMap serilize from point to VariantMap
     * \return
     */
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
