import QtQuick 2.5
import QtQuick.Controls 1.4
import "../../widgets"
import "../.."

Item {
    id: loginPage
    opacity: 1
    visible: opacity > 0

    // Main container
    Rectangle {
        id: mainContainer
        width: parent.width/2
        height: parent.height-2*Theme.toolBarHeight
        anchors.centerIn: parent
        color: "transparent"
        radius: 8
        border.color: "white"

        Item {
            anchors.fill: parent
            anchors.margins: 16

            // Maps
            Item {
                id: mapGroup
                width: parent.width
                height: Theme.toolBarHeight
                anchors.top: parent.top
                anchors.topMargin: Theme.toolBarHeight
                anchors.horizontalCenter: parent.horizontalCenter

                FileSelectorWidget {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    title: qsTr("Maps")
                }
            }

            // Mission
            Item {
                id: missionGroup
                width: parent.width
                height: Theme.toolBarHeight
                anchors.top: mapGroup.bottom
                anchors.topMargin: Theme.toolBarHeight
                anchors.horizontalCenter: parent.horizontalCenter

                FileSelectorWidget {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    title: qsTr("Mission")
                }
            }

            // Logs
            Item {
                id: logGroup
                width: parent.width
                height: Theme.toolBarHeight
                anchors.top: missionGroup.bottom
                anchors.topMargin: Theme.toolBarHeight
                anchors.horizontalCenter: parent.horizontalCenter

                FileSelectorWidget {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    title: qsTr("Logs")
                }
            }

            // Alerts
            Item {
                id: alertGroup
                width: parent.width
                height: Theme.toolBarHeight
                anchors.top: logGroup.bottom
                anchors.topMargin: Theme.toolBarHeight
                anchors.horizontalCenter: parent.horizontalCenter

                FileSelectorWidget {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    title: qsTr("Alerts")
                }
            }

            // Snapshots
            Item {
                id: snapShotGroup
                width: parent.width
                height: Theme.toolBarHeight
                anchors.top: alertGroup.bottom
                anchors.topMargin: Theme.toolBarHeight
                anchors.horizontalCenter: parent.horizontalCenter

                FileSelectorWidget {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    title: qsTr("Snapshots")
                }
            }
        }
    }

    // SpyRanger
    Item {
        id: leftArea
        anchors.left: parent.left
        anchors.right: mainContainer.left
        height: parent.height
        Image {
            id: spyRangerImg
            source: "qrc:/images/img-spyranger.png"
            anchors.centerIn: parent
            scale: .5
            StandardText {
                anchors.top: parent.bottom
                anchors.topMargin: Theme.standardMargin
                text: qsTr("Spy'Ranger by THALES")
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: Theme.largeFontSize
                font.bold: true
            }
            states: State {
                name: "maximized"
                PropertyChanges {
                    target: spyRangerImg
                    scale: 1
                    rotation: 360
                }
            }
            transitions: Transition {
                // Make the state changes smooth
                NumberAnimation {
                    duration: 2*Theme.standardAnimationDuration
                    properties: "scale, rotation"
                }
            }
        }
    }

    // Go next
    Item {
        id: rightArea
        anchors.left: mainContainer.right
        anchors.right: parent.right
        height: parent.height

        // Go next
        ImageButton {
            id: goNext
            anchors.centerIn: parent
            source: "qrc:/icons/ico-go-right.svg"
            enabled: appWindow.goNextEnabled
            width: Theme.goNextIconSize
            height: Theme.goNextIconSize
            onClicked: {
                MASTERCONTROLLER.updateApplicationTitle(mapTextField.text, missionTextField.text, missionTextField.text, operatorTextField.text)
                loginClicked()
            }
        }
    }

    states: State {
        name: "hidden"
        PropertyChanges {
            target: loginPage
            opacity: 0
        }
    }
    transitions: Transition {
        NumberAnimation {duration: Theme.standardAnimationDuration; properties: "opacity"}
    }

    Component.onCompleted: spyRangerImg.state = "maximized"
}
