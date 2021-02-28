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
    border.color: manageModel.stateBt.editing ? Settings.highlight.edit:Settings.highlight.base
    Behavior on y {SpringAnimation { spring: 2; damping: 0.4;}}
    //    Rectangle{
    //        id: _rectHighlight
    //        anchors.horizontalCenter: parent.horizontalCenter
    //        anchors.verticalCenter: parent.verticalCenter
    //        height: parent.height/2
    //        width: parent.width/4
    //        visible: false
    Text {
        id: _textHighlight
        anchors.fill: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.family: Settings.listView.fontFamily;
        font.pointSize: parent.height/2
    }
    //    }
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
            manageModel.qmlRegim(11);
            manageModel.qmlRegim(10);
        }
    }
    Connections{
        target: manageModel
        function onMsgEventChanged(){
            _textHighlight.text=manageModel.msgEvent;
        }
    }
}
