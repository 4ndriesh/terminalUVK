import QtQuick 2.14
import SettingsModule 1.0

Rectangle {
    color: Settings.listView.background
    ListView{
        id:_vagons
        anchors.fill: parent
        clip: true
        highlightFollowsCurrentItem: false
        highlightRangeMode: ListView.StrictlyEnforceRange
        preferredHighlightBegin: height/3
        preferredHighlightEnd: height/3
        model:vagonsModel
        currentIndex: vagonsModel.qmlCurrentIndex ? vagonsModel.qmlCurrentIndex:0
        interactive: false
        cacheBuffer:0
//        cacheBuffer:8000
//        snapMode:ListView.SnapOneItem
        delegate: Delegate{id:delegate}
        highlight:Highlight{z:2}

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            propagateComposedEvents: true
            acceptedButtons: Qt.LeftButton
            onClicked: mouse.accepted = false;
            onWheel: {
                if (wheel.angleDelta.y<0 && _vagons.currentItem.visible===true
                        && _vagons.currentIndex<119){
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
