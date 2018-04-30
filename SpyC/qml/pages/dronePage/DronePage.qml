import QtQuick 2.5
import Components 1.0

ListView {
    id: listView
    interactive: false
    cacheBuffer: width > 0 ? 3*width : 0
    model: MASTERCONTROLLER.droneModel
    spacing: 3
    orientation: Qt.Horizontal
    clip: true
    property bool droneExpanded: false

    // Drone display
    delegate: DroneDisplay {
        id: droneDisplay
        width: listView.width/MASTERCONTROLLER.droneModel.droneCount
        height: listView.height
        clip: true
        function onDroneExpandedChanged()
        {
            if ((droneExpanded === false) && (droneDisplay.state === "expanded"))
                droneDisplay.state = ""
        }
        Component.onCompleted: {
            listView.droneExpandedChanged.connect(onDroneExpandedChanged)
        }
    }
}
