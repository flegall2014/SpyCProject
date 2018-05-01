import QtQuick 2.5
import ".."

ListView {
    id: listView
    clip: true
    property variant columnTitles: [
        "Index",
        "Latitude",
        "Longitude",
        "Altitude",
        "Ground height"
    ]
    header: Component {
        id: headerComponent
        Row {
            width: listView.width
            height: Theme.wayPointDelegateHeight
            Repeater {
                model: columnTitles
                Item {
                    width: parent.width/columnTitles.length
                    height: parent.height
                    StandardText {
                        anchors.centerIn: parent
                        text: columnTitles[index]
                    }
                }
            }
        }
    }
    delegate: Item {
        width: listView.width
        height: Theme.wayPointDelegateHeight

        Row {
            anchors.fill: parent

            // Index delegate
            WayPointDelegate {
                width: listView.width/columnTitles.length
                height: parent.height
                text: wayPointIndex
            }

            // Latitude delegate
            WayPointDelegate {
                width: listView.width/columnTitles.length
                height: parent.height
                text: wayPointLatitude
            }

            // Longitude delegate
            WayPointDelegate {
                width: listView.width/columnTitles.length
                height: parent.height
                text: wayPointLongitude
            }

            // Altitude delegate
            WayPointDelegate {
                width: listView.width/columnTitles.length
                height: parent.height
                text: "0"
            }

            // Ground height deleagate
            WayPointDelegate {
                width: listView.width/columnTitles.length
                height: parent.height
                text: "0"
            }
        }

        // Top separator
        Rectangle {
            anchors.top: parent.top
            width: parent.width
            height: 1
            color: "green"
        }

        // Bottom separator
        Rectangle {
            anchors.bottom: parent.bottom
            width: parent.width
            height: 1
            color: "green"
            visible: index === listView.model.pointCount-1
        }
    }
}
