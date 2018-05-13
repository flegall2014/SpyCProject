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
            height: Theme.standardDelegateHeight
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
        height: Theme.standardDelegateHeight

        Row {
            anchors.fill: parent

            // Index delegate
            WayPointDelegate {
                width: listView.width/columnTitles.length
                height: parent.height
                text: wayPointIndex
                color: index === listView.model.currentPointIndex ? Theme.selectedColor : Theme.defaultFontColor
            }

            // Latitude delegate
            WayPointDelegate {
                width: listView.width/columnTitles.length
                height: parent.height
                text: wayPointLatitude.toFixed(3)
                color: index === listView.model.currentPointIndex ? Theme.selectedColor : Theme.defaultFontColor
            }

            // Longitude delegate
            WayPointDelegate {
                width: listView.width/columnTitles.length
                height: parent.height
                text: wayPointLongitude.toFixed(3)
                color: index === listView.model.currentPointIndex ? Theme.selectedColor : Theme.defaultFontColor
            }

            // Altitude delegate
            WayPointDelegate {
                width: listView.width/columnTitles.length
                height: parent.height
                text: wayPointAltitude.toFixed(3)
                color: index === listView.model.currentPointIndex ? Theme.selectedColor : Theme.defaultFontColor
            }

            // Ground height deleagate
            WayPointDelegate {
                width: listView.width/columnTitles.length
                height: parent.height
                text: "0"
                color: index === listView.model.currentPointIndex ? Theme.selectedColor : Theme.defaultFontColor
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

        MouseArea {
            anchors.fill: parent
            onClicked: listView.model.currentPointIndex = index
        }
    }
}
