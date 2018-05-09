import QtQuick 2.5
import QtQuick.Controls 2.0
import Components 1.0
import "../.."

// Common area
Rectangle {
    id: commonArea
    color: Theme.backgroundColor
    height: Theme.commonAreaHeight
    property variant targetDrone

    // Panel manager
    PanelManager {
        id: panelMgr
        anchors.fill: parent
        targetDrone: commonArea.targetDrone
    }

    // Listen to drone state changed
    function onDroneStateChanged()
    {
        if (targetDrone.state === DroneBase.FLYING)
            panelMgr.loadPanel("FlightEditor")
        else
        if (targetDrone.state === DroneBase.IDLE)
            panelMgr.loadPanel("PayloadEditor")
    }

    // Listen to drone work mode changed
    function onWorkModeChanged()
    {
        if (targetDrone.workMode === DroneBase.MISSION_PLAN_EDIT)
            panelMgr.loadPanel("MissionPlanEditor")
        else
        if (targetDrone.workMode === DroneBase.SAFETY_EDIT)
            panelMgr.loadPanel("SafetyPlanEditor")
        else
        if (targetDrone.workMode === DroneBase.CARTO_EDIT)
            panelMgr.loadPanel("CartoEditor")
        else
        if (targetDrone.workMode === DroneBase.PAYLOAD_EDIT)
            panelMgr.loadPanel("PayloadEditor")
        else
        if (targetDrone.workMode === DroneBase.GALLERY_EDIT)
            panelMgr.loadPanel("GalleryEditor")
        else
        if (targetDrone.workMode === DroneBase.EXCLUSION_EDIT)
            panelMgr.loadPanel("ExclusionAreaEditor")
        else
            panelMgr.loadPanel("PayloadEditor")
    }

    Component.onCompleted: {
        targetDrone.stateChanged.connect(onDroneStateChanged)
        targetDrone.workModeChanged.connect(onWorkModeChanged)
    }
}
