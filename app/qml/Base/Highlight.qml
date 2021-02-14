import QtQuick 2.0
import SettingsModule 1.0

Rectangle {
    id: _highlight
    visible: true;
    anchors.margins: 1
    width: parent.width;
    color: "transparent"
    border.width: 5
    border.color: manageModel.stateBt.editing ? Settings.editColorHighlight:Settings.baseColorHighlight
    Behavior on y {SpringAnimation { spring: 2; damping: 0.4;}}
}
