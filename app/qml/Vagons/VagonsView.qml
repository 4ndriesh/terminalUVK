import QtQuick 2.14
import SettingsModule 1.0

Rectangle {
    color: Settings.listView.background
    ListView{
        id:_vagons
        anchors.fill: parent
        highlightFollowsCurrentItem: true
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
            width: _vagons.width; height: 60
            color: "transparent"
            enabled: true
            border.width: 5
            border.color: "red"
        }
    }

}
