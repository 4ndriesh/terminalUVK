import QtQuick 2.14
import QtQuick.Layouts 1.4
import StyleModule 1.0

Rectangle {
    id: delegate
    objectName: "delegate"
    color: Style.backgroundColor
    //цвет в зависимости от STATE_LOCATION
    property variant items_color: ["red", "yellow","green","dimgrey","white","LightGray"]
    width: parent.width;
    height: 65
    visible: STATE_ENABLED
    states:
        [
        State {
            name: "red"
            when: STATE_ERROR==1// bind to isCurrentItem to set the state
            PropertyChanges {
                target: delegate
                color:delegate.items_color[0]
            }
        },
        State {
            name: "grey"
            when: STATE_LOCATION==2 && STATE_SP==STATE_SP_F || STATE_LOCATION == 3// bind to isCurrentItem to set the state
            PropertyChanges {
                target: delegate
                color:delegate.items_color[3]
            }
        },
        State {
            name: "lightgrey"
            when: STATE_LOCATION==2 && STATE_SP!=STATE_SP_F// bind to isCurrentItem to set the state
            PropertyChanges {
                target: delegate
                color:delegate.items_color[5]
            }
        },
        State {
            name: "yellow"
            when: STATE_LOCATION == 2 &&   STATE_ZKR_PROGRESS==1// bind to isCurrentItem to set the state
            PropertyChanges {
                target: delegate
                color:delegate.items_color[1]
            }
        },
        State {
            name: "lightsteelblue"
            when: delegate.ListView.isCurrentItem // bind to isCurrentItem to set the state
            PropertyChanges {
                target: delegate
                color: "lightsteelblue"
            }
        },
        State {
            name: "white"
            when: STATE_LOCATION == 1// bind to isCurrentItem to set the state
            PropertyChanges {
                target: delegate
                color: delegate.items_color[4]
           }
        }
//        },
//        State {
//            name: "dimgrey"
//            when: !delegate.ListView.isCurrentItem
//            PropertyChanges {
//                target: delegate
//                color: "dimgrey"
//            }
//        }


    ]

    RowLayout   {
        id: layout
        anchors.fill: parent
        spacing: 0
        Number {txt: STATE_NUM; objectName: 'STATE_NUM'}
//        Number {id: num1; txt: STATE_SP; objectName: 'STATE_SP'}
//        Number {txt: STATE_SP_F; objectName: 'STATE_SP_F'}
        DualNumber { objN1:'STATE_SP'; txt1: STATE_SP; objN2:'STATE_SP_F';txt2: STATE_SP_F;}
        DualNumber { txt1: STATE_SL_VAGON_CNT; objN1: 'STATE_SL_VAGON_CNT'; txt2: STATE_ZKR_VAGON_CNT; objN2: 'STATE_ZKR_VAGON_CNT'  }
        DualNumber { txt1: STATE_SL_VES.toFixed(2); objN1: 'STATE_SL_VES'; txt2: STATE_ZKR_VES.toFixed(2); objN2: 'STATE_ZKR_VES';  }
        Number { txt: STATE_ZKR_BAZA; objectName: 'STATE_ZKR_BAZA' }
        Number { txt: STATE_NAGON; objectName: 'STATE_NAGON' }
        Number { txt: STATE_SL_UR; objectName: 'STATE_SL_UR' }
        Number { txt: STATE_V; objectName: 'STATE_V' }
        Number { txt: STATE_V; objectName: 'STATE_V' }
    }

}





