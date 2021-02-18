import QtQuick 2.14
import SettingsModule 1.0

Rectangle {
    id: _highlight
    property int yHighlite
    property int heightHighlite
    property int widthHighlite
    property bool wink
    visible: true;
    height: heightHighlite;
    y:yHighlite;
    anchors.margins: 1
    width: widthHighlite;
    color: "transparent"
    border.width: 5
    border.color: manageModel.stateBt.editing ? Settings.editColorHighlight:Settings.baseColorHighlight
    Behavior on y {SpringAnimation { spring: 2; damping: 0.4;}}
    OpacityAnimator on opacity{
        id: _opacitywink
        target: _highlight
        loops: Animation.Infinite;
        from: 0;
        to: 1;
        duration: 500
        running: wink
//        onStarted: _highlight.color="white"
        onStopped: {
            manageModel.qmlRegim(10);
            manageModel.qmlRegim(11);
            _highlight.opacity=1;
//            _highlight.color="transparent"
        }
    }
    Timer {
        id: _timerwink
        interval: Settings.timeWink
        running: wink
        onTriggered: {
            manageModel.qmlRegim(10);
            manageModel.qmlRegim(11);
        }
    }

}
