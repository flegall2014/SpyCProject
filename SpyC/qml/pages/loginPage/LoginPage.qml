import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import Components 1.0
import "../../widgets"
import "../.."

Rectangle {
    id: root
    color: Theme.backgroundColor
    width: Theme.controlPanelWidth
    signal loginClicked()

    TabView {
        anchors.fill: parent
        // Login tab
        Tab {
            title: qsTr("Login")
            LoginTab {
                id: loginTab
                anchors.fill: parent
                anchors.margins: 8
                onLoginClicked: root.loginClicked()
            }
        }

        // Settings
        Tab {
            title: qsTr("Settings")
            SettingsTab {
                id: settingsTab
                anchors.fill: parent
                anchors.margins: 8
            }
        }

        style: Theme.loginPageTabViewStyle
    }

    states: State {
        name: "hidden"
        PropertyChanges {
            target: loginPage
            opacity: 0
        }
    }
    transitions: Transition {
        NumberAnimation {duration: Theme.standardAnimationDuration; properties: "opacity"}
    }
}
