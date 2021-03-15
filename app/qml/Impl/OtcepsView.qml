import QtQuick 2.14
import Base 1.0
import SettingsModule 1.0
import QtQuick.Controls 2.3
import QtQml.Models 2.14
import KeyBoard 1.0

Rectangle {
    id: _otcepView
    color: Settings.listView.background
    property bool winkCursor:manageModel.stateBt.wink_Cursor
    KeyBoard{id:keyboard}

    ListView {
        id: listView
        anchors.fill: parent
        clip: true
        highlightFollowsCurrentItem: false
        //                        highlightFollowsCurrentItem: true
        //                        highlightRangeMode: ListView.ApplyRange
        highlightRangeMode: ListView.StrictlyEnforceRange
        preferredHighlightBegin: height/3
        preferredHighlightEnd: height/3
        focus: true
        //        highlightMoveDuration: -1
        //        highlightMoveVelocity: -1
        model: otcepsModel
        keyNavigationEnabled: false
        keyNavigationWraps: false
        //        header: HeaderOtcepsView {z:3}
        headerPositioning: ListView.OverlayHeader
        highlight: Highlight{id:highliteBar;
            z:2
            wink: winkCursor
            heightHighlite: listView.currentItem.height
            yHighlite:listView.currentItem.y;
            widthHighlite:listView.width
        }
        MouseArea {
            id: mouseArea
            anchors.fill: parent
            propagateComposedEvents: true
            acceptedButtons: Qt.LeftButton
            onClicked: mouse.accepted = false;
            onDoubleClicked: {keyboard.open();}
        }

        delegate: DelegateOtcepView{id:delegate}

    }

    Connections{
        target: manageModel
        function onQmlCurrentItemChanged(){
            listView.currentIndex=manageModel.qmlCurentIndex;
        }
    }
}


