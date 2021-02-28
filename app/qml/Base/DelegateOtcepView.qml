import QtQuick 2.14
import QtQuick.Layouts 1.14
import SettingsModule 1.0
import QtQml.Models 2.1

Rectangle {
    id: delegate
    objectName: "delegate"
    property alias iconFlip: spinBoxIndicatorIconScale.yScale
    //    color: listView.isCurrentItem ? "black" : "red"
    //    color: Settings.backgroundListView
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

    property variant items_color: ["red", "yellow","white","silver","lightcyan"]
    width: listView.width;
    height: 60;
    visible: STATE_ENABLED ? true:false
    transform: Scale {
        id: spinBoxIndicatorIconScale
    }
    states:
        [
        State {
            name: "red"
            extend: "default"
            when: STATE_ERROR===1// bind to isCurrentItem to set the state
            PropertyChanges {
                target: state_sp
                color:delegate.items_color[0]
            }
            PropertyChanges {
                target: state_sp_f
                color:delegate.items_color[0]
            }
        },
        State {
            name: "yellow"
            extend: "lightsteelblue"
            when: STATE_ZKR_S_IN===1
            PropertyChanges {
                target: delegate
                color:delegate.items_color[1]
            }
        },

        State {
            name: "lightsteelblue"
            when: (delegate.ListView.isCurrentItem && STATE_IS_CURRENT===1 && STATE_LOCATION===1)
                  || (STATE_LOCATION===1 && delegate.ListView.isCurrentItem)
            PropertyChanges {
                target: state_sp
                enabled:true;
                color: delegate.items_color[4];
//                border.color: "green";
//                border.width: 5;
                textEnabled:true;
                textPutfocus: true;
            }

            PropertyChanges {
                target: delegate
                height:80

            }
            StateChangeScript {
                name: "insertIndex"
                script: manageModel.qmlCurentIndex=index
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
            name: "default"
            when: STATE_LOCATION !== 1
            PropertyChanges {
                target: delegate
                color: delegate.items_color[3]
            }
        }
    ]

    MouseAreaOtcepList {id: mouseArea}
    RowLayout   {
        id: layout
        anchors.fill: parent
        spacing: 0
        Number {txt: STATE_NUM;}
        Number {id: state_sp; txt: STATE_SP ? STATE_SP:""; }
        Number {id: state_sp_f; txt: STATE_SP_F ? STATE_SP_F:"";}
        Number {txt: STATE_SL_VAGON_CNT ? STATE_SP:"";}
        Number {txt: STATE_ZKR_VAGON_CNT ? STATE_ZKR_VAGON_CNT:"";}
        Number { txt: STATE_BAZA ? STATE_BAZA:"";}
        Number { txt: STATE_SL_VES ? STATE_SL_VES.toFixed(2):"";}
        Number { txt: STATE_SL_UR ? STATE_SL_UR:"";}
        Number {id: state_gac_w_stra; txt: STATE_GAC_W_STRA? "СТР":"";
            Layout.preferredWidth:(listView.width/10)/2}
        Number {id: state_gac_w_strb; txt: STATE_GAC_W_STRB? "БЛК":"";
            Layout.preferredWidth:(listView.width/10)/2}
    }



}







