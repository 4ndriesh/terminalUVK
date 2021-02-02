import QtQuick 2.14
import Base 1.0
import SettingsModule 1.0
import QtQuick.Controls 2.3
import QtQml.Models 2.14

Rectangle {
    id: _otcepView
    color: Settings.backgroundListView

    Component {
        id: highlight

        Rectangle {
            z:2
            visible: true;
            width: listView.width;
            height: 55
            color: "transparent"
            border.width: 5
            border.color: manageModel.stateBt.editing ? "orange":"green"
            //              color: "red"; radius: 5
            //            y: listView.currentItem.y
            y: listView.height/3
        }
    }


    ListView {
        id: listView
        anchors.fill: parent
        clip: true
        highlight: highlight
        highlightFollowsCurrentItem: true
        //        highlightRangeMode: ListView.ApplyRange
        highlightRangeMode: ListView.StrictlyEnforceRange
        preferredHighlightBegin: height/3
        preferredHighlightEnd: height/3
        focus: true
        highlightMoveDuration: -1
        highlightMoveVelocity: -1
        currentIndex: manageModel.qmlCurentIndex
//        currentIndex: manageModel.qmlCurentIndex
        //        currentIndex: manageModel.stateBt.editing ? manageModel.qmlCurentIndex:-1
        //                model: displayDelegateModel
        model: otcepsModel
        keyNavigationEnabled: false
        keyNavigationWraps: false
        header: HeaderOtcepsView {z:3}
        headerPositioning: ListView.OverlayHeader
        delegate: DelegateOtcepView{z:1}

    }

    DelegateModel {
        id: displayDelegateModel

        delegate: DelegateOtcepView{}
        model: otcepsModel
        groups: [
            DelegateModelGroup {
                includeByDefault: true
                name: "displayField"
            }
        ]

        filterOnGroup: "displayField"
    }
    //    Connections {
    //        target: listView.model    // EDIT: I drew the wrong conclusions here, see text below!
    //        onDataChanged: {
    //            console.log("DataChanged received")
    //        }
    //    }
    //    Connections{
    //        target: manageModel
    //        function onTextInputChanged(){

    //            var rowCount = otcepsModel.rowCount();
    //            displayDelegateModel.items.removeGroups(0,displayDelegateModel.items.count,"displayField")
    //            for( var i = 0;i < rowCount;i++ ) {
    //                var entry = otcepsModel.get(i);

    //                if(entry.STATE_ENABLED ===true) {
    //                    console.log(entry.STATE_SP)
    //                    displayDelegateModel.items.insert(entry, "displayField");
    //                }
    //            }

    //        }
    //    }


}


