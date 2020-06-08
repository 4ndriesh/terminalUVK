import QtQuick 2.0

Item {
    id: highlight

//    property alias visibleCursor: cursor.visible
    Rectangle {
        id: cursor
        width: listView.cellWidth; height: listView.cellHeight

//        y: listView.currentItem.y
//                Behavior on y {
//                    SpringAnimation {
//                        spring: 3
//                        damping: 0.2
//                    }
//                }

        color: "lightsteelblue"; radius: 5
        //        x: listView.currentItem.x
        //        y: listView.currentItem.y
        //        Behavior on x { SpringAnimation { spring: 1; damping: 0.3 } }
        Behavior on y { SpringAnimation { spring: 1; damping: 0.3 } }
    }
}
