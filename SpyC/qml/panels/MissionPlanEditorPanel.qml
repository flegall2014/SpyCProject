import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.2
import ".."
import "../widgets"

PanelBase {
    panelContents: Item {
        anchors.fill: parent
        WayPointView {
            anchors.left: parent.left
            anchors.right: pointEditor.left
            height: parent.height
            model: droneValid() ? targetDrone.missionPlanModel : undefined
        }
        Item {
            id: pointEditor
            anchors.right: parent.right
            width: parent.height
            height: parent.height
            Rectangle {
                anchors.fill: parent
                anchors.margins: Theme.standardMargin
                color: Theme.backgroundColor
                border.color: "green"
                Item {
                    width: parent.width
                    height: Theme.toolBarHeight
                    RowLayout {
                        anchors.centerIn: parent
                        Layout.fillWidth: true
                        ImageButton {
                            source: "qrc:/icons/ico-point.svg"
                        }
                        ImageButton {
                            source: "qrc:/icons/ico-circle.svg"
                        }
                        ImageButton {
                            source: "qrc:/icons/ico-hippodrom.svg"
                        }
                    }
                }
            }
        }
    }
}
