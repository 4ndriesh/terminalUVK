import QtQuick 2.14
import SettingsModule 1.0

Rectangle {
    color: Settings.listView.background
    ListView{
        id:_vagons
        anchors.fill: parent
        highlightFollowsCurrentItem: false
        highlightRangeMode: ListView.StrictlyEnforceRange
        preferredHighlightBegin: height/3
        preferredHighlightEnd: height/3
        clip: true
        currentIndex: vagonsModel.qmlCurrentIndex
        model:vagonsModel
        delegate: Delegate{}
        highlight:
            Rectangle {
            id: _highlight
            z:2
            width: _vagons.width;
            height: _vagons.currentItem.height;
            color: "transparent"
            border.width: 5
            border.color: "red"
            y:_vagons.currentItem.y;
            Behavior on y {SpringAnimation { spring: 2; damping: 0.4;}}
        }
    }

}
