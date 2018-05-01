import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import Components 1.0
import "../../widgets"
import "../.."

Rectangle {
    id: root
    color: Theme.backgroundColor
    width: Theme.controlPanelWidth
    property variant targetDrone

    TabView {
        anchors.fill: parent
        // Commands tab
        Tab {
            title: qsTr("Commands")
            Item {
                anchors.fill: parent
                anchors.margins: 8
                DroneActions {
                    anchors.fill: parent
                    targetDrone: root.targetDrone
                }
            }
        }

        // Alerts tab
        Tab {
            title: qsTr("Alerts")
            Item {
                anchors.fill: parent
                anchors.margins: 8
                DroneAlertView {
                    anchors.fill: parent
                    targetDrone: root.targetDrone
                }
            }
        }

        Tab {
            title: qsTr("Settings")
        }

        style: TabViewStyle {
            frameOverlap: 1
            tab: Rectangle {
                color: styleData.selected ? "steelblue" :"lightsteelblue"
                border.color:  "steelblue"
                implicitWidth: Math.max(text.width + 4, 80)
                implicitHeight: 48
                radius: 2
                Text {
                    id: text
                    anchors.centerIn: parent
                    text: styleData.title
                    color: styleData.selected ? Theme.defaultFontColor : Theme.invertDefaultFontColor
                }
            }
            frame: Rectangle { color: "steelblue" }
        }
    }
}
