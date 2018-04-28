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
            onClicked: MASTERCONTROLLER.missionPlanController.takeOff(drone.uid)
        }
    }
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            anchors.centerIn: parent
            source: "qrc:/icons/ico-crash.svg"
            onClicked: MASTERCONTROLLER.missionPlanController.failSafe(drone.uid)
        }
    }
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            anchors.centerIn: parent
            source: "qrc:/icons/ico-measurement.svg"
            //commandId: commands[index].comId
            //onClicked: MASTERCONTROLLER.executeCommand(commands[index].comId, drone.uid)
        }
    }
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            anchors.centerIn: parent
            source: "qrc:/icons/ico-geometry.svg"
            //commandId: commands[index].comId
            //onClicked: MASTERCONTROLLER.executeCommand(commands[index].comId, drone.uid)
        }
    }
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            anchors.centerIn: parent
            source: "qrc:/icons/ico-shape.svg"
            //commandId: commands[index].comId
            //onClicked: MASTERCONTROLLER.executeCommand(commands[index].comId, drone.uid)
        }
    }
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            anchors.centerIn: parent
            source: "qrc:/icons/ico-ground.svg"
            //commandId: commands[index].comId
            //onClicked: MASTERCONTROLLER.executeCommand(commands[index].comId, drone.uid)
        }
    }
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            anchors.centerIn: parent
            source: "qrc:/icons/ico-shape.svg"
            //commandId: commands[index].comId
            //onClicked: MASTERCONTROLLER.executeCommand(commands[index].comId, drone.uid)
        }
    }
}
