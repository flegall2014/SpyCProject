import QtQuick 2.4
import Components 1.0
import ".."

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
                MASTERCONTROLLER.currentDrone.editMode = DroneBase.NONE
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
                MASTERCONTROLLER.missionPlanController.validateMissionPlan(MASTERCONTROLLER.currentDrone.uid)
                MASTERCONTROLLER.currentDrone.editMode = DroneBase.NONE
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

