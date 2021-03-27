import QtQuick 2.14
import QtQuick.Layouts 1.14
import SettingsModule 1.0
import Base 1.0

Rectangle {
    id: state_sl_vagon_cnt;
    Layout.fillHeight: true
    Layout.fillWidth: true
    Layout.preferredWidth:_otceps.prefWidthState
    height: Settings.listView.height;
    color: delegate.color
    border.width: Settings.listView.borderWidth

    states:
        [
        State {
            name: "lightsteelblue"
            when: STATE_LOCATION===1 && delegate.ListView.isCurrentItem && manageModel.focus===2
            PropertyChanges {
                target: state_sl_vagon_cnt
                focus:true
                color:"lightsteelblue"
            }
        }
    ]

    TextOut
    {
        text:STATE_SL_VAGON_CNT ? STATE_SL_VAGON_CNT:"";
    }
    TextOut {
        anchors.margins: 5
        verticalAlignment: Text.AlignBottom
        horizontalAlignment: Text.AlignRight
        font.pointSize: parent.height/4
        text: STATE_SL_VAGON_CNT_PRED ? STATE_SL_VAGON_CNT_PRED:"";
    }
}
