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
        snapMode:ListView.SnapOneItem
        delegate: Delegate{id:delegate}
        highlight:
            Rectangle {
            id: _highlight
            z:2
            width: _vagons.width;
            height: _vagons.currentItem.height;
            color: "transparent"
            border.width: 5
            border.color: Settings.highlight.base
            y:_vagons.currentItem.y;
            Behavior on y {SpringAnimation { spring: 2; damping: 0.4;}}
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            propagateComposedEvents: true
            acceptedButtons: Qt.LeftButton
            onClicked: mouse.accepted = false;
            onWheel: {
                if (wheel.angleDelta.y<0 && _vagons.currentItem.visible===true){
                    vagonsModel.qmlCurrentIndex++;
                    if(_vagons.currentItem.visible===false)vagonsModel.qmlCurrentIndex--;;
                }else if(wheel.angleDelta.y>0 && _vagons.currentItem.visible===true
                         && _vagons.currentIndex>0){
                    vagonsModel.qmlCurrentIndex--;
                    if(_vagons.currentItem.visible===false)vagonsModel.qmlCurrentIndex++;;
                }


            }
        }
    }
}
