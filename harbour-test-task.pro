# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application

TARGET = harbour-test-task

CONFIG += sailfishapp location
QT += dbus

SOURCES += src/main.cpp \
    src/trackpointmodel.cpp \
    src/dbuscontroller.cpp

OTHER_FILES += \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    rpm/$${TARGET}.spec \
    rpm/$${TARGET}.yaml \
    translations/*.ts \
    $${TARGET}.desktop \
    nmea/*

nmea.files = nmea/*.nmea
nmea.path = /usr/share/$$TARGET/nmea

INSTALLS += nmea

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n
TRANSLATIONS += translations/$${TARGET}-ru.ts

DISTFILES += \
    qml/harbour-test-task.qml \
    qml/MapWrapper.qml

HEADERS += \
    include/trackpointmodel.h \
    include/dbuscontroller.h

INCLUDEPATH += include

