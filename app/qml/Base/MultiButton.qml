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
    Text {
        id: _buttonText
        anchors.fill: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.family: Settings.buttonPanel.fontFamily;
        font.pointSize: parent.height/5;
        fontSizeMode: Text.Fit
    }
    Opacity{target:rectangleButton}
    TimerWink{running: wink}
}
