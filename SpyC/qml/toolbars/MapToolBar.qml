import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.1
import "../widgets"
import ".."

ToolBarBase {
    // Maximize
    ImageButton {
        id: maximizeButton
        anchors.right: parent.right
        anchors.rightMargin: 4
        anchors.top: parent.top
        anchors.topMargin: 4
        source: mapView.state === "" ? "qrc:/icons/ico-maximized.png" : "qrc:/icons/ico-minimized.png"
        visible: mapView.state !== "mapMinimized"
    }
}
