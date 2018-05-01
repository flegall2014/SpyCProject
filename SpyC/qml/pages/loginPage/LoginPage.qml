import QtQuick 2.5
import QtQuick.Controls 1.4
import "../../widgets"
import "../.."

Item {
    id: loginPage
    opacity: 1
    visible: opacity > 0
    signal loginClicked()

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

            // Mission or replay?
            Item {
                id: missionOrReplayGroup
                width: parent.width
                height: Theme.toolBarHeight
                anchors.top: parent.top
                anchors.topMargin: Theme.toolBarHeight
                anchors.horizontalCenter: parent.horizontalCenter

                // Exclusive group
                ExclusiveGroup {
                    id: group
                }

                // Mission
                CustomRadioButton {
                    exclusiveGroup: group
                    anchors.left: parent.left
                    anchors.leftMargin: Theme.standardMargin
                    anchors.verticalCenter: parent.verticalCenter
                    labelText: qsTr("Mission")
                    checked: true
                }

                // Replay
                CustomRadioButton {
                    exclusiveGroup: group
                    anchors.right: parent.right
                    anchors.rightMargin: 8
                    anchors.verticalCenter: parent.verticalCenter
                    labelText: qsTr("Replay")
                }
            }

            // Army
            Item {
                id: armyGroup
                width: parent.width
                height: Theme.toolBarHeight
                anchors.top: missionOrReplayGroup.bottom
                anchors.topMargin: Theme.toolBarHeight
                anchors.horizontalCenter: parent.horizontalCenter
                StandardText {
                    id: armyTitle
                    anchors.left: parent.left
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: Theme.veryLargeFontSize
                    text: qsTr("Army")
                    width: 256
                }
                TextField {
                    id: armyTextField
                    anchors.left: armyTitle.right
                    anchors.right: parent.right
                    height: Theme.toolBarHeight
                    font.pixelSize: Theme.veryLargeFontSize
                    placeholderText: "NAVY"
                }
            }

            // Unit
            Item {
                id: unitGroup
                width: parent.width
                height: Theme.toolBarHeight
                anchors.top: armyGroup.bottom
                anchors.topMargin: Theme.toolBarHeight
                anchors.horizontalCenter: parent.horizontalCenter
                StandardText {
                    id: unitTitle
                    anchors.left: parent.left
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: Theme.veryLargeFontSize
                    text: qsTr("Unit")
                    width: 256
                }
                TextField {
                    id: unitTextField
                    anchors.left: unitTitle.right
                    anchors.right: parent.right
                    height: Theme.toolBarHeight
                    font.pixelSize: Theme.veryLargeFontSize
                    placeholderText: "TX-304"
                }
            }

            // Mission
            Item {
                id: missionGroup
                width: parent.width
                height: Theme.toolBarHeight
                anchors.top: unitGroup.bottom
                anchors.topMargin: Theme.toolBarHeight
                anchors.horizontalCenter: parent.horizontalCenter
                StandardText {
                    id: missionTitle
                    anchors.left: parent.left
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: Theme.veryLargeFontSize
                    text: qsTr("Mission")
                    width: 256
                }
                TextField {
                    id: missionTextField
                    anchors.left: missionTitle.right
                    anchors.right: parent.right
                    height: Theme.toolBarHeight
                    font.pixelSize: Theme.veryLargeFontSize
                    placeholderText: "MALI"
                }
            }

            // Operator
            Item {
                id: operatorGroup
                width: parent.width
                height: Theme.toolBarHeight
                anchors.top: missionGroup.bottom
                anchors.topMargin: Theme.toolBarHeight
                anchors.horizontalCenter: parent.horizontalCenter
                StandardText {
                    id: operatorTitle
                    anchors.left: parent.left
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: Theme.veryLargeFontSize
                    text: qsTr("Operator")
                    width: 256
                }
                TextField {
                    id: operatorTextField
                    anchors.left: operatorTitle.right
                    anchors.right: parent.right
                    height: Theme.toolBarHeight
                    font.pixelSize: Theme.veryLargeFontSize
                    placeholderText: "Will SMITH"
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
            enabled: (armyTextField.text.length > 0) && (unitTextField.text.length > 0) &&
                     (missionTextField.text.length > 0) && (operatorTextField.text.length > 0)
            width: Theme.goNextIconSize
            height: Theme.goNextIconSize
            onClicked: {
                MASTERCONTROLLER.updateApplicationTitle(armyTextField.text, unitTextField.text, missionTextField.text, operatorTextField.text)
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
}
