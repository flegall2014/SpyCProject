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

    // Flip
    function flip()
    {
        flipable.state = "back"
    }

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
            anchors.right: MASTERCONTROLLER.settingController.hand === SettingController.RIGHT_HAND ? parent.right : undefined
            anchors.left: MASTERCONTROLLER.settingController.hand === SettingController.LEFT_HAND ? parent.left : undefined
            anchors.bottom: commonArea.top
            anchors.top: parent.top
            targetDrone: drone
            onTakeSnapShot: videoView.takeSnapShot()
        }

        Item {
            id: root
            anchors.left: MASTERCONTROLLER.settingController.hand === SettingController.RIGHT_HAND ? parent.left : controlPanel.right
            anchors.right: MASTERCONTROLLER.settingController.hand === SettingController.RIGHT_HAND ? controlPanel.left : parent.right
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

            Flipable {
                id: flipable
                width: parent.width
                anchors.top: droneStatusWidget.bottom
                anchors.bottom: parent.bottom

                // Define transform
                transform: Rotation {
                    id: rotation
                    origin.x: flipable.width/2
                    origin.y: flipable.height/2
                    axis.x: 1; axis.y: 0; axis.z: 0
                    angle: 0
                }

                // Define states
                states: State {
                    name: "back"
                    PropertyChanges {target: rotation; angle: 180}
                    when: flipable.flipped
                }

                transitions: Transition {
                    NumberAnimation {target: rotation; property: "angle"; duration: 2*Theme.standardAnimationDuration}
                }

                front: Item {
                    width: parent.width
                    height: parent.height

                    // Map view
                    MapView {
                        id: mapView
                        width: parent.width
                        height: parent.height/2
                        z: 0
                        targetDrone: drone
                    }

                    // Horizontal toolbar loader
                    Loader {
                        id: horizontalToolBarLoader
                        width: parent.width
                        height: Theme.toolBarHeight
                        z: Theme.zMax
                        anchors.top: parent.top
                        onLoaded: item.targetDrone = targetDrone
                        function onWorkModeChanged()
                        {
                            if (targetDrone.workMode === DroneBase.MISSION_PLAN_EDIT)
                                horizontalToolBarLoader.source = "qrc:/qml/toolbars/MissionPlanToolBar.qml"
                            else
                                if (targetDrone.workMode === DroneBase.SAFETY_EDIT)
                                    horizontalToolBarLoader.source =  "qrc:/qml/toolbars/SafetyToolBar.qml"
                                else
                                    if (targetDrone.workMode === DroneBase.LANDING_PLAN_EDIT)
                                        horizontalToolBarLoader.source =  "qrc:/qml/toolbars/LandingPlanToolBar.qml"
                                    else
                                        if (targetDrone.workMode === DroneBase.EXCLUSION_EDIT)
                                            horizontalToolBarLoader.source =  "qrc:/qml/toolbars/ExclusionAreaToolBar.qml"
                                        else
                                            horizontalToolBarLoader.source = ""
                        }
                        Component.onCompleted: targetDrone.workModeChanged.connect(onWorkModeChanged)
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
                            if (MASTERCONTROLLER.currentDrone !== null)
                                MASTERCONTROLLER.currentDrone.setDefaultWorkMode
                        }
                    }
                }
                back: Item {
                    width: parent.width
                    height: parent.height
                    Image {
                        anchors.fill: parent
                        source: HELPER.fromLocalFile(targetDrone.galleryModel.currentScreenCapPath)
                        fillMode: Image.PreserveAspectFit

                        // Close button
                        ImageButton {
                            anchors.right: parent.right
                            anchors.rightMargin: 4
                            anchors.top: parent.top
                            anchors.topMargin: 4
                            source: "qrc:/icons/ico-close.svg"
                            onClicked: flipable.state = ""
                        }
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
                z: Theme.zMax
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
                z: Theme.zMax
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

    // Current drone changed
    function onCurrentDroneChanged()
    {
        if (MASTERCONTROLLER.currentDrone !== null)
        {
            if (targetDrone === MASTERCONTROLLER.currentDrone)
                droneDisplay.state = "map_maximized"
        }
        else
        {
            flipable.state = ""
            droneDisplay.state = ""
        }
    }

    Component.onCompleted: MASTERCONTROLLER.currentDroneChanged.connect(onCurrentDroneChanged)
}
