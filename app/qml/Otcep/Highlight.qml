import QtQuick 2.14
import SettingsModule 1.0
import Base 1.0

Rectangle {
    id: _highlight

    property bool wink:manageModel.stateBt.wink_Cursor

    height: _otceps.currentItem.height;
    width: _otceps.width;

    color: "transparent"

    border.width: 5
    border.color: Settings.highlight.base

    y:_otceps.currentItem.y;
    Behavior on y {SpringAnimation { spring: 2; damping: 0.4;}}

    TextOut{text:manageModel.msgEvent;}

    Opacity{target:_highlight}

    TimerWink{running: wink}
}
