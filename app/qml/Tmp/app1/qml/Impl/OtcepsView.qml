import QtQuick 2.14
import Base 1.0

Item {
    id: _otcepView
    ListView {
        id: listView
        anchors.fill: parent
        clip: true
        model: otcepsModel1

        header: HeaderOtcepsView {z:10}
        headerPositioning: ListView.OverlayHeader
        delegate: DelegateOtcepView{}

        currentIndex: otcepsModel.qmlVisibleObject ? otcepsModel.qmlCurentIndex:-1

        highlightFollowsCurrentItem: true
        highlightRangeMode: ListView.StrictlyEnforceRange
        preferredHighlightBegin: height/3
        preferredHighlightEnd: height/3
        focus: true

        Keys.onPressed: { if (event.key === Qt.Key_Up || event.key === Qt.Key_Down)
                event.accepted = true; }
    }
}


