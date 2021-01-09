import QtQuick 2.14

    Rectangle {
        id: cursor
        width: listView.width; height: listView.cellHeight
        color: "lightsteelblue";
        radius: 5
//        y: listView.currentItem.y;
//        Behavior on y { SpringAnimation { spring: 1; damping: 0.3 } }
    }

