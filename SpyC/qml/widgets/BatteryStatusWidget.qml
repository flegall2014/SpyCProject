import QtQuick 2.5
import QtGraphicalEffects 1.0
import Components 1.0
import ".."

// Battery image
Image {
    id: batteryImage
    property int batteryStatus
    property int batteryLevel
    fillMode: Image.PreserveAspectFit
    source: "qrc:/icons/ico-battery.svg"

    // Color overlay
    ColorOverlay {
        id: batteryColorOverlay
        anchors.fill: batteryImage
        source: batteryImage
        color: batteryStatus === DroneBase.NOMINAL ? Theme.nominalColor :
        (batteryStatus === DroneBase.WARNING ? Theme.warningColor : Theme.criticalColor)
    }

    // Text
    StandardText {
        anchors.centerIn: parent
        font.pixelSize: 0.2*parent.width
        color: batteryColorOverlay.color
        font.bold: true
        text: batteryLevel + "%"
    }
}
