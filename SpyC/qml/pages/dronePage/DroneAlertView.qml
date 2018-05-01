import QtQuick 2.5

Item {
    anchors.fill: parent
    anchors.margins: 8
    property variant targetDrone
    ListView {
        id: alertView
        model: targetDrone.alertModel
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
