import QtQuick 2.7
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.14
Rectangle {
    id: delegate
    //цвет в зависимости от STATE_LOCATION
    property variant items_color: ["brown", "yellow","green"]
    width: parent.width;
    height: 65
    visible: STATE_ENABLED
    //    enabled: STATE_ENABLED
    states:
        [
        State {
            name: "opacity_grey"
            when: model.index<delegate.ListView.view.currentIndex // bind to isCurrentItem to set the state
            PropertyChanges {
                target: delegate
                color: "#b7b7b7"
                opacity: 0.2
            }
        },
        State {
            name: "grey"
            when: model.index>delegate.ListView.view.currentIndex // bind to isCurrentItem to set the state
            PropertyChanges {
                target: delegate
                color: delegate.items_color[STATE_LOCATION]

            }
        },
        State {
            name: "lightsteelblue"
            when: delegate.ListView.isCurrentItem // bind to isCurrentItem to set the state
            PropertyChanges {
                target: delegate
                color: "lightsteelblue"
            }
        }

    ]
    MouseAreaQml {}

    RowLayout   {
        id: layout
        anchors.fill: parent
        spacing: 1
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        Number { txt: STATE_NUM; name: 'STATE_NUM'}
        DualNumber { txt1: STATE_MAR; name1: 'STATE_MAR'; txt2: STATE_MAR_F; name2: 'STATE_MAR_F'  }
        DualNumber { txt1: STATE_SL_VAGON_CNT; name1: 'STATE_SL_VAGON_CNT'; txt2: STATE_ZKR_VAGON_CNT; name2: 'STATE_ZKR_VAGON_CNT'  }
        DualNumber { txt1: STATE_SL_KAT; name1: 'STATE_SL_KAT'; txt2: STATE_ZKR_KAT; name2: 'STATE_ZKR_KAT';  }
        Number { txt: STATE_ZKR_BAZA; name: 'STATE_ZKR_BAZA' }
        Number { txt: STATE_NAGON; name: 'STATE_NAGON' }
        Number { txt: STATE_UR; name: 'STATE_UR' }
        Number { txt: STATE_V; name: 'STATE_V' }
        Number { txt: STATE_KZP; name: 'STATE_KZP' }
        Icons {
            src: "content/list-delete.png"
            MouseArea {anchors.fill:parent; onClicked: otcepsModelRedact.deleteFromEditOtcepList(index)            }
        }
        Icons {
            src: "content/plus-sign.png"
            MouseArea {anchors.fill:parent; onClicked: otcepsModelRedact.addToList()            }
        }
    }
}





