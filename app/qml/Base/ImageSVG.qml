import QtQuick 2.0
import QtGraphicalEffects 1.0

Image {
    id: _icon
    smooth: true
    anchors.centerIn: parent
    property alias color: colorOverlay.color
    property int size: 24  // default
    sourceSize.width: size
    sourceSize.height: size

    ColorOverlay {
            id: colorOverlay
            anchors.fill: _icon
            source: _icon
            antialiasing: true
        }

}
