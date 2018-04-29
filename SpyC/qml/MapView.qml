import QtQuick 2.5
import QtQuick.Layouts 1.3
import QtPositioning 5.6
import QtLocation 5.6
import QtQuick.Controls 1.4
import QtMultimedia 5.2
import Components 1.0
import "."
import "toolbars"

// Main map
Map {
    id: mapView
    plugin: mapPlugin
    zoomLevel: 10
    property string missionPlanColor: Theme.missionPlanColor
    property string safetyColor: Theme.safetyColor
    property int blinkCount: 0
    gesture.enabled: (drone.editMode !== DroneBase.SAFETY_EDIT) && (drone.editMode !== DroneBase.MISSION_PLAN_EDIT)

    // Map plugin
    Plugin {
        id: mapPlugin
        name: "osm"
    }

    // Blink effect
    Timer {
        id: blinkTimer
        interval: 300
        repeat: true
        running: (drone.editMode === DroneBase.MISSION_PLAN_EDIT) || (drone.editMode === DroneBase.SAFETY_EDIT)
        onRunningChanged: console.log("ICI : ", running)
        onTriggered: {
            if (drone.editMode === DroneBase.MISSION_PLAN_EDIT)
                mapView.missionPlanColor = (blinkCount%2 === 0) ? Theme.missionPlanColor : "blue"
            else
            if (drone.editMode === DroneBase.SAFETY_EDIT)
                mapView.safetyColor = (blinkCount%2 === 0) ? Theme.safetyColor : "blue"
            blinkCount++
        }
    }

    // Drone marker
    MapQuickItem {
        id: droneMarker
        anchorPoint.x: vehicleItem.width  / 2
        anchorPoint.y: vehicleItem.height / 2
        coordinate: drone.position

        sourceItem: Item {
            id: vehicleItem
            width: vehicleIcon.width
            height: vehicleIcon.height
            property int size: 48

            Image {
                id: vehicleIcon
                source: "qrc:/icons/ico-drone2.svg"
                mipmap: true
                width: vehicleItem.size
                sourceSize.width: vehicleItem.size
                fillMode: Image.PreserveAspectFit
                transform: Rotation {
                    origin.x: vehicleIcon.width /2
                    origin.y: vehicleIcon.height/2
                    angle: drone.heading
                }
            }
        }
    }

    // Draw mission plan way points
    MapItemView {
        id: missionPlanWayPoints
        model: drone.missionPlanModel
        delegate: Component {
            MapCircle {
                id: circle
                property bool selected: false
                center {
                    latitude: wayPointLatitude
                    longitude: wayPointLongitude
                }
                radius: 250
                color: Theme.missionPlanColor
                border.width: 3
                MouseArea {
                    id: circleMouseArea
                    anchors.fill: parent
                    enabled: drone.editMode === DroneBase.MISSION_PLAN_EDIT
                    onPressed: {
                        circle.selected = true
                    }
                    onPositionChanged: {
                        if (circle.selected)
                        {
                            var mapped = circleMouseArea.mapToItem(mapView, mouse.x, mouse.y)
                            drone.setMissionPlanPointPosition(index, mapView.toCoordinate(Qt.point(mapped.x, mapped.y)))
                        }
                    }
                    onReleased: {
                        circle.selected = false
                    }
                }
            }
        }
    }

    // Draw mission plan polylines
    MapPolyline {
        id: missionPlanPoly
        objectName: "missionPlanPoly"
        line.width: 3
        line.color: drone.state === DroneBase.IDLE ? Theme.missionPlanColor : mapView.missionPlanColor
        function updatePolyLine()
        {
            var lines = []
            for(var i=0; i<drone.missionPlanModel.path.size(); i++)
                lines[i] = drone.missionPlanModel.path.coordinateAt(i)
            missionPlanPoly.path = lines
        }
        function onDataChanged()
        {
            if (drone.missionPlanModel.path.size() === 0)
            {
                missionPlanPoly.visible = false
                var lines = []
                missionPlanPoly.path = lines
            }
            else
            {
                missionPlanPoly.visible = true
                updatePolyLine()
                missionPlanPoly.path = lines
            }
        }

        Component.onCompleted: drone.missionPlanModel.pathChanged.connect(onDataChanged)
    }

    // Draw safety way points
    MapItemView {
        id: safetyWayPoints
        model: drone.safetyModel
        delegate: Component {
            MapCircle {
                id: circle
                property bool selected: false
                center {
                    latitude: wayPointLatitude
                    longitude: wayPointLongitude
                }
                radius: 500
                color: Theme.safetyColor
                border.width: 3
                MouseArea {
                    id: circleMouseArea
                    anchors.fill: parent
                    enabled: drone.editMode === DroneBase.SAFETY_EDIT
                    onPressed: {
                        circle.selected = true
                    }
                    onPositionChanged: {
                        if (circle.selected)
                        {
                            var mapped = circleMouseArea.mapToItem(mapView, mouse.x, mouse.y)
                            drone.setSafetyPointPosition(index, mapView.toCoordinate(Qt.point(mapped.x, mapped.y)))
                        }
                    }
                    onReleased: {
                        circle.selected = false
                    }
                }
            }
        }
    }

    // Draw polylines
    MapPolyline {
        id: safetyPoly
        objectName: "safetyPoly"
        line.width: 3
        line.color: drone.state === DroneBase.IDLE ? Theme.safetyColor : mapView.safetyColor
        function updatePolyLine()
        {
            var lines = []
            for(var i=0; i<drone.safetyModel.path.size(); i++)
                lines[i] = drone.safetyModel.path.coordinateAt(i)
            safetyPoly.path = lines
        }
        function onDataChanged()
        {
            if (drone.safetyModel.path.size() === 0)
            {
                safetyPoly.visible = false
                var lines = []
                safetyPoly.path = lines
            }
            else
            {
                safetyPoly.visible = true
                updatePolyLine()
                safetyPoly.path = lines
            }
        }
        Component.onCompleted: drone.safetyModel.pathChanged.connect(onDataChanged)
    }

    // Handle clicks
    MouseArea {
        anchors.fill: parent
        enabled: (drone.editMode === DroneBase.MISSION_PLAN_EDIT) || (drone.editMode === DroneBase.SAFETY_EDIT)

        onClicked: {
            if (drone.editMode === DroneBase.SAFETY_EDIT)
                drone.addCoordinateToSafety(mapView.toCoordinate(Qt.point(mouse.x, mouse.y)))
            else
            if (drone.editMode === DroneBase.MISSION_PLAN_EDIT)
                drone.addCoordinateToMissionPlan(mapView.toCoordinate(Qt.point(mouse.x, mouse.y)))
        }
    }

    Component.onCompleted: mapView.center = drone.initialPosition
}
