import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.1
import Components 1.0
import ".."

ToolBarBase {
    width: parent.width
    StandardButton {
        id: clear
        width: Theme.buttonSize
        height: Theme.buttonSize
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.verticalCenter: parent.verticalCenter
        text: qsTr("Clear")
        endColor: Theme.defaultButtonColor
        onClicked: drone.clearSafety()
    }
    StandardButton {
        id: cancel
        width: Theme.buttonSize
        height: Theme.buttonSize
        anchors.right: done.left
        anchors.rightMargin: 4
        anchors.verticalCenter: parent.verticalCenter
        text: qsTr("Cancel")
        endColor: Theme.defaultButtonColor
        onClicked: drone.state = DroneBase.IDLE
    }
    StandardButton {
        id: done
        width: Theme.buttonSize
        height: Theme.buttonSize
        anchors.right: parent.right
        anchors.rightMargin: 4
        anchors.verticalCenter: parent.verticalCenter
        text: qsTr("Done")
        endColor: Theme.defaultButtonColor
        onClicked: {
            if (drone.safetyModel.pointCount === 0)
                dialogMgr.showDialog(SpyC.EMPTY_SAFETY_ERROR, drone.uid)
            else
                dialogMgr.showDialog(SpyC.SAFETY_VALIDATION, drone.uid)
        }
    }
}
