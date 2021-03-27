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
    RowLayout   {
        id: layout_sp_f
        anchors.fill: parent
        spacing: 0
        ST_Sl_Vag{id: state_sl_vagon_cnt;}
        ST_Zkr_Vag{id: state_zkr_vagon_cnt;}
    }

    Connections{
        target: manageModel
        function onTextInputChanged(){

            if (state_sl_vagon_cnt.focus===true)
            {
                STATE_SL_VAGON_CNT=manageModel.textInput;
            }
        }
    }
}
