import QtQuick 2.14
import QtQuick.Layouts 1.14
import SettingsModule 1.0

Rectangle {
    id: textField
    property alias txt: _textPut.text
//    property alias textEnabled: _textPut.enabled
//    property alias textPutfocus: _textPut.focus


    Layout.fillHeight: true
    Layout.fillWidth: true
    Layout.preferredWidth: listView.width/10

    height: 60
    color: delegate.color
    border.width: Settings.listView.borderWidth

    Item {
        id: _stra
        states:
            [
            State {
                name: "colorSTRA"
                //                extend: "colorSTRB"
                when: STATE_GAC_W_STRA===1 && textField===state_gac_w_stra
                PropertyChanges {
                    target: state_gac_w_stra
                    color: "orange"
                }
            }
        ]
    }
    Item {
        id: _strb
        states:
            [
            State {
                name: "colorSTRB"
                when: STATE_GAC_W_STRB===1 && textField===state_gac_w_strb
                PropertyChanges {
                    target: state_gac_w_strb
                    color: "red"
                }
            }
        ]
    }
    Item {
        id: _ur
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
    }
    Text {
        id: _textPut
        anchors.fill: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.family: Settings.listView.fontFamily;
        font.pointSize: parent.height*0.5
        fontSizeMode: Text.Fit
        //        enabled: false
        //        inputMethodHints:Qt.ImhFormattedNumbersOnly
        focus: false


    }
    Connections{
        target: manageModel
        function onTextInputChanged(){
            if(manageModel.qmlCurentIndex === index
                    && textField===state_sp)
            {
                STATE_SP=manageModel.textInput;
                //                _textPut.forceActiveFocus()
            }
        }
    }
}
