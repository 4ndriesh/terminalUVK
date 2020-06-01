import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
ColumnLayout {
    id:columnListView
    property alias visiblePB: pb1.visible
    property bool visibleIcon: false
    DialogWin{
        id: dialogAndroid

    }
    Frame {
        Layout.fillWidth: true
        ButtonPanel {
            id: controlPanel
        }
    }
    Frame {
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
            currentIndex: -1
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

    ProgressBar {
        id: pb1
        Layout.fillWidth: true
        minimumValue: 0
        maximumValue: 100
        value: 0
        visible: false
    }

    Timer {
        id: simpletimer
        interval: 100
        repeat: true
        running: false
        onTriggered: pb1.value < pb1.maximumValue ? pb1.value += 1.0 : pb1.value = pb1.minimumValue
    }
    Connections {
        target: otcepsModel
        onSendStopProgressBar: {
            simpletimer.running=false;
            pb1.visible=false;
        }
    }
    Connections {
        target: otcepsModel
        onSendStartProgressBar: {
            visiblePB=true
            simpletimer.running=true;
        }
    }


}

