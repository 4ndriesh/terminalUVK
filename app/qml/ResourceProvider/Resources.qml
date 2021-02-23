pragma Singleton
import QtQuick 2.14

Item {
    property alias contacts: _contacts
    QtObject {
        id: _contacts
//        readonly property string defaulticonList: "qrc:/qml/resources/NewList.svg"
//        readonly property string defaulticonConnect: "qrc:/qml/resources/AliveUVK.svg"
//        //Ресурсы для клавиатуры
//        readonly property color backgroundButtonColor: "black"
//        readonly property color textButtonColor: "white"
//        readonly property string insertDown: "qrc:/qml/resources/InsertDown.svg"
//        readonly property string enter: "qrc:/qml/resources/Enter.svg"
//        readonly property string upArrow: "qrc:/qml/resources/Up.svg"
//        readonly property string downArrow: "qrc:/qml/resources/Down.svg"
//        readonly property string trash: "qrc:/qml/resources/Trash.svg"
    }
}
