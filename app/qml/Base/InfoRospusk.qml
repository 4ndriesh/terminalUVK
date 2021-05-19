import QtQuick 2.0

Rectangle{
    id: recInfo
    color: "#FFFFE0"
    height: 50
    visible: _info.text.length ? true:false

    TextOut{
        id:_info
    }
    Timer {
        id: timerInfo
        interval: 1000
        repeat: true
        running: true
        onTriggered: {
            _info.text=manageModel.getInfo();
        }
    }
}
