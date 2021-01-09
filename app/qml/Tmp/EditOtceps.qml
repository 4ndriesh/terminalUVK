import QtQuick 2.10
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ColumnLayout {
    Frame {
        Layout.fillWidth: true
        Layout.fillHeight: true
        Component {
            id: highlightBar
            Rectangle {
                width: 200; height: 50
                y: ListView.currentItem.y;
                Behavior on y { SpringAnimation { spring: 1; damping: 0.3 } }
            }
        }
        ListView {
            id: listView1
            currentIndex: 0
            anchors.fill: parent
            model: otcepsModelRedact
            delegate: OtcepViewDelegate{}
            clip: true
            //            highlight: highlightBar
            highlightRangeMode: ListView.StrictlyEnforceRange
            preferredHighlightBegin: height/3
            preferredHighlightEnd: height/3
            headerPositioning: ListView.OverlayHeader
            header: HeaderOtcepsView {
                z: 10
            }

            highlightFollowsCurrentItem: false
            focus: false
        }
    }
    RowLayout {
        Button{text: "Добавить"; Layout.fillWidth: true}
        Button{text: "Отправить"; Layout.fillWidth: true}

    }
}
