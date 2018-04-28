import QtQuick 2.5
import "."

Item {
    id: root

    // Background
    Rectangle {
        anchors.fill: parent
        color: Theme.defaultPanelBkgColor
    }

    // Panel title
    property alias title: panelTitle.text

    // Panel contents
    property alias panelContents: panelContents.children

    // Panel object object (from JSON)
    property variant panelObject

    // Toolbar area
    Rectangle {
        id: panelToolbar
        color: "transparent"
        border.color: Theme.defaultPanelBorderColor
        anchors.top: parent.top
        width: parent.width
        height: Theme.toolBarHeight
        StandardText {
            id: panelTitle
            anchors.left: parent.left
            anchors.leftMargin: 4
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    // Panel contents
    Item {
        id: panelContents
        width: parent.width
        anchors.top: panelToolbar.bottom
        anchors.bottom: parent.bottom
    }

    // Initialize panel (virtual)
    function initialize()
    {
        title = panelObject.displayName
    }

    // Finalize panel (virtual)
    function finalize()
    {
    }
}
