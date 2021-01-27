pragma Singleton
import QtQuick 2.14

QtObject {
    property bool isDarkTheme: false
    property bool visibleInputPanel: false
    readonly property color backgroundColor: "white"
    readonly property color backgroundListView: "gainsboro"
    readonly property color themeHeaderColor: isDarkTheme ? "#607D8B" : "#b0c4de"
    readonly property color themeBtSignalColorDAct: isDarkTheme ? "#607D8B" : "#b0c4de"
    readonly property color themeBtSignalColorAct: isDarkTheme ? "#607D8B" : "orange"
    readonly property color themeButtonColor: isDarkTheme ? "#607D8B" : "#b0c4de"
    readonly property color themeRegimColor: "orange"

    readonly property color themeColorPB: "#17a81a"
    readonly property color backgroundColorPB: "#e6e6e6"

    readonly property int baseHeight: 50
    readonly property int timeWink: 5000

    readonly property int borderWidth: 1

    readonly property real defaultOpacity: 1




}
