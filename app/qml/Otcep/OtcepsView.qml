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
            clip: true
            highlightFollowsCurrentItem: false
            highlightRangeMode: ListView.StrictlyEnforceRange
            preferredHighlightBegin: height/3
            preferredHighlightEnd: height/3
            //        highlightMoveDuration: -1
            //        highlightMoveVelocity: -1
            model: otcepsModel
            keyNavigationEnabled: false
            keyNavigationWraps: false
            currentIndex: manageModel.qmlCurrentIndex;
//            headerPositioning: ListView.OverlayHeader
            highlight: Highlight{z:2}
            delegate: Delegate{}

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                propagateComposedEvents: true
                acceptedButtons: Qt.LeftButton
                onClicked: mouse.accepted = false;
                onDoubleClicked: {keyboard.open();}
            }
        }
    }
}


