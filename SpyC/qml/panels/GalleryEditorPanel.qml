import QtQuick 2.5
import ".."
import "../widgets"

PanelBase {
    id: root
    panelContents: Item {
        anchors.fill: parent

        ListView {
            anchors.fill: parent
            orientation: Qt.Horizontal
            model: root.droneValid() ? targetDrone.galleryModel : undefined
            spacing: 8
            delegate: Item {
                height: parent.height
                width: parent.height

                Rectangle {
                    anchors.fill: parent
                    color: "orange"
                }

                Image {
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                    source: SPYC.fromLocalFile(filePath)
                }
            }
        }
    }
}
