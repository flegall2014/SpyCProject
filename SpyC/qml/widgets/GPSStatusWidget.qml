import QtQuick 2.5
import QtGraphicalEffects 1.0
import Components 1.0
import ".."

// Battery image
Image {
    id: batteryImage
    property int gpsStatus
    property int gpsStrength
    fillMode: Image.PreserveAspectFit
    source: "qrc:/icons/ico-gps.svg"

    // Color overlay
    ColorOverlay {
        id: batteryColorOverlay
        anchors.fill: batteryImage
        source: batteryImage
        color: gpsStatus === DroneBase.NOMINAL ? Theme.nominalColor :
        (gpsStatus === DroneBase.WARNING ? Theme.warningColor : Theme.criticalColor)
    }

    // Text
    StandardText {
        anchors.centerIn: parent
        font.pixelSize: 0.175*parent.width
        color: Theme.invertDefaultFontColor
        font.bold: true
        text: gpsStrength + "%"
    }
}
