import QtQuick 2.14

Rectangle {
    id: rectangleButton
    property alias buttonText: buttonText.text;
    width: 100; height: 50
    radius: 8
    border.width: 1
    border.color: "black"
    Text {
        id: buttonText
        font.pointSize: 10
        anchors.centerIn: parent
    }
}


