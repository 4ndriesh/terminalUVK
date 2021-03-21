import QtQuick 2.14

Rectangle {
    id: showmessage
    color: "#FFFFE0"
    height: 50
    visible: listMsgView.count>0 ? true:false
    ListView{
        id:listMsgView
        anchors.fill: parent
        model:manageModel.listMsg
        delegate: MsgDelegate{}
    }
    Timer {
        id: msgTimer
        interval: listMsgView.count===1 ? 5000:10
        repeat: true
        running: manageModel.timerDelMsg
        onTriggered: manageModel.deleteMsg();
    }
}
