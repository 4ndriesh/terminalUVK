import QtQuick 2.14
import QtQuick.Layouts 1.14
import SettingsModule 1.0
import QtQml.Models 2.1
import QtQuick.Controls 1.4
import QtQuick.Controls 2.14
import QtQuick.Controls.Styles 1.4

Rectangle {
    id: delegate
    objectName: "delegate"
    //цвет в зависимости от STATE_LOCATION
    /*ЖИР и фокус при роспуске ((STATE_LOCATION == 1) && (STATE_GAC_ACTIVE==1)) ||
                             ((STATE_LOCATION == 2) && (STATE_GAC_ACTIVE==1)&&(STATE_ZKR_S_IN==1))

    цвет фона строки
    Белый STATE_LOCATION = 2
    желтый   STATE_ZKR_S_IN==1
    светло серый (STATE_LOCATION == 2) && (STATE_GAC_ACTIVE==1)
    ост - серый

    цвет фона ячейки маршрута
    Красный -STATE_ERROR
    остальн - обычн фон
stat
    EDIT когда ЖИР всегда или (STATE_LOCATION == 2)*/
    property variant sl_ur: ["","О1", "N2","N3"]
    property variant items_color: ["red", "yellow","white","silver","lightcyan"]
    width: listView.width;
    height: 60;
    visible: STATE_ENABLED ? true:false


    Item {
        id: _focusOtcepstates
        states: [
            State {
                name: "focus"
                when: STATE_IS_CURRENT===1
                StateChangeScript {
                    name: "insertIndex"
                    script: manageModel.qmlCurentIndex=STATE_NUM-1;
                }
                PropertyChanges {
                    target: delegate
                    height:80

                }
            }
        ]
    }

    Item {
        id: _error
        states:[
            State {
                name: "red"
                when: STATE_ERROR===1// bind to isCurrentItem to set the state
                PropertyChanges {
                    target: state_sp
                    color:delegate.items_color[0]
                }
                PropertyChanges {
                    target: state_sp_f
                    color:delegate.items_color[0]
                }
            }
        ]
    }

    Item {
        id: _focusYellow
        states: [
            State {
                name: "yellow"
                when: STATE_ZKR_S_IN===1
                PropertyChanges {
                    target: delegate
                    color:delegate.items_color[1]
                }
                PropertyChanges {
                    target: delegate
                    height:80
                }
            },
            State {
                name: "white"
                when: STATE_LOCATION === 1// bind to isCurrentItem to set the state
                PropertyChanges {
                    target: delegate
                    color: delegate.items_color[2]
                }
            },
            State {
                name: "grey"
                when: STATE_LOCATION !== 1
                PropertyChanges {
                    target: delegate
                    color: delegate.items_color[3]
                }
                PropertyChanges {
                    target: delegate
                    height:60

                }
            }
        ]
    }
    Item {
        id: _lightsteelblue
        states:[
            State {
                name: "lightsteelblue"
                when: (delegate.ListView.isCurrentItem && STATE_LOCATION===1)|| (delegate.ListView.isCurrentItem && STATE_ZKR_S_IN===1)
                PropertyChanges {
                    target: state_sp
                    color: delegate.items_color[4];
                }
            }
        ]
    }

    MouseAreaOtcepList {id: mouseArea}
    RowLayout   {
        id: layout
        anchors.fill: parent
        spacing: 0
        Number {txt: STATE_NUM;}
        Number {id: state_sp; txt: STATE_SP ? STATE_SP:""; }
        Number {id: state_sp_f; txt: STATE_SP_F ? STATE_SP_F:"";}
        Number {id: state_sl_vagon_cnt; txt: STATE_SL_VAGON_CNT ? STATE_SL_VAGON_CNT:"";}
        Number {id: state_zkr_vagon_cnt; txt: STATE_ZKR_VAGON_CNT ? STATE_ZKR_VAGON_CNT:"";}
        Number { txt: STATE_BAZA ? STATE_BAZA:"";}
        Number { txt: STATE_SL_VES ? STATE_SL_VES.toFixed(2):"";}
        Number { id: state_sl_ur; txt: sl_ur[STATE_SL_UR]}
        Number {id: state_gac_w_stra; txt: STATE_GAC_W_STRA? "СТР":"";
            Layout.preferredWidth:(listView.width/10)/2}
        Number {id: state_gac_w_strb; txt: STATE_GAC_W_STRB? "БЛК":"";
            Layout.preferredWidth:(listView.width/10)/2}
    }
}







