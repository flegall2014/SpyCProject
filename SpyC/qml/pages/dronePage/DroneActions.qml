import QtQuick 2.0
import Components 1.0
import "../../widgets"
import "../.."

Grid {
    id: droneActions
    columns: 3
    property variant targetDrone
    signal takeSnapShot()
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            anchors.centerIn: parent
            source: "qrc:/icons/ico-safety.svg"
            checkable: true
            checked: targetDrone.workMode === DroneBase.SAFETY_EDIT
            onClicked: targetDrone.workMode = DroneBase.SAFETY_EDIT
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
            checked: targetDrone.workMode === DroneBase.MISSION_PLAN_EDIT
            onClicked: targetDrone.workMode = DroneBase.MISSION_PLAN_EDIT
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
            source: "qrc:/icons/ico-landingplan.svg"
            checkable: true
            checked: targetDrone.workMode === DroneBase.LANDING_PLAN_EDIT
            onClicked: targetDrone.workMode = DroneBase.LANDING_PLAN_EDIT
            enabled: targetDrone.state !== DroneBase.FLYING
            label: qsTr("Landing plan")
            textPosition: "below"
        }
    }
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            anchors.centerIn: parent
            source: "qrc:/icons/ico-exclude.svg"
            checkable: true
            checked: targetDrone.workMode === DroneBase.EXCLUSION_EDIT
            onClicked: targetDrone.workMode = DroneBase.EXCLUSION_EDIT
            enabled: targetDrone.state !== DroneBase.FLYING
            label: qsTr("Exclusion area")
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
            label: qsTr("Go home")
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
            label: qsTr("GoTo")
            textPosition: "below"
        }
    }
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            anchors.centerIn: parent
            source: "qrc:/icons/ico-snapshot.svg"
            enabled: targetDrone.state === DroneBase.FLYING
            label: qsTr("Snapshot")
            textPosition: "below"
            onClicked: takeSnapShot()
        }
    }
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            anchors.centerIn: parent
            source: "qrc:/icons/ico-gallery.svg"
            enabled: true
            label: qsTr("Gallery")
            textPosition: "below"
            onClicked: {
                targetDrone.galleryModel.initialize()
                targetDrone.workMode = DroneBase.GALLERY_EDIT
            }
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
}
