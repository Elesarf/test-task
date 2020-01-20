/*
  Copyright (C) 2013 Jolla Ltd.
  Contact: Thomas Perl <thomas.perl@jollamobile.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

import QtQuick 2.0
import Sailfish.Silica 1.0
import QtLocation 5.0
import QtPositioning 5.2

import "pages"
import "cover"

ApplicationWindow
{
    id: mainWindow

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

    cover:  CoverPage{
            id: appCover
    }

    initialPage: FirstPage{
            id: mainPage
    }

    onApplicationActiveChanged:{

        if (applicationActive){
            mainPage.map = sharedMap
            appCover.map = null
        }
        else{
            appCover.map = sharedMap
            mainPage.map = null
        }

        console.log("state: " + applicationActive)
    }
}
