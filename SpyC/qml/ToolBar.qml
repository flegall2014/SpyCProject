import QtQuick 2.5
import QtQuick.Controls 1.4
import Components 1.0
import "."

// Status bar
Rectangle {
    id: toolBar
    color: Theme.toolBarColor

    // Mission name
    StandardText {
        anchors.centerIn: parent
        font.pixelSize: Theme.largeFontSize
        font.bold: true
        text: qsTr("Spy'C by THALES")
    }

    // Quit button
    ImageButton {
        anchors.right: parent.right
        anchors.rightMargin: 4
        anchors.verticalCenter: parent.verticalCenter
        source: "qrc:/icons/ico-shutdown.png"
        onClicked: Qt.quit()
    }
}
