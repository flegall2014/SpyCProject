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
                    width: droneDisplay.state === "expanded" ? parent.width/2 : parent.width
                    height: droneDisplay.state === "expanded" ? parent.height : parent.height/2
                    z: 0
                    targetDrone: drone

                    // Toolbar loader
                    Loader {
                        id: toolBarLoader
                        width: parent.width
                        height: Theme.toolBarHeight
                        z: 1000
                        anchors.top: parent.top
                        states: [
                            State {
                                name: "default"
                                when: (MASTERCONTROLLER.currentDrone !== null) && (targetDrone.workMode === targetDrone.defaultWorkMode)
                                PropertyChanges {
                                    target: toolBarLoader
                                    source: "qrc:/qml/toolbars/DroneDefaultToolBar.qml"
                                }
                            },
                            State {
                                name: "missionPlanEdit"
                                when: targetDrone.workMode === DroneBase.MISSION_PLAN_EDIT
                                PropertyChanges {
                                    target: toolBarLoader
                                    source: "qrc:/qml/toolbars/MissionPlanToolBar.qml"
                                }
                            },
                            State {
                                name: "safetyEdit"
                                when: targetDrone.workMode === DroneBase.SAFETY_EDIT
                                PropertyChanges {
                                    target: toolBarLoader
                                    source: "qrc:/qml/toolbars/SafetyToolBar.qml"
                                }
                            }
                        ]
                        onLoaded: item.targetDrone = targetDrone
                    }

                    states: [
                        State {
                            name: "mapMaximized"
                            PropertyChanges {
                                target: mapView
                                width: root.width
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
                            name: "mapMinimized"
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
                            properties: "x, y, width, height, opacity"
                        }
                    }
                }

                // Video view
                VideoView {
                    id: videoView
                    targetDrone: drone
                    x: droneDisplay.state === "expanded" ? mapView.width : 0
                    y: droneDisplay.state === "expanded" ? 0 : mapView.height
                    z: 0
                    width: droneDisplay.state === "expanded" ? parent.width/2 : parent.width
                    height: droneDisplay.state === "expanded" ? parent.height : parent.height/2

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

                    // Maximize
                    ImageButton {
                        anchors.right: parent.right
                        anchors.rightMargin: 4
                        anchors.top: parent.top
                        anchors.topMargin: 4
                        visible: droneDisplay.state === "expanded" && mapView.state !== "mapMaximized"
                        source: mapView.state === "" ? "qrc:/icons/ico-maximized.png" : "qrc:/icons/ico-minimized.png"
                        onClicked: {
                            if (mapView.state === "")
                                mapView.state = "mapMinimized"
                            else
                                mapView.state = ""
                        }
                    }
                }
            }
        }
    }

    // States
    states: [
        State {
            name: "expanded"
            when: MASTERCONTROLLER.currentDrone === targetDrone
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
        }
    ]

    transitions: Transition {
        // Make the state changes smooth
        NumberAnimation {
            duration: Theme.standardAnimationDuration
            properties: "width, height, contentX, opacity"
        }
    }
}
