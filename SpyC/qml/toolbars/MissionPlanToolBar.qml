import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.1
import Components 1.0
import ".."

ToolBarBase {
    StandardButton {
        id: clear
        width: Theme.buttonSize
        height: Theme.buttonSize
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.verticalCenter: parent.verticalCenter
        label: qsTr("Clear")
        endColor: Theme.defaultButtonColor
        onClicked: drone.clearMissionPlan()
    }
    StandardButton {
        id: cancel
        width: Theme.buttonSize
        height: Theme.buttonSize
        anchors.right: done.left
        anchors.rightMargin: 4
        anchors.verticalCenter: parent.verticalCenter
        label: qsTr("Cancel")
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
        label: qsTr("Done")
        endColor: Theme.defaultButtonColor
        onClicked: {
            if (drone.missionPlanModel.pointCount === 0)
                dialogMgr.showDialog(SpyC.EMPTY_MISSION_PLAN_ERROR, drone.uid)
            else
                dialogMgr.showDialog(SpyC.MISSION_PLAN_VALIDATION, drone.uid)
        }
    }
}
