import QtQuick 2.14
import SettingsModule 1.0

Rectangle {
    id: _highlight
    property bool wink
    height: 40;
    anchors.margins: 1
    width: listRChainView.width;
    color: "transparent"
    border.width: 5
    border.color: Settings.highlight.base
//    y:listRChainView.currentItem.y
//    Behavior on y {SpringAnimation { spring: 2; damping: 0.4;}}

    OpacityAnimator on opacity{
        id: _opacitywink
        target: _highlight
        loops: Animation.Infinite;
        from: 0;
        to: 1;
        duration: 500
        running: wink
        onStopped: {
            _highlight.opacity=1;
        }
    }
    Timer {
        id: _timerwink
        interval: Settings.highlight.timeWink
        running: wink
        onTriggered: {
            rChain.setWink_reset(false);
        }
    }
}
