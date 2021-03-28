pragma Singleton
import QtQuick 2.14

Item {
    property alias window: _window
    property alias keyboard: _keyboard
    property alias buttonPanel: _buttonPanel
    property alias buttonColor: _buttonColor
    property alias aliveUvk: _aliveUvk
    property alias newSortList: _newSortList
    property alias listView: _listView
    property alias highlight: _highlight
    property alias header: _header
    property alias progressbar: _progressbar
    property alias rChain: _rChain

    property bool isDarkTheme: false
    QtObject {
        id: _window
//        property bool visibleInputPanel: false
        readonly property color backgroundColor: "white"

    }
    QtObject {
        id: _keyboard
        //Ресурсы для клавиатуры
//        readonly property color baseColor: isDarkTheme ? "black":"grey"
        readonly property color baseColor: isDarkTheme ? "black":"#708090"
        readonly property color textColor: isDarkTheme ? "white":"white"
        readonly property color overlay: isDarkTheme ? "white":"white"
        readonly property string fontFamily: "Cursive"

        readonly property string insertDown: "qrc:/qml/Resources/InsertDown.svg"
        readonly property string enter: "qrc:/qml/Resources/Enter.svg"
        readonly property string upArrow: "qrc:/qml/Resources/Up.svg"
        readonly property string downArrow: "qrc:/qml/Resources/Down.svg"
        readonly property string trash: "qrc:/qml/Resources/Trash.svg"
        readonly property string del: "qrc:/qml/Resources/Del.svg"
        readonly property string setCurrentOtcep: "qrc:/qml/Resources/SetCurrentOtcep.svg"
    }
    QtObject {
        id: _aliveUvk
        readonly property color baseColor: isDarkTheme ? "red" : "red"
        readonly property color actColor: isDarkTheme ? "lime" : "lime"
        readonly property string svgAliveUvk: "qrc:/qml/Resources/AliveUVK.svg"
    }
    QtObject {
        id: _newSortList
        readonly property color baseColor: isDarkTheme ? "#607D8B" : "#b0c4de"
        readonly property color actColor: isDarkTheme ? "orange" : "orange"
        readonly property string svgSortList: "qrc:/qml/Resources/NewSortList.svg"
    }

    QtObject {
        id: _buttonPanel
        //Панель кнопок
        readonly property color regimRospusk: isDarkTheme ? "#607D8B" : "lime"
        readonly property color regim: isDarkTheme ? "orange":"orange"
        readonly property int timeWink: 5000
        readonly property string fontFamily: "Cursive"

    }
    QtObject {
        id: _listView
        //Список отцепов
        readonly property color baseColor: isDarkTheme ? "#607D8B" : "#b0c4de"
        readonly property int height: 60
        readonly property int textHeight: 30
        readonly property int heightScale: 80
        readonly property int borderWidth: 1
        readonly property string fontFamily: "Cursive"
        readonly property color background: isDarkTheme ? "silver":"gainsboro"
    }
    QtObject {
        id: _buttonColor
        //Список отцепов
        readonly property color baseColor: isDarkTheme ? "#607D8B" : "#b0c4de"
        readonly property color regim: isDarkTheme ? "orange":"orange"
        readonly property color regimRospusk: isDarkTheme ? "#607D8B" : "lime"
    }
    QtObject {
        id: _highlight
        //Список отцепов
        readonly property color text: "red"
        readonly property color edit: "#ffa500"
        readonly property color base: "#00bfff"
        readonly property int timeWink: 5000
    }
    QtObject {
        id: _progressbar
        //Список отцепов
        readonly property color load: "#17a81a"
        readonly property color background: "#e6e6e6"
    }
    QtObject {
        id: _header
        //Шапка
        readonly property color baseColor: isDarkTheme ? "#607D8B" : "#b0c4de"
        readonly property int height: 80
        readonly property int column: 10
        readonly property int borderWidth: 1
        readonly property string fontFamily: "Cursive"
        readonly property color textColor: isDarkTheme ? "black":"black"
    }
    QtObject {
        id: _rChain
        //Шапка
        readonly property color background: "#ff4500"
        readonly property int borderWidth: 1
    }

}
