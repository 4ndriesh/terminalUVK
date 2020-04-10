import QtQuick 2.0
import QtQuick.Controls 2.4

Item {
    id: icons
    width: 50
    height: 50
    property var src
    Image {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        source: src
    }

}
