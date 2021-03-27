import QtQuick 2.14
import QtQuick.Layouts 1.14
import SettingsModule 1.0
import Base 1.0

Rectangle {
    id: state_zkr_vagon_cnt;
    Layout.fillHeight: true
    Layout.fillWidth: true
    Layout.preferredWidth:_otceps.prefWidthState
    height: Settings.listView.height;
    color: delegate.color
    border.width: Settings.listView.borderWidth

    states:[
        State {
            name: "orange"
            when: STATE_SL_VAGON_CNT!==0 &&
                  STATE_ZKR_VAGON_CNT!==0 &&
                  STATE_ZKR_VAGON_CNT>STATE_SL_VAGON_CNT
            PropertyChanges {
                target: state_zkr_vagon_cnt
                color:delegate.items_color[5]
            }
        }
    ]

    TextOut
    {
        text:STATE_ZKR_VAGON_CNT ? STATE_ZKR_VAGON_CNT:"";
    }
}
