import QtQuick 2.0
import SettingsModule 1.0

Rectangle {
    id: _highlight
    property int yHighlite
    property int heightHighlite
    property int widthHighlite
    visible: true;
    height: heightHighlite;
    y:yHighlite;
    anchors.margins: 1
    width: widthHighlite;
    color: "transparent"
    border.width: 5
    border.color: manageModel.stateBt.editing ? Settings.editColorHighlight:Settings.baseColorHighlight
    Behavior on y {SpringAnimation { spring: 2; damping: 0.4;}}
}
