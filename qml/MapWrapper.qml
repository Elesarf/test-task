import QtQuick 2.0
import QtLocation 5.0
import QtPositioning 5.2

Item {

    function getMap(){
        return sharedMap;
    }

    PositionSource{
        id: positionSource

        updateInterval: 4000
        nmeaSource: "/usr/share/%1/nmea/output.nmea".arg(Qt.application.name)
        active: true
    }

    Plugin {
        id: osmPlugin
        name: "osm"

        PluginParameter
        {
            name: "osm"
        }
    }

    Map {
        id: sharedMap

        zoomLevel: maximumZoomLevel
        center: positionSource.position.coordinate

        plugin: osmPlugin

        Component.onCompleted: parent = mainWindow
    }
}
