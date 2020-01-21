import QtQuick 2.0
import QtLocation 5.0
import Sailfish.Silica 1.0
import QtPositioning 5.2

Item {
    id: mW

    property var model: null

    onModelChanged:{

        if (model !== null)
            trackPointsView.model = model

        console.log("model update")
    }

    function getMap(){
        return sharedMap;
    }

    function setState(_state){
        if (_state === "page" || _state === "cover")
            mW.state = _state
    }

    function updateViewport(){
        sharedMap.fitViewportToMapItems()
    }

    Timer
    {
        id: mapRefreshtimer
        running: true
        interval: 2000
        repeat: true
        onTriggered:
        {
            sharedMap.fitViewportToMapItems()
        }
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

        MapItemView{
            id: trackPointsView
            model: markerModel

            delegate: MapQuickItem {
                coordinate: QtPositioning.coordinate(latitudeValue, longitudeValue)
                sourceItem: Rectangle{
                    width: Theme.iconSizeExtraSmall
                    height: width
                    radius: height / 2
                    color: colorString
                    border.width: 1
                }
            }
        }

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
