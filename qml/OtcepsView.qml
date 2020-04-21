import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4

ColumnLayout {
    id:columnListView
    Frame {
        Layout.fillWidth: true
        Layout.fillHeight: true
        Connections{
            target: otcepsModel
            onSetCurrentItem: {
                listView.currentIndex=index
            }
        }



//        ScrollView {
//            anchors.fill: parent
//            horizontalScrollBarPolicy: Qt.ScrollBarAsNeeded
//            verticalScrollBarPolicy: Qt.ScrollBarAlwaysOn
//            clip: true
            ListView {
                id: listView
                currentIndex: 0
                anchors.fill: parent
                model: otcepsModel
                delegate: OtcepViewDelegate{}
                clip: true

                highlight: HighlightBar{}
                highlightRangeMode: ListView.StrictlyEnforceRange
                preferredHighlightBegin: height/3
                preferredHighlightEnd: height/3
                headerPositioning: ListView.OverlayHeader
                header: HeaderOtcepsView {
                    z: 10
                }
                highlightFollowsCurrentItem: false
                focus: true

            }
        }
    }
//}
