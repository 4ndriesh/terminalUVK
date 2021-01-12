pragma Singleton
import QtQuick 2.14

QtObject {
    property bool isDarkTheme: true
    readonly property color backgroundColor: "white"
    readonly property color backgroundListView: "grey"
    readonly property color themeHeaderColor: isDarkTheme ? "#607D8B" : "#b0c4de"
    readonly property color themeButtonColor: isDarkTheme ? "#607D8B" : "#b0c4de"
    readonly property color themeRegimColor: "orange"
    readonly property int baseHeight: 50
    readonly property int timeWink: 5000

    readonly property int borderWidth: 1

    readonly property real defaultOpacity: 1

}
