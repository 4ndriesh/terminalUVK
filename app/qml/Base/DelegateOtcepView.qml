import QtQuick 2.14
import QtQuick.Layouts 1.14
import SettingsModule 1.0
import QtQml.Models 2.1
import "Binding.js" as MyScript

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



    property variant items_color: ["red", "yellow","green","dimgrey","white","LightGray"]
    width: listView.width;
    height: 60;
    //    visible: true
    visible: STATE_ENABLED ? true:false
    transform: Scale {
        id: spinBoxIndicatorIconScale
    }
    states:
        [
        State {
            name: "red"
            when: STATE_ERROR===1// bind to isCurrentItem to set the state
            PropertyChanges {
                target: delegate
                color:delegate.items_color[0]
                //                color:delegate.items_color[0]
            }
        },
        State {
            name: "yellow"
            extend: "focus"
            when: STATE_ZKR_S_IN===1
            PropertyChanges {
                target: delegate
                color:delegate.items_color[1]

            }

//            StateChangeScript {
//                name: "insertIndex"
//                script: manageModel.qmlCurentIndex=index

//            }
            StateChangeScript {
                name: "delegateScale"
                script: delegate.height=80

            }
        },
        State {
            name: "focus"
            when: (((STATE_LOCATION === 1) && (STATE_GAC_ACTIVE===1)) ||
                   ((STATE_LOCATION === 2) && (STATE_GAC_ACTIVE===1)&&(STATE_ZKR_S_IN===1)))&& STATE_ZKR_S_IN!==1

//            PropertyChanges {
//                target: delegate
//                height:80
//                //                color:delegate.items_color[5]
//            }
            StateChangeScript {
                name: "insertIndex"
                script: manageModel.qmlCurentIndex=index

            }
        },
        State {
            name: "lightsteelblue"
            //            when: manageModel.qmlCurentIndex === index // bind to isCurrentItem to set the state
            when: delegate.ListView.isCurrentItem
                  && STATE_LOCATION===1
            //                  && manageModel.stateBt.editing===1// bind to isCurrentItem to set the state
            PropertyChanges {
                target: delegate
                color: "lightsteelblue"

            }
            PropertyChanges {
                target: state_sp
                enabled:true;
                border.color: "green";
                border.width: 5;
                textEnabled:true;
                textPutfocus: true;
                visibleCursor:true;

            }
         },

        State {
            name: "lightgrey"
            when: (STATE_LOCATION == 2) && (STATE_GAC_ACTIVE==1)
            PropertyChanges {
                target: delegate
                color:delegate.items_color[5]
            }
        },
        State {
            name: "darkgrey"
            when: (STATE_LOCATION !== 1) && (STATE_GAC_ACTIVE==0)
            PropertyChanges {
                target: delegate
                color:delegate.items_color[3]
            }
        },


        State {
            name: "white"
            when: STATE_LOCATION === 2// bind to isCurrentItem to set the state
            PropertyChanges {
                target: delegate
                //                color: MyScript.borderGreen(STATE_NUM,STATE_LOCATION);
                color: delegate.items_color[4]
            }
        }
    ]

    MouseAreaOtcepList {id: mouseArea}
    RowLayout   {
        id: layout
        anchors.fill: parent
        spacing: 0
        Number {txt: STATE_NUM;}
        Number {id: state_sp; txt: STATE_SP; }
        Number {id: state_sp_f; txt: STATE_SP_F;}
        Number {id: state_sl; txt: STATE_SL_VAGON_CNT;}
        Number {txt: STATE_ZKR_VAGON_CNT;}
        Number { txt: STATE_SL_VES.toFixed(2);}
        //        Number {txt: STATE_ZKR_VES.toFixed(2); }
        //        Number { txt: STATE_ZKR_BAZA;}
        //        Number { txt: STATE_NAGON;}
        //        Number { txt: STATE_SL_UR;}
        //        Number { txt: STATE_V;}
        //        Number { txt: STATE_ENABLED;}
        Number { txt: STATE_LOCATION;}
        Number { txt: STATE_GAC_ACTIVE;}
        Number { txt: STATE_ZKR_S_IN;}
        Number { txt: STATE_GAC_W_STRA;}
    }
}







