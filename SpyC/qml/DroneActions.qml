import QtQuick 2.0
import Components 1.0
import "./widgets"

Grid {
    id: droneActions
    columns: 3
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            anchors.centerIn: parent
            source: "qrc:/icons/ico-safety.svg"
            checkable: true
            checked: drone.editMode === DroneBase.SAFETY_EDIT
            onClicked: drone.editMode = DroneBase.SAFETY_EDIT
            enabled: drone.state !== DroneBase.FLYING
            label: qsTr("Safety")
            textPosition: "below"
        }
    }
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            anchors.centerIn: parent
            source: "qrc:/icons/ico-missionplan.svg"
            checkable: true
            checked: drone.editMode === DroneBase.MISSION_PLAN_EDIT
            onClicked: drone.editMode = DroneBase.MISSION_PLAN_EDIT
            enabled: drone.state !== DroneBase.FLYING
            label: qsTr("Mission plan")
            textPosition: "below"
        }
    }
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            anchors.centerIn: parent
            source: "qrc:/icons/ico-takeoff.svg"
            onClicked: dialogMgr.showDialog(SpyC.CONFIRM_TAKE_OFF)
            label: qsTr("Take off")
            textPosition: "below"
        }
    }
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            anchors.centerIn: parent
            source: "qrc:/icons/ico-crash.svg"
            enabled: drone.state === DroneBase.FLYING
            onClicked: dialogMgr.showDialog(SpyC.CONFIRM_FAILSAFE)
            label: qsTr("Fail safe")
            textPosition: "below"
        }
    }
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            anchors.centerIn: parent
            source: "qrc:/icons/ico-home.svg"
            enabled: drone.state === DroneBase.FLYING
            label: qsTr("Home")
            textPosition: "below"
        }
    }
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            anchors.centerIn: parent
            source: "qrc:/icons/ico-geometry.svg"
            enabled: false
            label: qsTr("Geometry")
            textPosition: "below"
        }
    }
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            anchors.centerIn: parent
            source: "qrc:/icons/ico-shape.svg"
            enabled: false
            label: qsTr("Loiter")
            textPosition: "below"
        }
    }
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            anchors.centerIn: parent
            source: "qrc:/icons/ico-ground.svg"
            enabled: false
            label: qsTr("Test")
            textPosition: "below"
        }
    }
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            anchors.centerIn: parent
            source: "qrc:/icons/ico-shape.svg"
            enabled: false
            label: qsTr("Test")
            textPosition: "below"
        }
    }
}
