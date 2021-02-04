import QtQuick 2.14
import Base 1.0
import SettingsModule 1.0
import QtQuick.Controls 2.3
import QtQml.Models 2.14

Rectangle {
    id: _otcepView
    color: Settings.backgroundListView




    ListView {
        id: listView
        anchors.fill: parent
        clip: true
        highlight: highlight
        highlightFollowsCurrentItem: false
        //                highlightFollowsCurrentItem: true
        //                        highlightRangeMode: ListView.ApplyRange
        highlightRangeMode: ListView.StrictlyEnforceRange
        preferredHighlightBegin: height/3
        preferredHighlightEnd: height/3
        //        focus: true
        highlightMoveDuration: -1
        highlightMoveVelocity: -1

        currentIndex: manageModel.qmlCurentIndex
        //        currentIndex: manageModel.stateBt.editing ? manageModel.qmlCurentIndex:0
        model: otcepsModel
        keyNavigationEnabled: false
        keyNavigationWraps: false
        header: HeaderOtcepsView {z:3}
        headerPositioning: ListView.OverlayHeader
        delegate: DelegateOtcepView{id: delegate}
     }
    Component {
        id: highlight

        Rectangle {
            id: _highlight
            z:2
            visible: true;
            width: listView.width;
            height: 60
            focus: true
            color: "transparent"
            border.width: 5
            border.color: manageModel.stateBt.editing ? "orange":"green"
            //              color: "red"; radius: 5
            y: listView.currentItem.y;
            Behavior on y { SpringAnimation { spring: 2; damping: 0.4} }
        }
    }
    //    Connections{
    //        target: manageModel
    //        function onQmlCurrentItemChanged(){

    //            listView.currentIndex=manageModel.qmlCurentIndex;
    //            console.log("currentIndex->",listView.currentIndex)
    //        }
    //    }
}


