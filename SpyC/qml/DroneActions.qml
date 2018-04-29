import QtQuick 2.0
import Components 1.0

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
            checked: drone.state === DroneBase.SAFETY_EDIT
            onClicked: drone.state = DroneBase.SAFETY_EDIT
            enabled: drone.state !== DroneBase.FLYING
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
            checked: drone.state === DroneBase.MISSION_PLAN_EDIT
            onClicked: drone.state = DroneBase.MISSION_PLAN_EDIT
            enabled: drone.state !== DroneBase.FLYING
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
        }
    }
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            anchors.centerIn: parent
            source: "qrc:/icons/ico-measurement.svg"
            enabled: false
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
        }
    }
}
