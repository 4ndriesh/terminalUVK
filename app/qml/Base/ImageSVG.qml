import QtQuick 2.14
import QtGraphicalEffects 1.14

Image {
    id: _icon
    smooth: true
    anchors.centerIn: parent
//    property alias color: colorOverlay.color
    property int widthsvg: 24  // default
    property int heightsvg: 24  // default
    sourceSize.width: widthsvg
    sourceSize.height: heightsvg

//    ColorOverlay {
//            id: colorOverlay
//            anchors.fill: _icon
//            source: _icon
//            antialiasing: true
//        }

}
