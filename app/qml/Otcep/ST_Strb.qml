import QtQuick 2.14
import QtQuick.Layouts 1.14
import SettingsModule 1.0
import Base 1.0

Rectangle {
    id: state_gac_w_strb;
    Layout.fillHeight: true
    Layout.fillWidth: true
    Layout.preferredWidth:_otceps.prefWidthState/2
    height: Settings.listView.height;
    color: delegate.color
    border.width: Settings.listView.borderWidth

    states:
        [
        State {
            name: "colorSTRB"
            when: STATE_GAC_W_STRB===1
            PropertyChanges {
                target: state_gac_w_strb
                color: "red"
            }
        }
    ]

    TextOut
    {
        text:STATE_GAC_W_STRB? "БЛК":"";
    }
}
