pragma Singleton
import QtQuick 2.14

Item {
    property alias contacts: _contacts
    QtObject {
        id: _contacts
        readonly property string defaultPlusIcon: "qrc:/qml/resources/plus-sign.png"
        readonly property string defaultDelIcon: "qrc:/qml/resources/minus-sign.png"
        readonly property string defaultAddUpIcon: "qrc:/qml/resources/arrow-up.png"
        readonly property string defaultAddDownIcon: "qrc:/qml/resources/arrow-down.png"
        readonly property string vkAddUpIcon: "qrc:/qml/resources/home.svg"
        readonly property string defaulticonList: "qrc:/qml/resources/list.svg"
        readonly property string defaulticonConnect: "qrc:/qml/resources/transfer.svg"
    }
}
