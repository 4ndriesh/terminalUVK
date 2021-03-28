import QtQuick 2.14
import QtQuick.Layouts 1.14
import SettingsModule 1.0
import Base 1.0

Number {
    id: state_zkr_vagon_cnt;

    states:[
        State {
            name: "orange"
            when: STATE_SL_VAGON_CNT!==0 &&
                  STATE_ZKR_VAGON_CNT!==0 &&
                  STATE_ZKR_VAGON_CNT>STATE_SL_VAGON_CNT
            PropertyChanges {
                target: state_zkr_vagon_cnt
                color:"orange"
            }
        }
    ]

    TextOut
    {
        text:STATE_ZKR_VAGON_CNT ? STATE_ZKR_VAGON_CNT:"";
    }
}
