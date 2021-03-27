import QtQuick 2.14
import QtQuick.Layouts 1.14
import SettingsModule 1.0
import Base 1.0

Rectangle {
    id: state_sl_ur;
    property variant sl_ur: ["","О1", "N2","N3"]
    Layout.fillHeight: true
    Layout.fillWidth: true
    Layout.preferredWidth: _otceps.prefWidthState
    height: Settings.listView.height;
    color: delegate.color
    border.width: Settings.listView.borderWidth

    states:
        [
        State {
            name: "colorUR1"
            when: STATE_SL_UR===1 && textField===state_sl_ur
            PropertyChanges {
                target: state_sl_ur
                color: "yellow"
            }
        },
        State {
            name: "colorUR2"
            when: STATE_SL_UR===2 && textField===state_sl_ur
            PropertyChanges {
                target: state_sl_ur
                color: "red"
            }
        },
        State {
            name: "colorUR3"
            when: STATE_SL_UR===3 && textField===state_sl_ur
            PropertyChanges {
                target: state_sl_ur
                color: "red"
            }
        }
    ]

    TextOut
    {
        text:sl_ur[STATE_SL_UR]
    }
}
