import QtQuick 2.5
import "."

Rectangle {
    id: button
    signal clicked
    width: Theme.buttonSize
    height: Theme.buttonSize
    radius: 5
    border.color: enabled ? (checkable ? (checked ? Theme.checkedColor : Theme.disabledColor) : Theme.disabledColor) : Theme.invertDefaultFontColor
    border.width: checkable ? (checked ? 3 : 1) : 1
    property alias text: title.text
    antialiasing: true
    property color startColor: "white"
    property color endColor: Theme.defaultButtonColor
    property string textColor: Theme.invertDefaultFontColor
    property bool checkable: false
    property bool checked: false

    // Gradient
    gradient: Gradient {
        GradientStop { position: 0.0; color: startColor }
        GradientStop { position: 1.0; color: endColor }
    }

    // Label
    StandardText {
        id: title
        anchors.centerIn: parent
        width: parent.width
        color: textColor
    }

    Rectangle {
        color: "gray"
        anchors.fill: parent
        opacity: .5
        visible: button.enabled === false
    }

    // Handle clicks
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: parent.clicked()
    }

    // Define states
    states: State {
        name: "pressed"
        when: checkable ? checked : mouseArea.pressed
        PropertyChanges {
            target: button
            scale: .95
        }
    }
}
