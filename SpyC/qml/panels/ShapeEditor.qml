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
        id: polygonEditorComponent
        Item {
            anchors.fill: parent
            ListView {
                width: parent.width/2
                height: Theme.coordinateDelegateHeight*currentShape.count
                anchors.centerIn: parent
                interactive: false
                model: currentShape.count
                delegate: CoordinateEditor {
                    id: delegate
                    coordinate: currentShape.path.coordinateAt(index)
                    onLatitudeChanged: {
                        currentShape.setLatitudeAtIndex(index, latitude)
                    }
                    onLongitudeChanged: {
                        currentShape.setLongitudeAtIndex(index, longitude)
                    }
                    onAltitudeChanged: {
                        currentShape.setAltitudeAtIndex(index, altitude)
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
                shapeEditorLoader.sourceComponent = polygonEditorComponent
        }
        else shapeEditorLoader.sourceComponent = null
    }
}
