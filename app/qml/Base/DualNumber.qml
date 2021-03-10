import QtQuick 2.0
import QtQuick.Layouts 1.14
import SettingsModule 1.0

Rectangle{
    Layout.fillHeight: true
    Layout.preferredWidth: (listView.width/10)*2
    Layout.fillWidth: true
    height: 60
    color: delegate.color
    border.width: Settings.listView.borderWidth
    Item {
        id: _join
        states:
            [
            State {
<<<<<<< HEAD
                name: "joinoffSP"
                when: STATE_SP!==STATE_SP_F || STATE_GAC_ACTIVE===1
=======
                name: "joinoff"
                when: STATE_SP!==STATE_SP_F
>>>>>>> 1875760f9afb78816d481d890b3e5cbac2e87a5e
                PropertyChanges {
                    target: state_sp_f
                    visible: true
                }
            },
            State {
<<<<<<< HEAD
                name: "joinSP"
                when: STATE_SP===STATE_SP_F && STATE_GAC_ACTIVE===0
=======
                name: "join"
                when: STATE_SP===STATE_SP_F && STATE_GAC_ACTIVE!==1
>>>>>>> 1875760f9afb78816d481d890b3e5cbac2e87a5e
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
                when: STATE_SL_VAGON_CNT===STATE_ZKR_VAGON_CNT
                PropertyChanges {
                    target: state_zkr_vagon_cnt
                    visible: false
                }
            },
            State {
                name: "joinoffvagon"
                when: STATE_SL_VAGON_CNT!==STATE_ZKR_VAGON_CNT
                PropertyChanges {
                    target: state_zkr_vagon_cnt
                    visible: true
                }
            }
        ]
    }
}
