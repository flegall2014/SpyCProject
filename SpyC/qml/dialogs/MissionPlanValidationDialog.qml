import QtQuick 2.4
import Components 1.0
import ".."
import "../widgets"

DialogBase {
    bottomBarContents: Item {
        anchors.fill: parent

        // Cancel
        StandardButton {
            id: cancelButton
            anchors.right: parent.right
            anchors.rightMargin: 4
            anchors.verticalCenter: parent.verticalCenter
            label: qsTr("Cancel")
            onClicked: {
                targetDrone.setDefaultWorkMode()
                closeDialog()
            }
        }

        // OK
        StandardButton {
            id: okButton
            anchors.right: cancelButton.left
            anchors.rightMargin: 4
            anchors.verticalCenter: parent.verticalCenter
            label: qsTr("OK")
            onClicked: {
                MASTERCONTROLLER.missionPlanController.validateMissionPlanRequest(targetDrone.uid)
                targetDrone.setDefaultWorkMode()
                closeDialog()
            }
        }
    }
    dialogContents: Item {
        anchors.fill: parent
        StandardText {
            anchors.centerIn: parent
            font.pixelSize: Theme.largeFontSize
            text: qsTr("Upload mission plan?")
        }
    }
}

