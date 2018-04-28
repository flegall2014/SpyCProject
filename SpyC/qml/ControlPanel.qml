import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtMultimedia 5.5
import QtGraphicalEffects 1.0
import Components 1.0
import "."

Rectangle {
    color: Theme.backgroundColor
    width: 300

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
                }
            }
        }

        // Status tab
        Tab {
            title: qsTr("Status")
            Item {
                anchors.fill: parent

                // Battery image
                Image {
                    id: batteryImage
                    width: parent.width-64
                    fillMode: Image.PreserveAspectFit
                    anchors.top: parent.top
                    anchors.topMargin: 8
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "qrc:/icons/ico-battery.svg"

                    // Color overlay
                    ColorOverlay {
                        id: batteryColorOverlay
                        anchors.fill: batteryImage
                        source: batteryImage
                        color: drone.batteryStatus === DroneBase.NOMINAL ? Theme.nominalColor :
                        (drone.batteryStatus === DroneBase.WARNING ? Theme.warningColor : Theme.criticalColor)
                    }

                    // Text
                    StandardText {
                        anchors.centerIn: parent
                        font.pixelSize: Theme.veryLargeFontSize
                        color: batteryColorOverlay.color
                        font.bold: true
                        text: drone.batteryLevel + "%"
                    }
                }

                // GPS image
                Image {
                    id: gpsImage
                    width: parent.width-64
                    anchors.top: batteryImage.bottom
                    anchors.topMargin: 8
                    fillMode: Image.PreserveAspectFit
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "qrc:/icons/ico-gps.svg"

                    // Color overlay
                    ColorOverlay {
                        id: gpsColorOverlay
                        anchors.fill: gpsImage
                        source: gpsImage
                        color: drone.gpsStatus === DroneBase.NOMINAL ? Theme.nominalColor :
                        (drone.gpsStatus === DroneBase.WARNING ? Theme.warningColor : Theme.criticalColor)
                    }

                    // Text
                    StandardText {
                        anchors.centerIn: parent
                        font.pixelSize: Theme.veryLargeFontSize
                        color: gpsColorOverlay.color
                        font.bold: true
                        text: drone.gpsStrength + "%"
                    }
                }
            }
        }

        /*
        // Alerts tab
        Tab {
            title: qsTr("Alerts")
            Item {
                anchors.fill: parent
                anchors.margins: 8
                ListView {
                    id: alertView
                    model: MASTERCONTROLLER.droneAlertModel
                    anchors.fill: parent
                    spacing: 3
                    clip: true
                    delegate: Item {
                        width: alertView.width
                        height: Theme.alertDeleagateHeight
                        Rectangle {
                            anchors.fill: parent
                            color: level
                            Text {
                                anchors.left: parent.left
                                anchors.leftMargin: 4
                                anchors.verticalCenter: parent.verticalCenter
                                font.family: Theme.standardFont
                                font.pixelSize: Theme.standardFontSize
                                color: Theme.defaultFontColor
                                text: what
                            }
                            Text {
                                anchors.right: parent.right
                                anchors.rightMargin: 4
                                anchors.verticalCenter: parent.verticalCenter
                                font.family: Theme.standardFont
                                font.pixelSize: Theme.standardFontSize
                                color: Theme.defaultFontColor
                                text: date
                            }
                        }
                    }
                }
            }
        }
        */

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
