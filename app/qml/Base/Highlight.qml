import QtQuick 2.0

Rectangle {
    id: _highlight
    property alias scaleHight: scaleTransform.yScale
    visible: true;
    width: listView.width;
    height: 60
    focus: true
    color: "transparent"
    border.width: 5
    border.color: manageModel.stateBt.editing ? "orange":"green"

    y: listView.currentItem.y;

    transform: Scale {
        id: scaleTransform
    }
    Behavior on y {SpringAnimation { spring: 2; damping: 0.4}}
}
