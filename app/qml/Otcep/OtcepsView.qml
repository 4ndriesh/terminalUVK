import QtQuick 2.14
import Base 1.0
import SettingsModule 1.0
import KeyBoard 1.0

Rectangle {
    color: Settings.listView.background
    KeyBoard{id:keyboard}
    FocusScope{
        anchors.fill: parent
        ListView {
            id: _otceps
            anchors.fill: parent
            property int prefWidthState:  width/Settings.header.column
            clip: true
            highlightFollowsCurrentItem: false
            highlightRangeMode: ListView.StrictlyEnforceRange
            preferredHighlightBegin: height/3
            preferredHighlightEnd: height/3
            model: otcepsModel
            currentIndex: manageModel.qmlCurrentIndex;
            highlight: Highlight{z:2}
            delegate: Delegate{}
            interactive: false
            cacheBuffer:0
//            cacheBuffer:8000

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                propagateComposedEvents: true
                acceptedButtons: Qt.LeftButton
//                onClicked: mouse.accepted = false;
                onDoubleClicked: {keyboard.open();}
                onWheel: {
                    if (wheel.angleDelta.y<0){
                        manageModel.keyDown(40,false);
                    }else if(wheel.angleDelta.y>0){
                        manageModel.keyDown(38,false);
                    }
                }
            }
        }
    }
}
