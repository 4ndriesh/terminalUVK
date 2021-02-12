import QtQuick 2.14
import QtQuick.Controls 2.14
import SettingsModule 1.0

Button {
    id: rectangleButton
//    property alias buttonText: rectangleButton.text;
    property alias colorButton: _backgroundButton.color
    property bool wink
    signal setWink()
    text: "ВВОД СЛ1"
    background: Rectangle {
        id:_backgroundButton
        implicitWidth: 100
        implicitHeight: 50
//        color:rectangleButton.down ? Qt.darker(_backgroundButton.color, 1.5) :rectangleButton.colorButton
        border.color: "#26282a"
        border.width: 2
        radius: 8
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
