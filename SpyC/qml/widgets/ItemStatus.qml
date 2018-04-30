import QtQuick 2.5
import Components 1.0
import ".."

Item {
    width: 96
    height: Theme.toolBarHeight
    property alias statusText: statusLabel.text
    property int level
    property int status
    property color endColor: Theme.nominalColor

    // Label
    StandardText {
        id: statusLabel
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.verticalCenter: parent.verticalCenter
    }

    // Image
    Rectangle {
        id: indicator
        smooth: true
        radius: 8
        width: height
        height: parent.height-12
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 4

        // Gradient
        gradient: Gradient {
            GradientStop { position: 0.0; color: "white" }
            GradientStop { position: 1.0; color: endColor }
        }

        // Value
        StandardText {
            text: level + "%"
            anchors.centerIn: parent
            color: Theme.invertDefaultFontColor
        }
    }

    onStatusChanged: {
        if (status === DroneBase.NOMINAL)
            endColor = Theme.nominalColor
        else
        if (status === DroneBase.WARNING)
            endColor = Theme.warningColor
        else
            endColor = Theme.criticalColor
    }
}
