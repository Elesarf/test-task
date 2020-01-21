import QtQuick 2.0
import QtLocation 5.0
import Sailfish.Silica 1.0
import QtPositioning 5.2

Item {
    id: mW

    function getMap(){
        return sharedMap;
    }

    function setState(_state){
        if (_state === "page" || _state === "cover")
            mW.state = _state
    }

    states: [
        State {
            name: "page"
            PropertyChanges {
                target: meMarker
                width: Theme.iconSizeExtraSmall
            }
        },
        State {
            name: "cover"
            PropertyChanges {
                target: meMarker
                width: Theme.iconSizeExtraSmall / 2
            }
        }
    ]

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

        MapQuickItem {
            id: marker
            anchorPoint.x: meMarker.width/4
            anchorPoint.y: meMarker.height
            coordinate: positionSource.position.coordinate

            sourceItem: Rectangle{
                id: meMarker
                width: Theme.iconSizeExtraSmall
                height: width
                radius: height / 2
                color: "green"
                border.width: 1
            }
        }
    }
}
