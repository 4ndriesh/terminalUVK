import QtQuick 2.14
import QtQuick.Layouts 1.14
import SettingsModule 1.0
import QtQml.Models 2.1
import "Binding.js" as MyScript

Rectangle {
    id: delegate
    objectName: "delegate"
    color: Settings.backgroundListView
    //цвет в зависимости от STATE_LOCATION
    property variant items_color: ["red", "yellow","green","dimgrey","white","LightGray"]
    width: _otcepView.width;
    height: 65
    //    property int index: DelegateModel.itemsIndex
    visible: STATE_ENABLED ? true:false
    states:
        [
        State {
            name: "yellow"
            when: STATE_LOCATION === 2 &&   STATE_ZKR_PROGRESS===1// bind to isCurrentItem to set the state
            PropertyChanges {
                target: delegate
                color:delegate.items_color[1]
            }
        },
        State {
            name: "lightsteelblue"
            //                        when: manageModel.qmlCurentIndex === index // bind to isCurrentItem to set the state
            when: delegate.ListView.isCurrentItem // bind to isCurrentItem to set the state
            PropertyChanges {
                target: delegate
                color: MyScript.borderGreen(0,STATE_LOCATION)
            }
            PropertyChanges {
                target: state_sp
                enabled:false;
                border.color: "black";
                border.width: 1;
                textPutfocus:false;
                visibleCursor:false;
            }
        },
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
            name: "dimgrey"
//            when: STATE_LOCATION===2 && STATE_SP===STATE_SP_F || STATE_LOCATION == 3// bind to isCurrentItem to set the state
            when: STATE_LOCATION===2 && ((STATE_SP===STATE_SP_F)&& STATE_SP!==0) || STATE_LOCATION == 3// bind to isCurrentItem to set the state
            PropertyChanges {
                target: delegate
                color:delegate.items_color[3]
            }
        },
        State {
            name: "lightgrey"
            when: STATE_LOCATION===2 && STATE_SP!==STATE_SP_F// bind to isCurrentItem to set the state
            PropertyChanges {
                target: delegate
                color:delegate.items_color[5]
            }
        },

        State {
            name: "white"
            when: STATE_LOCATION === 1// bind to isCurrentItem to set the state
            PropertyChanges {
                target: delegate
                //                color: MyScript.borderGreen(STATE_NUM,STATE_LOCATION);
                color: delegate.items_color[4]
            }
        },
        State {
            name: "grey"
            when: STATE_LOCATION === 0// bind to isCurrentItem to set the state
            PropertyChanges {
                target: delegate
                //                color: MyScript.borderGreen(STATE_NUM,STATE_LOCATION);
                color: delegate.items_color[3]
            }
        },
        State {
            name: "green"
            when: STATE_ZKR_PROGRESS == 1// bind to isCurrentItem to set the state
            PropertyChanges {
                target: delegate
                color:MyScript.borderGreen(0,0)
            }
        }



        //        State {
        //            name: "white"
        //            when: STATE_LOCATION === 1 || delegate.ListView.isCurrentItem// bind to isCurrentItem to set the state
        //            PropertyChanges {
        //                target: delegate
        //                color: MyScript.borderGreen()
        ////                color: MyScript.cursor(STATE_NUM-1);
        //                color: delegate.items_color[4]
        //            }

        //            PropertyChanges {
        //                target: state_sp
        //                enabled:false;
        //                border.color: "black";
        //                border.width: 1;
        //            }
        //        }
    ]
//    Binding

    MouseAreaOtcepList {id: mouseArea}
    RowLayout   {
        id: layout
        anchors.fill: parent
        spacing: 0
        //        Number {txt: STATE_NUM; objectName: 'STATE_NUM'}
        //        Number {id: state_sp; txt: STATE_SP; objectName: 'STATE_SP'}
        //        Number {id: state_sp_f; txt: STATE_SP_F; objectName: 'STATE_SP_F'}
        //        Number {id: state_sl; txt: STATE_SL_VAGON_CNT; objectName: 'STATE_SL_VAGON_CNT'}
        //        Number {txt: STATE_ZKR_VAGON_CNT; objectName: 'STATE_ZKR_VAGON_CNT'}
        //        Number { txt: STATE_SL_VES.toFixed(2); objectName: 'STATE_SL_VES'}
        //        Number {txt: STATE_ZKR_VES.toFixed(2); objectName: 'STATE_ZKR_VES'}
        //        Number { txt: STATE_ZKR_BAZA; objectName: 'STATE_ZKR_BAZA' }
        //        Number { txt: STATE_NAGON; objectName: 'STATE_NAGON' }
        //        Number { txt: STATE_SL_UR; objectName: 'STATE_SL_UR' }
        //        Number { txt: STATE_V; objectName: 'STATE_V' }
        //        Number { txt: STATE_V; objectName: 'STATE_V' }
        Number {txt: STATE_NUM;}
        Number {id: state_sp; txt: STATE_SP; }
        Number {id: state_sp_f; txt: STATE_SP_F;}
        Number {id: state_sl; txt: STATE_SL_VAGON_CNT;}
        Number {txt: STATE_ZKR_VAGON_CNT;}
        Number { txt: STATE_SL_VES.toFixed(2);}
        Number {txt: STATE_ZKR_VES.toFixed(2); }
        Number { txt: STATE_ZKR_BAZA;}
        Number { txt: STATE_NAGON;}
//        Number { txt: STATE_SL_UR;}
//        Number { txt: STATE_V;}
        Number { txt: STATE_ENABLED;}
        Number { txt: STATE_LOCATION;}
        Number { txt: STATE_ZKR_PROGRESS;}

    }
    Component.onCompleted: {
        if(manageModel.stateBt.editing===0)
            manageModel.qmlCurrentItemChanged();
    }
}







