import QtQuick 2.0
//import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
Item {
    id: icons
    Layout.fillWidth: true
    Layout.minimumWidth: 60
    Layout.maximumWidth: 300
    Layout.minimumHeight: 60
    property var src
    Image {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        source: src
    }

}
