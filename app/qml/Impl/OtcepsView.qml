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
        highlightFollowsCurrentItem: true
        highlightRangeMode: ListView.ApplyRange
        preferredHighlightBegin: height/3
        preferredHighlightEnd: height/3
        focus: true
        currentIndex: manageModel.stateBt.editing ? manageModel.qmlCurentIndex:-1
        model: displayDelegateModel
        //        model: otcepsModel
        keyNavigationEnabled: false
        keyNavigationWraps: false
        header: HeaderOtcepsView {z:10}
        headerPositioning: ListView.OverlayHeader
        //        delegate: DelegateOtcepView{}
    }

    DelegateModel {
        id: displayDelegateModel

        delegate: DelegateOtcepView{id: delegate}
        model: otcepsModel
        groups: [
            DelegateModelGroup {
                includeByDefault: true
                name: "displayField"
            }
        ]

        filterOnGroup: "displayField"
    }
    Connections{
        target: manageModel
        function onTextInputChanged(){
            var rowCount = otcepsModel.rowCount();
            displayDelegateModel.items.removeGroups(0,displayDelegateModel.items.count,"displayField")
            for( var i = 0;i < rowCount;i++ ) {
                var entry = otcepsModel.get(i);

                if(entry.STATE_ENABLED ===true) {
                    console.log(entry.STATE_SP)
                    displayDelegateModel.items.insert(entry, "displayField");
                }
            }

        }
    }


}


