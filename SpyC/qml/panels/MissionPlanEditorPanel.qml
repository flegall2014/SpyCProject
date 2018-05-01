import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import ".."
import "../widgets"

PanelBase {
    panelContents: Item {
        anchors.fill: parent
        WayPointView {
            anchors.fill: parent
            model: droneValid() ? targetDrone.missionPlanModel : undefined
        }
    }
}
