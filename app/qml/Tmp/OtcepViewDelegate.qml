import QtQuick 2.7
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import ResourceProvider 1.0
import Base 1.0
import StyleModule 1.0

Rectangle {
    id: delegate
    objectName: "delegate"
    //цвет в зависимости от STATE_LOCATION
    property variant items_color: Style.list_color
    width: parent.width;
    height: 65
    visible: STATE_ENABLED
    //        state: "dimgrey"
    states:
        [


        //        State {
        //            name: "black1"
        ////            when: model.index<delegate.ListView.view.currentIndex // bind to isCurrentItem to set the state
        ////            when: model.index<delegate.ListView.view.currentIndex
        //            PropertyChanges {
        //                target: delegate
        //                color: "black"
        ////                opacity: 0.2
        //            }
        //        },


        //        State {
        //            name: "opacity_grey"
        //            //            when: model.index<delegate.ListView.view.currentIndex // bind to isCurrentItem to set the state
        //            //            when: model.index<delegate.ListView.view.currentIndex
        //            PropertyChanges {
        //                target: delegate
        //                color: "#b7b7b7"
        //                opacity: 0.2
        //            }
        //        },
        //        State {
        //                        name: "Current"
        //                        when: delegate.ListView.isCurrentItem
        //                        PropertyChanges { target: delegate; x: 20 }
        //                    },
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
        },
        State {
            name: "dimgrey"
            when: !delegate.ListView.isCurrentItem
            PropertyChanges {
                target: delegate
                color: "dimgrey"
            }
        }


    ]
//    MouseAreaQml {id: mouseArea}
    RowLayout   {
        id: layout
//        objectName: "RowLayout"
        anchors.fill: parent
        spacing: 2

//        anchors.verticalCenter: parent.verticalCenter
//        anchors.horizontalCenter: parent.horizontalCenter

        Number {txt: STATE_NUM; objectName: 'STATE_NUM'}
        DualNumber { objN1:'STATE_SP'; txt1: STATE_SP; objN2:'STATE_SP_F';txt2: STATE_SP_F;}
        DualNumber { txt1: STATE_SL_VAGON_CNT; objN1: 'STATE_SL_VAGON_CNT'; txt2: STATE_ZKR_VAGON_CNT; objN2: 'STATE_ZKR_VAGON_CNT'  }
        DualNumber { txt1: STATE_SL_VES.toFixed(2); objN1: 'STATE_SL_VES'; txt2: STATE_ZKR_VES.toFixed(2); objN2: 'STATE_ZKR_VES';  }
        Number { txt: STATE_ZKR_BAZA; objectName: 'STATE_ZKR_BAZA' }
        Number { txt: STATE_NAGON; objectName: 'STATE_NAGON' }
        Number { txt: STATE_SL_UR; objectName: 'STATE_SL_UR' }
        Number { txt: STATE_V; objectName: 'STATE_V' }
        Number { txt: STATE_V; objectName: 'STATE_V' }
//        Icons {
//            id:iconDel
//            src: Resources.contacts.defaultDelIcon
//            visible: otcepsModel.qmlVisibleObject
//            MouseArea {anchors.fill:parent; onClicked: otcepsModelRedact.deleteFromEditOtcepList(index)}
//        }
//        Icons {
//            id:iconAdd
//            src: Resources.contacts.defaultPlusIcon
//            visible: otcepsModel.qmlVisibleObject
//            MouseArea {anchors.fill:parent; onClicked: otcepsModelRedact.addToList()}
//        }
    }

}





