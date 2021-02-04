import QtQuick 2.14
import SettingsModule 1.0

Rectangle {
    id: rectangleButton
    property alias buttonText: _buttonText.text;
    property bool wink
    signal setWink()
    color: Settings.themeHeaderColor
    width: 100; height: 50
    radius: 8
    border.width: 2
    border.color: "black"

    Text {
        id: _buttonText
        font.pointSize: 10
        anchors.centerIn: parent
    }

    states:[
        State {
            name: "pause"
            when: regim===2
            PropertyChanges {
                target: pause
                color:Settings.themeRegimColor

            }
        },
        State {
            name: "Hovering"
            PropertyChanges {
                target: rectangleButton
                border.color: "red"
            }
        },
        State {
            name: "Exited"
            PropertyChanges {
                target: rectangleButton
                border.color: "black"
            }
        }
    ]

    OpacityAnimator on opacity{
        id: _opacitywink
        target: rectangleButton
        loops: Animation.Infinite;
        from: 0;
        to: 1;
        duration: 500
        running: wink
        onStopped: {
            rectangleButton.opacity=1;
        }
    }

    Timer {
        id: _timerwink
        interval: Settings.timeWink
        running: wink
        onTriggered: {
            setWink();
            manageModel.qmlRegim(11);
            manageModel.qmlRegim(10);
        }
    }

}
