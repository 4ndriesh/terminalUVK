import QtQuick 2.7
import QtQuick.Controls 2.4

Rectangle {
    id: delegate
    width: parent.width;
    height: 64
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
                color: "#b7b7b7"
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
    MouseArea {
        anchors.fill: parent
        onClicked: delegate.ListView.view.currentIndex = index // if only selection is wanted

    }



    Row {
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 1

        Number { txt: n; name: 'n'}
        DualNumber { txt1: mar; name1: 'mar'; txt2: mar_f; name2: 'mar_f'  }
        DualNumber { txt1: len; name1: 'len'; txt2: len_f; name2: 'len_f'  }
        DualNumber { txt1: kat; name1: 'kat'; txt2: kat_f; name2: 'kat_f';  }
        Number { txt: baz; name: 'baz' }
        Number { txt: nag; name: 'nag' }
        Number { txt: ur; name: 'ur' }
        Number { txt: V; name: 'V' }
        Number { txt: kzp; name: 'kzp' }
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





