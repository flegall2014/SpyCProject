import QtQuick 2.5
import QtQuick.Controls 2.0
import Components 1.0
import "."

// Common area
Rectangle {
    id: commonArea
    color: Theme.backgroundColor

    // Panel manager
    PanelManager {
        id: panelMgr
        anchors.fill: parent
    }

    // Listen to drone state changed
    function onDroneStateChanged()
    {
        if (drone.state === DroneBase.MISSION_PLAN_EDIT)
            panelMgr.loadPanel("MissionPlanEditor")
        else
        if (drone.state === DroneBase.SAFETY_EDIT)
            panelMgr.loadPanel("SafetyPlanEditor")
        else
        if (drone.state === DroneBase.FLYING)
            panelMgr.loadPanel("FlightEditor")
        else
        if (drone.state === DroneBase.IDLE)
            panelMgr.loadPanel("PayloadEditor")
    }

    Component.onCompleted: drone.stateChanged.connect(onDroneStateChanged)
}
