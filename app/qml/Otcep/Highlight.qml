import QtQuick 2.14
import SettingsModule 1.0
import Base 1.0

Rectangle {
    id: _highlight
    property bool wink:manageModel.stateBt.wink_Cursor
    height: _otceps.currentItem.height;
    width: _otceps.width;
    y:_otceps.currentItem.y;
    //    anchors.margins: 1
    color: "transparent"
    border.width: 5
    border.color: manageModel.stateBt.editing ? Settings.highlight.edit : Settings.highlight.base
    Behavior on y {SpringAnimation { spring: 2; damping: 0.4;}}

    Text {
        id: _textHighlight
        anchors.fill: parent
        color: Settings.highlight.text
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignRight
        font.family: Settings.listView.fontFamily;
        font.pointSize: _highlight.height/2
        font.bold: true
        text:manageModel.msgEvent;
    }

    Opacity{target:_highlight}
    TimerWink{running: wink}
}
