import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtLocation 5.3
import QtPositioning 5.6
import Components 1.0
import "."
import "pages/dronePage"
import "pages/loginPage"

// Main application window
ApplicationWindow {
    id: appWindow
    width: 512
    height: 512

    // App title
    property string appTitle: "Template"

    // Set visible
    visible: true

    // Go next enabled?
    property bool goNextEnabled: true

    // Visibility
    visibility: Window.FullScreen

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
            showDroneStatus: dronePage.droneExpanded
        }

        // Login page
        LoginPage {
            id: loginPage
            anchors.bottom: statusBar.top
            anchors.top: toolBar.bottom
            width: parent.width
            onLoginClicked: {
                MASTERCONTROLLER.detectDrones()
                loginPage.state = "hidden"
                dronePage.state = "visible"
            }
        }

        // Drone page
        DronePage {
            id: dronePage
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
            windowsButtonVisible: dronePage.droneExpanded
            enabled: dialogMgr.state === ""
            onWindowsButtonClicked: {
                dronePage.droneExpanded = false
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
