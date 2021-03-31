import QtQuick 2.14
import SettingsModule 1.0
import Base 1.0

Rectangle {
    id: _highlight
    width: _vagons.width;
    height: _vagons.currentItem.height;
    color: "transparent"
    border.width: 5
    border.color: Settings.highlight.base
    y:_vagons.currentItem.y;

    Behavior on y {SpringAnimation { spring: 2; damping: 0.4;}}
}
