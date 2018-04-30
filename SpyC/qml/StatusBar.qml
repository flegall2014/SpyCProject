import QtQuick 2.5
import Components 1.0
import "."
import "./widgets"

// Status bar
Rectangle {
    id: statusBar
    color: Theme.statusBarColor
    property bool windowsButtonVisible: false
    signal windowsButtonClicked()

    // Windows button
    ImageButton {
        id: windowsButton
        visible: windowsButtonVisible
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.verticalCenter: parent.verticalCenter
        source: "qrc:/icons/ico-windows.svg"
        onClicked: windowsButtonClicked()
    }

    // Other drone display
    Item {
        id: otherDroneDisplay
        anchors.left: windowsButton.right
        anchors.leftMargin: 8
        width: 512
        height: parent.height
        visible: windowsButtonVisible
        ListView {
            id: listView
            anchors.fill: parent
            interactive: false
            orientation: Qt.Horizontal
            model: MASTERCONTROLLER.otherDroneCount
            spacing: 8
            delegate: StandardText {
                anchors.verticalCenter: parent.verticalCenter
                color: (MASTERCONTROLLER.getOtherDrone(index).globalStatus === DroneBase.NOMINAL) ? Theme.nominalColor : (MASTERCONTROLLER.getOtherDrone(index).globalStatus === DroneBase.WARNING ? Theme.warningColor : Theme.criticalColor)
                text: "[" + MASTERCONTROLLER.getOtherDrone(index).uid + " (" + MASTERCONTROLLER.getOtherDrone(index).stateText + ")]"
                font.pixelSize: Theme.largeFontSize
            }
        }
    }

    // Thales icon
    Image {
        id: thalesIcon
        anchors.centerIn: parent
        source: "file:///D:/projects/SpycProject/SpyC/thales/ico-thales.png"
        height: parent.height
        fillMode: Image.PreserveAspectFit
        antialiasing: true
    }

    // Date display
    DateDisplay {
        height: parent.height
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.verticalCenter: parent.verticalCenter
    }
}
