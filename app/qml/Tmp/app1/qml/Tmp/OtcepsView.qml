import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14
import QtQuick.Controls 1.4
import ListHeader 1.0

ColumnLayout {
    id:columnListView
    property alias visiblePB: pb1.visible
//    DialogWin{
//        id: dialogAndroid

//    }

    Frame {
        Layout.fillWidth: true
        ButtonPanel {
            id: controlPanel
        }
    }
    Frame {
        id: _list
        Layout.fillWidth: true
        Layout.fillHeight: true
        //        ScrollView {
        //            anchors.fill: parent
        //            horizontalScrollBarPolicy: Qt.ScrollBarAsNeeded
        //            verticalScrollBarPolicy: Qt.ScrollBarAlwaysOn
        //            clip: true
        //        }
        ListView {
            id: listView
            anchors.fill: parent
            model: otcepsModel
            currentIndex: otcepsModel.qmlVisibleObject ? otcepsModel.qmlCurentIndex:-1
            delegate: OtcepViewDelegate{}
            clip: true

            highlightFollowsCurrentItem: true
            highlight: HighlightBar{}

            highlightRangeMode: ListView.StrictlyEnforceRange
            preferredHighlightBegin: height/3
            preferredHighlightEnd: height/3
            headerPositioning: ListView.OverlayHeader
            header: HeaderOtcepsView {
                z: 10
            }
            focus: true
            Keys.onPressed: { if (event.key === Qt.Key_Up || event.key === Qt.Key_Down)
                    event.accepted = true; }
        }
    }

    ProgressBar {
        id: pb1
        Layout.fillWidth: true
        minimumValue: 0
        maximumValue: otcepsModel.qmlStatusPB.set_maximumValue
        value: otcepsModel.qmlStatusPB.set_value
        visible: otcepsModel.qmlStatusPB.set_visible
    }
}

