import QtQuick 2.0
import Sailfish.Silica 1.0
import QtLocation 5.0

Page {
    id: page

    property var map: null
    property double currentZoomLevel: 0.0

    onMapChanged: {
        if (map === null)
            return

        map.parent = this
        map.anchors.fill = this
        map.enabled = true

        zoomControl.z = map.z + 1

        if (currentZoomLevel === 0)
            currentZoomLevel = map.zoomLevel

        map.zoomLevel = currentZoomLevel
    }

    function zoomIn(){

        if (map.zoomLevel < map.maximumZoomLevel)
            map.zoomLevel += 0.2

        currentZoomLevel = map.zoomLevel
    }

    function zoomOut(){

        if (map.zoomLevel > map.minimumZoomLevel)
            map.zoomLevel -= 0.2

        currentZoomLevel = map.zoomLevel

        console.log(map.maximumZoomLevel - map.zoomLevel)
    }

    Column{
        id: zoomControl

        y: parent.height / 2
        anchors.right: parent.right

        spacing: Theme.paddingSmall

        Button{
            id: zoomIn

            width: height

            text: "+"
            color: Theme.darkPrimaryColor

            onClicked: page.zoomIn()
        }

        Button{
            id: zoomOut

            width: height

            text: "-"
            color: Theme.darkPrimaryColor

            onClicked: page.zoomOut()
        }
    }
}

