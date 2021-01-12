import QtQuick 2.14
import SettingsModule 1.0

Rectangle {
    id: rectangleButton
    property alias buttonText: _buttonText.text;
    property bool wink
    signal setWink()

    width: 100; height: 50
    radius: 8
    border.width: 1
    border.color: "black"
    Text {
        id: _buttonText
        font.pointSize: 10
        anchors.centerIn: parent
    }
    OpacityAnimator on opacity{
        target: rectangleButton
        id: _opacitywink
        loops: Animation.Infinite;
        from: 0;
        to: 1;
        duration: 500
        running: wink
        onStopped: rectangleButton.opacity=1
    }
    Timer {
        id: _timerwink
        interval: Settings.timeWink
        running: wink
        onTriggered: setWink();
    }

}
