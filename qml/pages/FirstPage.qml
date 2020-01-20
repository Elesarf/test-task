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

        zoomIn.z = map.z + 1
        zoomOut.z = map.z + 1

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
    }

    Rectangle{
        id: zoomIn

        color: "grey"
        border.width: 1

        width: 160
        height: width
        radius: width / 2

        anchors{
            right: parent.right
            rightMargin: 16
            bottom: zoomOut.top
            bottomMargin: 16
        }

        Text {
            text: qsTr("+")
            anchors{
                fill: parent
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }
        }

        MouseArea{
            anchors.fill: parent

            onClicked: page.zoomIn()
        }
    }

    Rectangle{
        id: zoomOut

        color: "grey"
        border.width: 1

        width: 160
        height: width
        radius: width / 2
        z: 2

        anchors{
            right: parent.right
            rightMargin: 16
            bottom: parent.bottom
            bottomMargin: 16
        }

        Text {
            text: qsTr("-")
            anchors{
                fill: parent
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }
        }

        MouseArea{
            anchors.fill: parent

            onClicked: page.zoomOut()
        }
    }
}

