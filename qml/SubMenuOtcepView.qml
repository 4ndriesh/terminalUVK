import QtQuick 2.0
import QtQuick.Controls 2.0

Menu {
    id: contextMenu
    MenuItem {
        text: "Вставить до";
        Icons {
            id:iconAddUp
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 20
            src: "content/arrow-up.png"
        }
        onTriggered: otcepsModel.addOtcepUP(listView.currentIndex);
    }
    MenuItem {
        text: "Вставить после";
        Icons {
            id:iconAddDown
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 20
            src: "content/arrow-down.png"
        }
        onTriggered: otcepsModel.addOtcepDown(listView.currentIndex);
    }
    MenuItem {
        text: "Очистить все"
        onTriggered: otcepsModel.addOtcepClearAll();
    }
}



