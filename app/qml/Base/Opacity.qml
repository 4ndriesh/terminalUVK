import QtQuick 2.14

Item {
    property alias target: _opacity.target
    OpacityAnimator on opacity{
        id: _opacity
        target: _opacitywink
        loops: Animation.Infinite;
        from: 0;
        to: 1;
        duration: 500
        running: wink
        onStopped: {
            target.opacity=1;
        }
    }
}
