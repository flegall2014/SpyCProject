import QtQuick 2.5
import Components 1.0
import ".."

// Top container
Item {
    id: topContainer
    property variant targetDrone

    // Drone valid?
    function droneValid()
    {
        return (typeof targetDrone !== "undefined") && (targetDrone !== null)
    }

    // Drone label
    StandardText {
        id: droneLabel
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.verticalCenter: parent.verticalCenter
        color: droneValid() ? ((targetDrone.globalStatus === DroneBase.NOMINAL) ? Theme.nominalColor : (targetDrone.globalStatus === DroneBase.WARNING ? Theme.warningColor : Theme.criticalColor)) : Theme.defaultButtonColor
        text: droneValid() ? ("[" + targetDrone.uid + " (" + targetDrone.stateText + ")]") : ""
        font.pixelSize: Theme.largeFontSize
    }

    // Battery status widget
    BatteryStatusWidget {
        id: batteryStatusWidget
        anchors.left: droneLabel.right
        anchors.leftMargin: 4
        anchors.verticalCenter: parent.verticalCenter
        status: droneValid() ? targetDrone.batteryStatus : DroneBase.NOMINAL
        level: droneValid() ? targetDrone.batteryLevel : 0
    }

    // GPS status widget
    GPSStatusWidget {
        id: gpsStatusWidget
        anchors.left: batteryStatusWidget.right
        anchors.leftMargin: 4
        anchors.verticalCenter: parent.verticalCenter
        status: droneValid() ? targetDrone.gpsStatus : DroneBase.NOMINAL
        level: droneValid() ? targetDrone.gpsStrength : 0
    }
}
