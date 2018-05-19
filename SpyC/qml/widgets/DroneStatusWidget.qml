import QtQuick 2.5
import Components 1.0
import ".."

// Top container
Item {
    id: root
    property variant targetDrone

    // Drone valid?
    function droneValid()
    {
        return (typeof targetDrone !== "undefined") && (targetDrone !== null)
    }

    // Battery status widget
    BatteryStatusWidget {
        id: batteryStatusWidget
        anchors.left: parent.left
        anchors.leftMargin: Theme.standardMargin
        anchors.verticalCenter: parent.verticalCenter
        batteryLevel: droneValid() ? targetDrone.batteryLevel : 0
        returnLevel: droneValid() ? targetDrone.returnLevel : 0
    }

    Rectangle {
        color: "red"
        anchors.left: batteryStatusWidget.right
        anchors.right: parent.right
        height: parent.height
    }
}
