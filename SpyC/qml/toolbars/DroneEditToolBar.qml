import QtQuick 2.5
import QtQuick.Controls 1.4
import ".."

ToolBarBase {
    // Drone name
    Item {
        anchors.left: parent.left
        anchors.right: maximizeButton.left
        height: parent.height
        StandardText {
            anchors.left: parent.left
            anchors.leftMargin: 4
            anchors.verticalCenter: parent.verticalCenter
            text: drone.uid
            color: Theme.invertDefaultFontColor
            font.bold: true
        }
    }

    // Maximize
    ImageButton {
        id: maximizeButton
        anchors.right: parent.right
        anchors.rightMargin: 4
        anchors.top: parent.top
        anchors.topMargin: 4
        source: mapView.state === "" ? "qrc:/icons/ico-maximized.png" : "qrc:/icons/ico-minimized.png"
        visible: mapView.state !== "mapMinimized"
        onClicked: {
            if (droneDisplay.state === "")
            {
                droneDisplay.state = "expanded"
                listView.droneExpanded = true
                MASTERCONTROLLER.currentDrone = drone
            }
            else
            {
                if (mapView.state === "")
                    mapView.state = "mapMaximized"
                else
                    mapView.state = ""
            }
        }
    }
}
