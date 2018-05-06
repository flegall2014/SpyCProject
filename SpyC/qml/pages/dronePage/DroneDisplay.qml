import QtQuick 2.5
import QtPositioning 5.6
import QtLocation 5.6
import QtQuick.Controls 1.4
import Components 1.0
import "../../widgets"
import "../.."

Rectangle {
    id: droneDisplay
    border.color: (targetDrone.globalStatus === DroneBase.NOMINAL) ? Theme.nominalColor : (targetDrone.globalStatus === DroneBase.WARNING ? Theme.warningColor : Theme.criticalColor)
    border.width: 3
    color: Theme.backgroundColor
    property variant targetDrone
    Item {
        anchors.fill: parent
        anchors.margins: parent.border.width

        // Common area
        CommonArea {
            id: commonArea
            height: 0
            opacity: 0
            anchors.bottom: parent.bottom
            width: parent.width
            targetDrone: drone
        }

        // Control Panel
        ControlPanel {
            id: controlPanel
            width: 0
            opacity: 0
            anchors.right: parent.right
            anchors.bottom: commonArea.top
            anchors.top: parent.top
            targetDrone: drone
        }

        Item {
            id: root
            anchors.left: parent.left
            anchors.right: controlPanel.left
            anchors.bottom: commonArea.top
            anchors.top: parent.top

            // Drone status widget
            DroneStatusWidget {
                id: droneStatusWidget
                width: parent.width
                height: Theme.toolBarHeight
                targetDrone: drone
                opacity: 1
                visible: opacity > 0
            }

            Item {
                width: parent.width
                anchors.top: droneStatusWidget.bottom
                anchors.bottom: parent.bottom

                // Map view
                MapView {
                    id: mapView
                    width: parent.width
                    height: parent.height/2
                    z: 0
                    targetDrone: drone

                    // Toolbar loader
                    Loader {
                        id: toolBarLoader
                        width: parent.width
                        height: Theme.toolBarHeight
                        z: 1000
                        anchors.top: parent.top
                        onLoaded: item.targetDrone = targetDrone
                        function onWorkModeChanged()
                        {
                            if (targetDrone.workMode === DroneBase.MISSION_PLAN_EDIT)
                                toolBarLoader.source = "qrc:/qml/toolbars/MissionPlanToolBar.qml"
                            else
                            if (targetDrone.workMode === DroneBase.SAFETY_EDIT)
                                toolBarLoader.source =  "qrc:/qml/toolbars/SafetyToolBar.qml"
                            else
                                toolBarLoader.source = ""
                        }
                        Component.onCompleted: targetDrone.workModeChanged.connect(onWorkModeChanged)
                    }
                }

                // Video view
                VideoView {
                    id: videoView
                    targetDrone: drone
                    x: 0
                    y: mapView.height
                    z: 0
                    width: parent.width
                    height: parent.height/2

                    // Drone state changed
                    function onDroneStateChanged()
                    {
                        if (targetDrone.state === DroneBase.FLYING)
                            videoView.play()
                        else
                            videoView.stop()
                    }
                    Component.onCompleted: {
                        targetDrone.stateChanged.connect(onDroneStateChanged)
                    }
                }

                // Swith carto/video
                ImageButton {
                    id: switchButton
                    anchors.left: parent.left
                    anchors.leftMargin: 4
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 4
                    source: "qrc:/icons/ico-swap.svg"
                    visible: (MASTERCONTROLLER.currentDrone !== null) && (targetDrone === MASTERCONTROLLER.currentDrone)
                    onClicked: {
                        if (droneDisplay.state === "map_maximized")
                            droneDisplay.state = "map_minimized"
                        else
                        if (droneDisplay.state === "map_minimized")
                             droneDisplay.state = "map_maximized"
                    }
                }
            }
        }
    }

    // States
    states: [
        State {
            name: "map_maximized"
            PropertyChanges {
                target: commonArea
                height: Theme.commonAreaHeight
                opacity: 1
            }
            PropertyChanges {
                target: controlPanel
                width: Theme.controlPanelWidth
                opacity: 1
            }
            PropertyChanges {
                target: droneDisplay
                width: dronePage.width
            }
            PropertyChanges {
                target: dronePage
                explicit: true
                contentX: droneDisplay.x
            }
            PropertyChanges {
                target: droneStatusWidget
                height: 0
                opacity: 0
            }
            PropertyChanges {
                target: mapView
                width: root.width
                height: parent.height
                x: 0
                y: 0
                z: 0
            }
            PropertyChanges {
                target: videoView
                width: Theme.mapOrVideoThumbnailSize
                height: Theme.mapOrVideoThumbnailSize
                x: mapView.width-Theme.mapOrVideoThumbnailSize
                y: mapView.height-Theme.mapOrVideoThumbnailSize
                z: 1000
            }
        },
        State {
            name: "map_minimized"
            PropertyChanges {
                target: commonArea
                height: Theme.commonAreaHeight
                opacity: 1
            }
            PropertyChanges {
                target: controlPanel
                width: Theme.controlPanelWidth
                opacity: 1
            }
            PropertyChanges {
                target: droneDisplay
                width: dronePage.width
            }
            PropertyChanges {
                target: dronePage
                explicit: true
                contentX: droneDisplay.x
            }
            PropertyChanges {
                target: droneStatusWidget
                height: 0
                opacity: 0
            }
            PropertyChanges {
                target: mapView
                width: Theme.mapOrVideoThumbnailSize
                height: Theme.mapOrVideoThumbnailSize
                x: videoView.width-Theme.mapOrVideoThumbnailSize
                y: videoView.height-Theme.mapOrVideoThumbnailSize
                z: 1000
            }
            PropertyChanges {
                target: videoView
                width: root.width
                height: parent.height
                x: 0
                y: 0
                z: 0
            }
        }
    ]

    transitions: Transition {
        // Make the state changes smooth
        NumberAnimation {
            duration: Theme.standardAnimationDuration
            properties: "x, y, width, height, contentX, opacity"
        }
    }

    function onCurrentDroneChanged()
    {
        if (MASTERCONTROLLER.currentDrone !== null)
        {
            if (targetDrone === MASTERCONTROLLER.currentDrone)
                droneDisplay.state = "map_maximized"
        }
        else droneDisplay.state = ""
    }

    Component.onCompleted: MASTERCONTROLLER.currentDroneChanged.connect(onCurrentDroneChanged)
}
