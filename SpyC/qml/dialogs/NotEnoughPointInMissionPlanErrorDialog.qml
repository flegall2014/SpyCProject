import QtQuick 2.4
import Components 1.0
import ".."
import "../widgets"

DialogBase {
    bottomBarContents: Item {
        anchors.fill: parent

        // OK
        StandardButton {
            id: cancelButton
            anchors.right: parent.right
            anchors.rightMargin: 4
            anchors.verticalCenter: parent.verticalCenter
            label: qsTr("OK")
            onClicked: {
                targetDrone.editMode = DroneBase.NONE
                closeDialog()
            }
        }
    }
    dialogContents: Item {
        anchors.fill: parent
        StandardText {
            anchors.centerIn: parent
            font.pixelSize: Theme.largeFontSize
            text: qsTr("Not enough points in mission plan. ABORTING")
        }
    }
}

