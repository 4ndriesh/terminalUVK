import QtQuick 2.14
import SettingsModule 1.0

Rectangle {
    id: rectangleButton
    property alias buttonText: _buttonText.text;
    property color colorButton:Settings.keyboard.baseColor
    property int textSize: Math.min(0.5*panelKeyboard.itemWidth, 0.5*panelKeyboard.itemHeight)
    color: colorButton
    width: panelKeyboard.itemWidth; height: panelKeyboard.itemHeight
    radius: 8
    border.width: 2
    border.color: "black"
    states:
        State {
        name: "Hovering"
        PropertyChanges {
            target: rectangleButton
            color:Qt.lighter(colorButton, 1.5)
        }
    }
    Text {
        id: _buttonText
        font.family: Settings.keyboard.fontFamily;
        font.pointSize: textSize ?textSize : 10
        color: Settings.keyboard.textColor;
        anchors.centerIn: rectangleButton
    }
}
