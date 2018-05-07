import QtQuick 2.5
import QtQuick.Controls 1.4
import Components 1.0
import "../../widgets"
import "../.."

Item {
    id: loginPage
    opacity: 1
    visible: opacity > 0
    property bool goNextEnabled: (armyTextField.text.length > 0) && (unitTextField.text.length > 0) &&
             (missionTextField.text.length > 0) && (operatorTextField.text.length > 0)
    property alias armyText: armyTextField.text
    property alias unitText: unitTextField.text
    property alias missionText: missionTextField.text
    property alias operatorText: operatorTextField.text
    signal loginClicked()

    // Main container
    Rectangle {
        id: mainContainer
        width: parent.width
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
                height: Theme.buttonSize
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
                height: Theme.buttonSize
                anchors.top: missionOrReplayGroup.bottom
                anchors.topMargin: Theme.toolBarHeight
                anchors.horizontalCenter: parent.horizontalCenter
                StandardText {
                    id: armyTitle
                    anchors.left: parent.left
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: Theme.veryLargeFontSize
                    text: qsTr("Army")
                    width: 224
                }
                TextField {
                    id: armyTextField
                    anchors.left: armyTitle.right
                    anchors.right: parent.right
                    height: parent.height
                    font.pixelSize: Theme.veryLargeFontSize
                    text: MASTERCONTROLLER.settingController.army
                    onTextChanged: MASTERCONTROLLER.settingController.army = text
                }
            }

            // Unit
            Item {
                id: unitGroup
                width: parent.width
                height: Theme.buttonSize
                anchors.top: armyGroup.bottom
                anchors.topMargin: Theme.toolBarHeight
                anchors.horizontalCenter: parent.horizontalCenter
                StandardText {
                    id: unitTitle
                    anchors.left: parent.left
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: Theme.veryLargeFontSize
                    text: qsTr("Unit")
                    width: 224
                }
                TextField {
                    id: unitTextField
                    anchors.left: unitTitle.right
                    anchors.right: parent.right
                    height: parent.height
                    font.pixelSize: Theme.veryLargeFontSize
                    text: MASTERCONTROLLER.settingController.unit
                    onTextChanged: MASTERCONTROLLER.settingController.unit = text
                }
            }

            // Mission
            Item {
                id: missionGroup
                width: parent.width
                height: Theme.buttonSize
                anchors.top: unitGroup.bottom
                anchors.topMargin: Theme.toolBarHeight
                anchors.horizontalCenter: parent.horizontalCenter
                StandardText {
                    id: missionTitle
                    anchors.left: parent.left
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: Theme.veryLargeFontSize
                    text: qsTr("Mission")
                    width: 224
                }
                TextField {
                    id: missionTextField
                    anchors.left: missionTitle.right
                    anchors.right: parent.right
                    height: parent.height
                    font.pixelSize: Theme.veryLargeFontSize
                    text: MASTERCONTROLLER.settingController.mission
                    onTextChanged: MASTERCONTROLLER.settingController.mission = text
                }
            }

            // Operator
            Item {
                id: operatorGroup
                width: parent.width
                height: Theme.buttonSize
                anchors.top: missionGroup.bottom
                anchors.topMargin: Theme.toolBarHeight
                anchors.horizontalCenter: parent.horizontalCenter
                StandardText {
                    id: operatorTitle
                    anchors.left: parent.left
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: Theme.veryLargeFontSize
                    text: qsTr("Operator")
                    width: 224
                }
                TextField {
                    id: operatorTextField
                    anchors.left: operatorTitle.right
                    anchors.right: parent.right
                    height: parent.height
                    font.pixelSize: Theme.veryLargeFontSize
                    text: MASTERCONTROLLER.settingController.operatorName
                    onTextChanged: MASTERCONTROLLER.settingController.operatorName = text
                }
            }
        }
    }
}
