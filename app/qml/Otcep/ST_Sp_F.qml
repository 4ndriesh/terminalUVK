import QtQuick 2.14
import QtQuick.Layouts 1.14
import SettingsModule 1.0
import Base 1.0

Number {
    id: state_sp_f;

    states:[
        State {
            name: "red"
            when: STATE_ERROR===1
            PropertyChanges {
                target: state_sp_f
                color:"red"
            }
        }
    ]

    TextOut
    {
        text:STATE_SP_F ? STATE_SP_F:"";
    }
}
