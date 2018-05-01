import QtQuick 2.5
import ".."
import "../widgets"

PanelBase {
    panelContents: Item {
        anchors.fill: parent

        AltitudeWidget {
            size: 256
            anchors.centerIn: parent
        }
    }
}
