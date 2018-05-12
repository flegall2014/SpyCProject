import QtQuick 2.5
import QtPositioning 5.6
import QtLocation 5.6
import QtQuick.Controls 1.4
import Components 1.0
import "../.."

// Exclusion area
MapItemView {
    delegate: MapPolygon {
        id: polygonShape
        color: Theme.exclusionAreaColor
        border.color: Theme.exclusionAreaBorderColor
        border.width: 3
        opacity: Theme.exclusionAreaOpacity
        visible: false
        property variant targetShape: shape
        function onCurrentPathChanged()
        {
            polygonShape.path = []
            for (var i=0; i<targetShape.count; i++)
            {
                var coordinate = targetShape.path.coordinateAt(i)
                polygonShape.addCoordinate(coordinate)
            }
        }
        onTargetShapeChanged: {
            if ((typeof targetShape !== "undefined") && (targetShape !== null))
            {
                polygonShape.visible = (targetShape.type === BaseShape.TRIANGLE) || (targetShape.type === BaseShape.RECTANGLE)
                if (polygonShape.visible)
                {
                    targetShape.pathChanged.connect(onCurrentPathChanged)
                    onCurrentPathChanged()
                }
            }
        }
        MouseArea {
            anchors.fill: parent
            onClicked: shape.rescale(1)
            onWheel: {
                if (wheel.modifiers & Qt.ControlModifier) {
                    shape.rescale(wheel.angleDelta.y > 0 ? 1 : -1)
                }
                else
                if (wheel.modifiers & Qt.ShiftModifier) {
                    shape.rotate(wheel.angleDelta.y > 0 ? 1 : -1)
                }
            }
        }
    }
}
