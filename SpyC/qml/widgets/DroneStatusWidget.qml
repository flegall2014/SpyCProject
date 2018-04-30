import QtQuick 2.5
import Components 1.0
import ".."

// Top container
Item {
    id: topContainer
    property variant currentDrone

    // Drone valid?
    function droneValid()
    {
        return (typeof currentDrone !== "undefined") && (currentDrone !== null)
    }

    // Drone label
    StandardText {
        id: droneLabel
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.verticalCenter: parent.verticalCenter
        color: droneValid() ? ((currentDrone.globalStatus === DroneBase.NOMINAL) ? Theme.nominalColor : (currentDrone.globalStatus === DroneBase.WARNING ? Theme.warningColor : Theme.criticalColor)) : Theme.defaultButtonColor
        text: droneValid() ? ("[" + currentDrone.uid + " (" + currentDrone.stateText + ")]") : ""
        font.pixelSize: Theme.largeFontSize
    }

    // Battery status widget
    BatteryStatusWidget {
        id: batteryStatusWidget
        anchors.left: droneLabel.right
        anchors.leftMargin: 4
        anchors.verticalCenter: parent.verticalCenter
        status: droneValid() ? currentDrone.batteryStatus : DroneBase.NOMINAL
        level: droneValid() ? currentDrone.batteryLevel : 0
    }

    // GPS status widget
    GPSStatusWidget {
        id: gpsStatusWidget
        anchors.left: batteryStatusWidget.right
        anchors.leftMargin: 4
        anchors.verticalCenter: parent.verticalCenter
        status: droneValid() ? currentDrone.gpsStatus : DroneBase.NOMINAL
        level: droneValid() ? currentDrone.gpsStrength : 0
    }
}
