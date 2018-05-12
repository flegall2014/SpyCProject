import QtQuick 2.5
import QtPositioning 5.6
import QtLocation 5.6
import QtQuick.Controls 1.4
import Components 1.0
import "../.."

// Exclusion area
MapItemView {
    delegate: Component {
        MapCircle {
            id: circleShape
            color: Theme.exclusionAreaColor
            border.color: Theme.exclusionAreaBorderColor
            opacity: Theme.exclusionAreaOpacity
            visible: false
            property variant targetShape: shape
            center {
                latitude: shape.center.latitude
                longitude: shape.center.longitude
            }
            function onCurrentPathChanged()
            {
                circleShape.radius = targetShape.radius
            }
            onTargetShapeChanged: {
                if ((typeof targetShape !== "undefined") && (targetShape !== null))
                {
                    circleShape.visible = (targetShape.type === BaseShape.CIRCLE)
                    if (circleShape.visible)
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
}
