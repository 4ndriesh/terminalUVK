import QtQuick 2.14
import Base 1.0
import SettingsModule 1.0
import QtQuick.Controls 2.3
import QtQuick.VirtualKeyboard 2.1

Rectangle {
    id: _otcepView
    color: Settings.backgroundListView
    ListView {
        id: listView
        anchors.fill: parent
        clip: true
        highlightFollowsCurrentItem: true
        highlightRangeMode: ListView.StrictlyEnforceRange
        preferredHighlightBegin: height/3
        preferredHighlightEnd: height/3
        focus: true
        currentIndex: manageModel.stateBt.editing ? manageModel.qmlCurentIndex:-1
        model: otcepsModel

        keyNavigationEnabled: false
        keyNavigationWraps: true

        header: HeaderOtcepsView {z:10}
        headerPositioning: ListView.OverlayHeader
        delegate: DelegateOtcepView{}
    }    
}


