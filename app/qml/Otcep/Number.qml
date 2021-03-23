import QtQuick 2.14
import QtQuick.Layouts 1.14
import SettingsModule 1.0

Rectangle {
    id: textField
    property alias txt: _textPut.text
    property alias textPutfocus: _textPut.focus
    Layout.fillHeight: true
    Layout.fillWidth: true
    Layout.preferredWidth: delegate.width/Settings.header.column
    height: Settings.listView.height;
    color: delegate.color
    border.width: Settings.listView.borderWidth
    Item {
        id: _lightsteelblue
        states:[
            State {
                name: "lightsteelblue"
                when: _textPut.focus===true
                PropertyChanges {
                    target: textField
                    color: delegate.items_color[4];
                }
            }
        ]
    }

    Item {
        id: _zkr_vagons
        states:[
            State {
                name: "orange"
                when: STATE_SL_VAGON_CNT!==0 &&
                      STATE_ZKR_VAGON_CNT!==0 &&
                      STATE_ZKR_VAGON_CNT>STATE_SL_VAGON_CNT
                //                      textField===state_zkr_vagon_cnt
                PropertyChanges {
                    target: state_zkr_vagon_cnt
                    color:delegate.items_color[5]
                }
            }
        ]
    }
    Item {
        id: _stra
        states:
            [
            State {
                name: "colorSTRA"
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
        font.pointSize: parent.height/2
        fontSizeMode: Text.Fit
    }    
}
