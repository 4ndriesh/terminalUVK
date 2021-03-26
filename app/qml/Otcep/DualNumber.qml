import QtQuick 2.0
import QtQuick.Layouts 1.14
import SettingsModule 1.0

Rectangle{
    Layout.fillHeight: true
    Layout.preferredWidth: (delegate.width/Settings.header.column)*2
    Layout.fillWidth: true
    height: Settings.listView.height
    color: delegate.color
    border.width: Settings.listView.borderWidth



    Item {
        id: _join
        states:
            [
            State {
                name: "joinoffSP"
                when: STATE_SP!==STATE_SP_F || STATE_GAC_ACTIVE===1
                PropertyChanges {
                    target: state_sp_f
                    visible: true
                }
            },
            State {
                name: "joinSP"
                when: STATE_SP===STATE_SP_F && STATE_GAC_ACTIVE===0
                PropertyChanges {
                    target: state_sp_f
                    visible: false
                }
            }

        ]
    }
    Item {
        id: _joinvagon
        states:
            [
            State {
                name: "joinvagon"
                when: STATE_SL_VAGON_CNT_PRED!==0 ? STATE_SL_VAGON_CNT_PRED===STATE_ZKR_VAGON_CNT:STATE_SL_VAGON_CNT===STATE_ZKR_VAGON_CNT
                PropertyChanges {
                    target: state_zkr_vagon_cnt
                    visible: false
                }
            },
            State {
                name: "joinoffvagon"
                when:STATE_SL_VAGON_CNT_PRED!==0 ? STATE_SL_VAGON_CNT_PRED!==STATE_ZKR_VAGON_CNT:STATE_SL_VAGON_CNT!==STATE_ZKR_VAGON_CNT
                PropertyChanges {
                    target: state_zkr_vagon_cnt
                    visible: true
                }
            }
        ]
    }


}
