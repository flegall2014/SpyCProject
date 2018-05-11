import QtQuick 2.5
import QtQuick.Controls 1.4
import Components 1.0
import ".."
import "../widgets"

ToolBarBase {
    width: parent.width
    StandardButton {
        id: clear
        width: Theme.buttonSize
        height: Theme.buttonSize
        anchors.left: parent.left
        anchors.leftMargin: Theme.standardMargin
        anchors.verticalCenter: parent.verticalCenter
        label: qsTr("Clear")
        endColor: Theme.defaultButtonColor
        onClicked: targetDrone.clearExclusionAreas()
    }
    StandardButton {
        id: cancel
        width: Theme.buttonSize
        height: Theme.buttonSize
        anchors.right: done.left
        anchors.rightMargin: 4
        anchors.verticalCenter: parent.verticalCenter
        label: qsTr("Cancel")
        endColor: Theme.defaultButtonColor
        onClicked: targetDrone.setDefaultWorkMode()
    }
    StandardButton {
        id: done
        width: Theme.buttonSize
        height: Theme.buttonSize
        anchors.right: parent.right
        anchors.rightMargin: 4
        anchors.verticalCenter: parent.verticalCenter
        label: qsTr("Done")
        endColor: Theme.defaultButtonColor
        onClicked: targetDrone.setDefaultWorkMode()
    }
}
