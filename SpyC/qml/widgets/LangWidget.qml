import QtQuick 2.5
import ".."

Row {
    width: french.width+us.width+saudi.width+2*spacing
    height: Theme.buttonSize
    spacing: Theme.standardSpacing
    ImageButton {
        id: french
        source: "qrc:/icons/ico-french-flag.png"
        checkable: true
        checked: MASTERCONTROLLER.settingController.langString === "FR"
        onClicked: {
            MASTERCONTROLLER.settingController.applyLanguage("FR")
        }
    }
    ImageButton {
        id: us
        source: "qrc:/icons/ico-us-flag.png"
        checkable: true
        checked: MASTERCONTROLLER.settingController.langString === "US"
        onClicked: {
            MASTERCONTROLLER.settingController.applyLanguage("US")
        }
    }
    ImageButton {
        id: saudi
        source: "qrc:/icons/ico-saudi-flag.png"
        checkable: true
        checked: MASTERCONTROLLER.settingController.langString === "SD"
        onClicked: {
            MASTERCONTROLLER.settingController.applyLanguage("SD")
        }
    }
}
