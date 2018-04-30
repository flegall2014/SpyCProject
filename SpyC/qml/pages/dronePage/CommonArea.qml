import QtQuick 2.5
import QtQuick.Controls 2.0
import Components 1.0
import "../.."

// Common area
Rectangle {
    id: commonArea
    color: Theme.backgroundColor
    height: Theme.commonAreaHeight

    // Panel manager
    PanelManager {
        id: panelMgr
        anchors.fill: parent
    }

    // Listen to drone state changed
    function onDroneStateChanged()
    {
        if (drone.state === DroneBase.FLYING)
            panelMgr.loadPanel("FlightEditor")
        else
            if (drone.state === DroneBase.IDLE)
                panelMgr.loadPanel("PayloadEditor")
    }

    // Listen to drone edit mode changed
    function onEditModeChanged()
    {
        if (drone.editMode === DroneBase.MISSION_PLAN_EDIT)
            panelMgr.loadPanel("MissionPlanEditor")
        else
        if (drone.editMode === DroneBase.SAFETY_EDIT)
            panelMgr.loadPanel("SafetyPlanEditor")
        else
        if (drone.editMode === DroneBase.CARTO_EDIT)
            panelMgr.loadPanel("CartoEditor")
        else
        if (drone.editMode === DroneBase.PAYLOAD_EDIT)
            panelMgr.loadPanel("PayloadEditor")
        else
            panelMgr.loadPanel("PayloadEditor")
    }

    Component.onCompleted: {
        drone.stateChanged.connect(onDroneStateChanged)
        drone.editModeChanged.connect(onEditModeChanged)
    }
}
