import QtQuick 2.0
import SettingsModule 1.0

Rectangle {
    id: _highlight
    property alias scaleHight: scaleTransform.yScale
    visible: true;
    anchors.margins: 1
    width: parent.width;

    //    focus: true
    color: "transparent"
    border.width: 5
    border.color: manageModel.stateBt.editing ? "orange":"green"



    transform: Scale {
        id: scaleTransform
    }
    Behavior on y {SpringAnimation { spring: 2; damping: 0.4;}}
}
