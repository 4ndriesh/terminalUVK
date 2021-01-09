import QtQuick 2.14
import Message 1.0

Rectangle {

    color: "#FFFFE0"
    height: 50
    ListView{
        id:listMsgView
        anchors.fill: parent
        model:otcepsModel.listMsg
        delegate: MsgDelegate{}
    }
    Timer {
        id: msgTimer
        interval: 1000
        repeat: true
        running: manageModel.timerDelMsg
        onTriggered: manageModel.deleteMsg();
    }
}
