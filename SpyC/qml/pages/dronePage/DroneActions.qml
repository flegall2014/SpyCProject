import QtQuick 2.0
import Components 1.0
import "../../widgets"
import "../.."

Grid {
    id: droneActions
    columns: 3
    property variant targetDrone
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            anchors.centerIn: parent
            source: "qrc:/icons/ico-safety.svg"
            checkable: true
            checked: targetDrone.editMode === DroneBase.SAFETY_EDIT
            onClicked: targetDrone.editMode = DroneBase.SAFETY_EDIT
            enabled: targetDrone.state !== DroneBase.FLYING
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
            checked: targetDrone.editMode === DroneBase.MISSION_PLAN_EDIT
            onClicked: targetDrone.editMode = DroneBase.MISSION_PLAN_EDIT
            enabled: targetDrone.state !== DroneBase.FLYING
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
            enabled: targetDrone.state !== DroneBase.FLYING
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
            enabled: targetDrone.state === DroneBase.FLYING
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
            enabled: targetDrone.state === DroneBase.FLYING
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
