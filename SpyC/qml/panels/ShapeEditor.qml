import QtQuick 2.5
import "../widgets"
import Components 1.0
import ".."

Item {
    property variant currentShape

    Component {
        id: circleEditorComponent
        StandardText {
            anchors.centerIn: parent
            text: currentShape.radius + " / " + currentShape.center
        }
    }
    Component {
        id: rectangleEditorComponent
        Item {
            anchors.fill: parent
            Rectangle {
                width: parent.width/2
                height: parent.height/2
                color: "green"
                anchors.centerIn: parent

                ListView {
                    anchors.fill: parent
                    interactive: false
                    model: currentShape.count
                    delegate: StandardText {
                        text: currentShape.path.coordinateAt(index).toString()
                        horizontalAlignment: Text.AlignHCenter
                    }
                }
            }
        }
    }
    Component {
        id: triangleEditorComponent
        Item {
            anchors.fill: parent
            Rectangle {
                width: parent.width/2
                height: parent.height/2
                color: "green"
                anchors.centerIn: parent

                ListView {
                    anchors.fill: parent
                    interactive: false
                    model: currentShape.count
                    delegate: StandardText {
                        text: currentShape.path.coordinateAt(index).toString()
                        horizontalAlignment: Text.AlignHCenter
                    }
                }
            }
        }
    }

    Loader {
        id: shapeEditorLoader
        anchors.fill: parent
    }

    onCurrentShapeChanged: {
        if ((typeof currentShape !== "undefined") && (currentShape !== null))
        {
            if (currentShape.type === BaseShape.CIRCLE)
                shapeEditorLoader.sourceComponent = circleEditorComponent
            else
            if (currentShape.type === BaseShape.RECTANGLE)
                shapeEditorLoader.sourceComponent = rectangleEditorComponent
            else
            if (currentShape.type === BaseShape.TRIANGLE)
                shapeEditorLoader.sourceComponent = triangleEditorComponent
        }
        else shapeEditorLoader.sourceComponent = null
    }
}
