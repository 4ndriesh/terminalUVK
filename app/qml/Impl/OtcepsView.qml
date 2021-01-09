import QtQuick 2.14
import Base 1.0

Item {
    id: _otcepView
    ListView {
        id: listView
        anchors.fill: parent
        clip: true
        highlightFollowsCurrentItem: true
        highlightRangeMode: ListView.StrictlyEnforceRange
        preferredHighlightBegin: height/3
        preferredHighlightEnd: height/3
        focus: true
        currentIndex: manageModel.qmlVisibleObject ? manageModel.qmlCurentIndex:-1
        model: otcepsModel

        header: HeaderOtcepsView {z:10}
        headerPositioning: ListView.OverlayHeader
        delegate: DelegateOtcepView{}

        Keys.onPressed: { if (event.key === Qt.Key_Up || event.key === Qt.Key_Down)
                event.accepted = true; }
    }
}


