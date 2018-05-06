import QtQuick 2.5
import QtQuick.Controls 1.4
import ".."
import "../widgets"

ToolBarBase {
    // Drone name
    Item {
        id: droneStatus
        anchors.left: parent.left
        anchors.right: switchButton.left
        height: parent.height
    }

    // Swith carto/video
    ImageButton {
        id: switchButton
        anchors.right: parent.right
        anchors.rightMargin: 4
        anchors.top: parent.top
        anchors.topMargin: 4
        source: "qrc:/icons/ico-maximized.png"
        onClicked: {
            if (mapView.state === "mapMinimized")
                mapView.state = "mapMaximized"
            else
            if (mapView.state === "mapMaximized")
                 mapView.state = "mapMinimized"
        }
    }
}
