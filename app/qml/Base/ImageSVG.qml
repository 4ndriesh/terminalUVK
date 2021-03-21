import QtQuick 2.14

Image {
    id: _icon
    smooth: true
    anchors.centerIn: parent
    property int widthsvg: 24  // default
    property int heightsvg: 24  // default
    sourceSize.width: widthsvg
    sourceSize.height: heightsvg
}
