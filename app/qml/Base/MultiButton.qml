import QtQuick 2.14
import SettingsModule 1.0

Rectangle {
    id: rectangleButton
    property alias buttonText: _buttonText.text;
    property color colorButton:Settings.newSortList.baseColor
    property bool wink: false
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
    TextOut{
        id: _buttonText
        font.pointSize: parent.height/5;
    }

    Opacity{target:rectangleButton}
    TimerWink{running: wink}
}
