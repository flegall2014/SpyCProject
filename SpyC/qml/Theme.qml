pragma Singleton
import QtQuick 2.5
import QtQuick.Controls.Styles 1.4
import "widgets"

Item {
    // Colors
    property color backgroundColor: "#202F42"
    property color statusBarColor: "#202F42"
    property color toolBarColor: "#202F42"
    property color nominalColor: "#00FF01"
    property color warningColor: "orange"
    property color criticalColor: "red"
    property color defaultPanelBkgColor: "#202F42"
    property color defaultPanelBorderColor: "white"
    property color buttonBkgColor: "lightgray"
    property color defaultFontColor: "white"
    property color invertDefaultFontColor: "black"
    property color checkedColor: "red"
    property color disabledColor: "black"
    property color safetyColor: "red"
    property color missionPlanColor: "green"
    property color videoBkgColor: "black"
    property color defaultButtonColor: "steelblue"

    // Sizes
    property int toolBarHeight: 64
    property int controlPanelWidth: 316
    property int commonAreaHeight: 316
    property int buttonSize: toolBarHeight-8
    property int alertDeleagateHeight: 32
    property int wayPointDelegateHeight: 48
    property int mapOrVideoThumbnailSize: 256
    property int goNextIconSize: 160

    // Font
    property string standardFont: "Segoe UI"
    property int standardFontSize: 14
    property int veryLargeFontSize: 36
    property int largeFontSize: 18
    property int mediumFontSize: 13
    property int smallFontSize: 12
}
