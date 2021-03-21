import QtQuick 2.14

Rectangle {
    id: delegateItem
    color: "#FFFFE0"
    width: listMsgView.width; height: 50
    clip: true
    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        text: modelData
        font.pointSize: 18
        color: "black"
    }
}
