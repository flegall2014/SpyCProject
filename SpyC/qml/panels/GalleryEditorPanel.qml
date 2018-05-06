import QtQuick 2.5
import QtQuick.Controls 1.4
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
                Image {
                    id: image
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                    source: SPYC.fromLocalFile(filePath)
                    asynchronous: true
                }
                BusyIndicator {
                     running: image.status === Image.Loading
                     anchors.centerIn: parent
                     style: Theme.busyIndicatorSytle
                     width: Theme.busyIndicatorSize
                     height: Theme.busyIndicatorSize
                 }
            }
        }
    }
}
