import QtQuick 2.0
import QtLocation 5.0
import Sailfish.Silica 1.0
import QtPositioning 5.2

Item {
    id: mW

    property var model: null

    signal viewportCoordChanged(real topLeftLat, real topLeftLon, real bottomRightLat, real bottomRightLon)
    signal centerCoordChanged(real lat, real lon)
    signal zoomChanged(real zoom)

    onModelChanged:{
        if (model !== null)
            trackPointsView.model = model
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

    function drawNewPoint(){
        sharedMap.removeMapItem(markerItem)
        sharedMap.zoomLevel = sharedMap.minimumZoomLevel - 1
        sharedMap.center = QtPositioning.coordinate(0, 0)
        sharedMap.fitViewportToMapItems()
    }

    function updateRect(mr){

        sharedMap.clearMapItems()
        sharedMap.drawingRegion = Qt.createQmlObject(
                    'import QtLocation 5.0; MapRectangle {border.width: 2}',
                    sharedMap)
        sharedMap.drawingRegion.topLeft.latitude = mr.topLeftLat
        sharedMap.drawingRegion.topLeft.longitude = mr.topLeftLon
        sharedMap.drawingRegion.bottomRight.latitude = mr.bottomRightLat
        sharedMap.drawingRegion.bottomRight.longitude = mr.bottomRightLon
        sharedMap.addMapItem(sharedMap.drawingRegion)

        sharedMap.center = QtPositioning.coordinate((mr.bottomRightLat + mr.topLeftLat) / 2,
                                                    (mr.bottomRightLon + mr.topLeftLon) / 2)
        sharedMap.zoomLevel = sharedMap.minimumZoomLevel - 1

        sharedMap.fitViewportToMapItems()
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
    }

    Map {
        id: sharedMap

        property MapRectangle drawingRegion

        plugin: osmPlugin
        gesture.enabled: true

        center: positionSource.position.coordinate

        Component.onCompleted: {
            zoomLevel = maximumZoomLevel
            addMapItem(markerItem)
        }

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
    }

    MapQuickItem {
        id: markerItem
        anchorPoint.x: meMarker.width / 2
        anchorPoint.y: meMarker.height / 2
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
