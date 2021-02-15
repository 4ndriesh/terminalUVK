import QtQuick 2.14
import SettingsModule 1.0

Rectangle {
    id: rectangleButton
    property alias buttonText: _buttonText.text;
    property color colorButton:Settings.themeHeaderColor
    property bool wink
    color: colorButton
    width: 100; height: 50
    radius: 8
    border.width: 2
    border.color: "black"

    states:
        State {
        name: "Hovering"
        PropertyChanges {
            target: rectangleButton
            color:Qt.darker(colorButton, 1.5)
        }
    }
    Text {
        id: _buttonText
        font.family: Settings.fontFamily;
        font.pointSize: 10
        anchors.centerIn: parent
    }

    OpacityAnimator on opacity{
        id: _opacitywink
        target: rectangleButton
        loops: Animation.Infinite;
        from: 0;
        to: 1;
        duration: 500
        running: wink
        onStopped: {
            manageModel.qmlRegim(11);
            rectangleButton.opacity=1;
        }
    }

    Timer {
        id: _timerwink
        interval: Settings.timeWink
        running: wink
        onTriggered: {
            manageModel.qmlRegim(11);
            manageModel.qmlRegim(10);
        }
    }

}
