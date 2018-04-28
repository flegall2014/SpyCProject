import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtLocation 5.3
import QtPositioning 5.6
import Components 1.0
import "."

// Main application window
ApplicationWindow {
    id: app
    width: 512
    height: 512

    // App title
    property string appTitle: "Template"

    // Set visible
    visible: true

    // Visibility
    visibility: Window.Maximized

    Rectangle {
        anchors.fill: parent
        color: Theme.backgroundColor

        // Status bar
        ToolBar {
            id: toolBar
            width: parent.width
            height: Theme.toolBarHeight
            anchors.top: parent.top
            enabled: dialogMgr.state === ""
        }

        // Drone view
        DroneView {
            id: droneView
            anchors.bottom: statusBar.top
            anchors.top: toolBar.bottom
            width: parent.width
            enabled: dialogMgr.state === ""
        }

        // Status bar
        StatusBar {
            id: statusBar
            width: parent.width
            height: Theme.toolBarHeight
            anchors.bottom: parent.bottom
            windowsButtonVisible: droneView.droneExpanded
            enabled: dialogMgr.state === ""
            onWindowsButtonClicked: {
                droneView.droneExpanded = false
                MASTERCONTROLLER.setAllDroneState(DroneBase.IDLE)
            }
        }

        // Dialog manager
        DialogMgr {
            id: dialogMgr
            anchors.fill: parent
            Component.onCompleted: {
                MASTERCONTROLLER.missionPlanController.missionPlanError.connect(onMissionPlanError)
            }

            // Safety error
            function onMissionPlanError(error, droneUID)
            {
                console.log("POPO ", error, droneUID)

                if (error === MissionPlanController.EMPTY_SAFETY)
                    dialogMgr.showDialog(SpyC.EMPTY_SAFETY_ERROR, droneUID)
                else
                if (error === MissionPlanController.NOT_ENOUGH_POINTS_IN_SAFETY)
                    dialogMgr.showDialog(SpyC.NOT_ENOUGH_POINT_IN_SAFETY, droneUID)
                else
                if (error === MissionPlanController.EMPTY_MISSION_PLAN)
                    dialogMgr.showDialog(SpyC.EMPTY_MISSION_PLAN_ERROR, droneUID)
                else
                if (error === MissionPlanController.NOT_ENOUGH_POINTS_IN_MISSION_PLAN)
                     dialogMgr.showDialog(SpyC.NOT_ENOUGH_POINT_IN_MISSION_PLAN, droneUID)
            }
        }
    }
}
