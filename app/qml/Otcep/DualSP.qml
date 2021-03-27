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

    RowLayout   {
        id: layout_sp
        anchors.fill: parent
        spacing: 0

        ST_Sp{id:state_sp;}
        ST_Sp_F{id:state_sp_f}
    }

    Connections{
        target: manageModel
        function onTextInputChanged(){
            if(state_sp.focus===true)
            {
                STATE_SP=manageModel.textInput;
            }
        }
    }

}
