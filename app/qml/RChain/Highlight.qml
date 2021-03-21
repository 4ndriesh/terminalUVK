import QtQuick 2.14
import SettingsModule 1.0
import Base 1.0

Rectangle {
    id: _highlight
    property bool wink: rChain.wink_reset
    height: 40;
    anchors.margins: 1
    width: _rchain.width;
    color: "transparent"
    border.width: 5
    border.color: Settings.highlight.base

    Opacity{target:_highlight}

    Timer {
        id: _timerwink
        interval: Settings.highlight.timeWink
        running: wink
        onTriggered: {
            rChain.wink_reset=false;
        }
    }
}
