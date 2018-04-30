import QtQuick 2.5
import QtQuick.Controls 1.4
import Components 1.0
import "."
import "./widgets"

// Status bar
Rectangle {
    id: toolBar
    color: Theme.toolBarColor
    property bool showDroneStatus: false

    // Drone status widget
    DroneStatusWidget {
        id: droneStatusWidget
        width: (parent.width-Theme.controlPanelWidth)/2
        height: parent.height
        opacity: showDroneStatus ? 1 : 0
        visible: opacity > 0
        currentDrone: MASTERCONTROLLER.currentDrone
        function onDroneReady()
        {
            if ((typeof MASTERCONTROLLER.currentDrone !== "undefined") && (MASTERCONTROLLER.currentDrone !== null))
                droneStatusWidget.currentDrone = MASTERCONTROLLER.currentDrone
        }
        Component.onCompleted: MASTERCONTROLLER.currentDroneChanged.connect(onDroneReady)
        Behavior on opacity {
            NumberAnimation {duration: Theme.standardAnimationDuration}
        }
    }

    // Mission name
    StandardText {
        anchors.centerIn: parent
        font.pixelSize: Theme.largeFontSize
        font.bold: true
        text: qsTr("Spy'C by THALES")
    }

    // Quit button
    ImageButton {
        anchors.right: parent.right
        anchors.rightMargin: 4
        anchors.verticalCenter: parent.verticalCenter
        source: "qrc:/icons/ico-shutdown.png"
        onClicked: dialogMgr.showDialog(SpyC.EXIT_SPYC)
    }
}
