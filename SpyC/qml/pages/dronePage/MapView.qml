import QtQuick 2.5
import QtQuick.Layouts 1.3
import QtPositioning 5.6
import QtLocation 5.6
import QtQuick.Controls 1.4
import Components 1.0
import QtQuick.Shapes 1.0
import "../.."
import "../../toolbars"

// Main map
Map {
    id: mapView
    plugin: mapPlugin
    zoomLevel: 10
    property bool missionPlanVisible: true
    property bool safetyVisible: true
    property variant targetDrone
    gesture.enabled: (targetDrone.workMode !== DroneBase.SAFETY_EDIT) && (targetDrone.workMode !== DroneBase.MISSION_PLAN_EDIT)
                     && (targetDrone.workMode !== DroneBase.EXCLUSION_EDIT)

    // Map plugin
    Plugin {
        id: mapPlugin
        name: "osm"
    }

    // Blink effect for safety
    Timer {
        id: safetyBlinkTimer
        interval: Theme.standardAnimationDuration
        repeat: true
        running: (targetDrone.workMode === DroneBase.SAFETY_EDIT)
        onTriggered: mapView.safetyVisible = !mapView.safetyVisible
        onRunningChanged: {
            if (running === false)
                mapView.safetyVisible = true
        }
    }

    // Blink effect for mission plan
    Timer {
        id: missionPlanBlinkTimer
        interval: Theme.standardAnimationDuration
        repeat: true
        running: (targetDrone.workMode === DroneBase.MISSION_PLAN_EDIT)
        onTriggered: mapView.missionPlanVisible = !mapView.missionPlanVisible
        onRunningChanged: {
            if (running === false)
                mapView.missionPlanVisible = true
        }
    }

    // Drone marker
    MapQuickItem {
        id: droneMarker
        anchorPoint.x: droneItem.width  / 2
        anchorPoint.y: droneItem.height / 2
        coordinate: targetDrone.position

        sourceItem: Item {
            id: droneItem
            width: droneIcon.width
            height: droneIcon.height
            property int size: 48

            Image {
                id: droneIcon
                source: "qrc:/icons/ico-drone2.svg"
                mipmap: true
                width: droneItem.size
                sourceSize.width: droneItem.size
                fillMode: Image.PreserveAspectFit
                transform: Rotation {
                    origin.x: droneIcon.width /2
                    origin.y: droneIcon.height/2
                    angle: targetDrone.heading
                }
            }
        }
    }

    // Draw mission plan way points
    MapItemView {
        id: missionPlanWayPoints
        model: targetDrone.missionPlanModel
        delegate: Component {
            MapCircle {
                id: circle
                property bool selected: false
                center {
                    latitude: wayPointLatitude
                    longitude: wayPointLongitude
                }
                radius: 250
                color: mapView.missionPlanVisible ? Theme.missionPlanColor : "black"
                border.width: 3
                MouseArea {
                    id: circleMouseArea
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    anchors.fill: parent
                    enabled: targetDrone.workMode === DroneBase.MISSION_PLAN_EDIT
                    onClicked: {
                        if (mouse.button === Qt.RightButton)
                        {
                            targetDrone.removeCoordinateFromMissionPlanAtIndex(index)
                        }
                    }
                    onPressed: {
                        targetDrone.missionPlanModel.currentPointIndex = index
                        circle.selected = true
                    }
                    onPositionChanged: {
                        if (circle.selected)
                        {
                            var mapped = circleMouseArea.mapToItem(mapView, mouse.x, mouse.y)
                            targetDrone.setMissionPlanPointPosition(index, mapView.toCoordinate(Qt.point(mapped.x, mapped.y)))
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
        line.color: mapView.missionPlanVisible ? Theme.missionPlanColor : "black"
        function updatePolyLine()
        {
            var lines = []
            for(var i=0; i<targetDrone.missionPlanModel.path.size(); i++)
                lines[i] = targetDrone.missionPlanModel.path.coordinateAt(i)
            missionPlanPoly.path = lines
        }
        function onDataChanged()
        {
            if (targetDrone.missionPlanModel.path.size() === 0)
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

        Component.onCompleted: targetDrone.missionPlanModel.pathChanged.connect(onDataChanged)
    }

    // Draw safety way points
    MapItemView {
        id: safetyWayPoints
        model: targetDrone.safetyModel
        delegate: Component {
            MapCircle {
                id: circle
                property bool selected: false
                center {
                    latitude: wayPointLatitude
                    longitude: wayPointLongitude
                }
                radius: 250
                color: mapView.safetyVisible ? Theme.safetyColor : "black"
                border.width: 3
                MouseArea {
                    id: circleMouseArea
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    anchors.fill: parent
                    enabled: targetDrone.workMode === DroneBase.SAFETY_EDIT
                    onClicked: {
                        if (mouse.button === Qt.RightButton)
                            targetDrone.removeCoordinateFromSafetyPlanAtIndex(index)
                    }
                    onPressed: {
                        targetDrone.safetyModel.currentPointIndex = index
                        circle.selected = true
                    }
                    onPositionChanged: {
                        if (circle.selected)
                        {
                            var mapped = circleMouseArea.mapToItem(mapView, mouse.x, mouse.y)
                            targetDrone.setSafetyPointPosition(index, mapView.toCoordinate(Qt.point(mapped.x, mapped.y)))
                        }
                    }
                    onReleased: {
                        circle.selected = false
                    }
                }
            }
        }
    }

    // Draw safety
    MapPolyline {
        id: safetyPoly
        objectName: "safetyPoly"
        line.width: 3
        line.color: mapView.safetyVisible ? Theme.safetyColor : "black"
        function updatePolyLine()
        {
            var lines = []
            for(var i=0; i<targetDrone.safetyModel.path.size(); i++)
                lines[i] = targetDrone.safetyModel.path.coordinateAt(i)
            safetyPoly.path = lines
        }
        function onDataChanged()
        {
            if (targetDrone.safetyModel.path.size() === 0)
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
        Component.onCompleted: targetDrone.safetyModel.pathChanged.connect(onDataChanged)
    }

    // Exclusion area
    MapItemView {
        model: targetDrone.exclusionAreaModel
        delegate: MapPolygon {
            id: polygonShape
            color: "blue"
            //visible: (targetShape.type === BaseShape.TRIANGLE) || (targetShape.type === BaseShape.RECTANGLE)
            property variant targetShape: shape
            function onCurrentPathChanged()
            {
                polygonShape.path = []
                for(var i=0; i<targetShape.count; i++)
                {
                    var coordinate = targetShape.path.coordinateAt(i)
                    polygonShape.addCoordinate(coordinate)
                }
            }
            onTargetShapeChanged: {
                targetShape.pathChanged.connect(onCurrentPathChanged)
                onCurrentPathChanged()
            }
            MouseArea {
                anchors.fill: parent
                onClicked: shape.rotate(1)
            }
        }
    }

    /*
    // Exclusion area
    MapItemView {
        model: targetDrone.exclusionAreaModel
        delegate: Component {
            MapCircle {
                id: circleShape
                radius: shape.radius
                color: "blue"
                visible: (targetShape.type === BaseShape.CIRCLE)
                center {
                    latitude: shape.center.latitude
                    longitude: shape.center.longitude
                }
                MouseArea {
                    id: exclusionArea
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    anchors.fill: parent
                    enabled: targetDrone.workMode === DroneBase.EXCLUSION_EDIT
                    onPressed: {
                        shape.selected = true
                    }
                    onReleased: shape.selected = false
                }
            }
        }
    }
    */

    // Handle clicks
    MouseArea {
        anchors.fill: parent
        enabled: (targetDrone.workMode === DroneBase.MISSION_PLAN_EDIT) || (targetDrone.workMode === DroneBase.SAFETY_EDIT) ||
                 (targetDrone.workMode === DroneBase.EXCLUSION_EDIT)

        onClicked: {
            if (targetDrone.workMode === DroneBase.SAFETY_EDIT)
                targetDrone.addCoordinateToSafety(mapView.toCoordinate(Qt.point(mouse.x, mouse.y)))
            else
            if (targetDrone.workMode === DroneBase.MISSION_PLAN_EDIT)
                targetDrone.addCoordinateToMissionPlan(mapView.toCoordinate(Qt.point(mouse.x, mouse.y)))
            else
            if (targetDrone.workMode === DroneBase.EXCLUSION_EDIT)
                targetDrone.exclusionAreaModel.addRectangle(mapView.toCoordinate(Qt.point(mouse.x, mouse.y)))
        }
    }

    Component.onCompleted: mapView.center = targetDrone.initialPosition
}
