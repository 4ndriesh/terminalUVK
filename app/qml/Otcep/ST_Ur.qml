import QtQuick 2.14
import QtQuick.Layouts 1.14
import SettingsModule 1.0
import Base 1.0

Number {
    id: state_sl_ur;
    property variant sl_ur: ["","О1", "N2","N3"]

    states:
        [
        State {
            name: "colorUR1"
            when: STATE_SL_UR===1
            PropertyChanges {
                target: state_sl_ur
                color: "yellow"
            }
        },
        State {
            name: "colorUR2"
            when: STATE_SL_UR===2
            PropertyChanges {
                target: state_sl_ur
                color: "red"
            }
        },
        State {
            name: "colorUR3"
            when: STATE_SL_UR===3
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
