import QtQuick 2.5
import QtQuick.Controls 1.4
import ".."

PanelBase {
    panelContents: Item {
        anchors.fill: parent
        TableView {
            anchors.fill: parent
            model: drone.safetyModel
            clip: true
            TableViewColumn {
                role: "wayPointIndex"
                title: "Index"
                width: 64
            }
            TableViewColumn {
                role: "wayPointLatitude"
                title: "Latitude"
                width: 128
            }
            TableViewColumn {
                role: "wayPointLongitude"
                title: "Longitude"
                width: 128
            }
        }
    }
}

