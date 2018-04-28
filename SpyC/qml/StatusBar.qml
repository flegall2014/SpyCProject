import QtQuick 2.5
import "."

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
