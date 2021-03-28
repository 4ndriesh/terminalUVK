import QtQuick 2.14
import QtQuick.Layouts 1.14
import SettingsModule 1.0
import Base 1.0

Number {
    id: state_gac_w_stra;
    Layout.preferredWidth:_otceps.prefWidthState/2
    states:
        [
        State {
            name: "colorSTRA"
            when: STATE_GAC_W_STRA===1
            PropertyChanges {
                target: state_gac_w_stra
                color: "orange"
            }
        }
    ]

    TextOut
    {
        text:STATE_GAC_W_STRA? "СТР":"";
    }
}
