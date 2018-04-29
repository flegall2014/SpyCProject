import QtQuick 2.4
import Components 1.0
import ".."

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
                console.log(MASTERCONTROLLER.missionPlanController.currentDrone)
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
            text: qsTr("Safety plan is empty. ABORTING")
        }
    }
}

