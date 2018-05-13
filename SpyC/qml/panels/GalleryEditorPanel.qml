import QtQuick 2.5
import QtQuick.Controls 1.4
import Components 1.0
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
            delegate: Rectangle {
                height: parent.height
                width: parent.height
                color: index === targetDrone.galleryModel.currentScreenCapIndex ? Theme.currentSnapShotBorderColor : "transparent"
                border.color: Theme.currentSnapShotBorderColor

                // Top bar
                Item {
                    id: topBar
                    width: parent.width
                    height: Theme.galleryViewToolBarHeight

                    // Snapshot index
                    StandardText {
                        anchors.left: parent.left
                        anchors.leftMargin: 4
                        anchors.verticalCenter: parent.verticalCenter
                        text: index+1
                        font.bold: true
                    }

                    // Close button
                    ImageButton {
                        anchors.right: parent.right
                        anchors.rightMargin: 4
                        anchors.top: parent.top
                        width: parent.height
                        height: parent.height
                        source: "qrc:/icons/ico-close.svg"
                        onClicked: {
                            targetDrone.galleryModel.currentScreenCapIndex = index
                            dialogMgr.showDialog(SpyC.CONFIRM_REMOVE_CAPTURE)
                        }
                    }
                }

                Item {
                    id: imgContainer
                    anchors.top: topBar.bottom
                    anchors.bottom: bottomBar.top
                    width: parent.width

                    Image {
                        id: image
                        anchors.fill: parent
                        fillMode: Image.PreserveAspectFit
                        source: SPYC.fromLocalFile(filePath)
                        asynchronous: true

                        MouseArea {
                            anchors.fill: parent
                            onClicked: targetDrone.galleryModel.currentScreenCapIndex = index
                        }
                    }
                }

                // Bottom bar
                Item {
                    id: bottomBar
                    width: parent.width
                    height: Theme.galleryViewToolBarHeight
                    anchors.bottom: parent.bottom
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
