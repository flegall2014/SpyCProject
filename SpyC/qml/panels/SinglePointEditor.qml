import QtQuick 2.5
import QtQuick.Layouts 1.2
import "../widgets"

Item {
    id: pointEditor
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
