import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0
Item {
    id:button
    width: 100
    height: 50
    property int put_nadviga: 0
    property string text: "РОСПУСК: "
    property int mouseButtonClicked: Qt.NoButton
    //    property string text: "Hovering"
    property variant items: ["1","2"]
    property int currentSelection: 0
    signal selectionLeftMouse(variant selection)
    signal selectionRightMouse()
    property alias buttonText: innerText.text;
    property alias colorRect: rectangleButton.color
    property color hoverColor: "LightSkyBlue"
    property color pressColor: "slategray"
    property int fontSize: 10
    property int borderWidth: 1
    property int borderRadius: 8
    scale: state === "Pressed" ? 0.90 : 1.0
    onEnabledChanged: state = ""
    signal clicked
    //define a scale animation
    Behavior on scale {
        NumberAnimation {
            duration: 100
            easing.type: Easing.InOutQuad
        }
    }

    //Rectangle to draw the button
    Rectangle {
        id: rectangleButton
        anchors.fill: parent
        radius: borderRadius
        color: button.enabled ? "lightsteelblue" : "lightsteelblue"
        border.width: borderWidth
        border.color: "black"
        Text {
            id: innerText
            font.pointSize: fontSize
            anchors.centerIn: parent
            text: button.text + button.items[currentSelection]
        }
    }

    //change the color of the button in differen button states
    states: [
        State {
            name: "Hovering"
            PropertyChanges {
                target: rectangleButton
                border.color: hoverColor
            }
        },
        State {
            name: "Pressed"
            PropertyChanges {
                target: rectangleButton
                border.color: pressColor
            }
        }
    ]

    //define transmission for the states
    transitions: [
        Transition {
            from: ""; to: "Hovering"
            ColorAnimation { duration: 200 }
        },
        Transition {
            from: "*"; to: "Pressed"
            ColorAnimation { duration: 10 }
        }
    ]
    MouseArea {
        id: buttonMouseArea

        acceptedButtons: Qt.RightButton | Qt.LeftButton
        hoverEnabled: true
        anchors.fill: button
        onEntered: { button.state='Hovering'}
        onExited: { button.state=''}

        onPressed: {
            button.state="Pressed"
            if (pressedButtons & Qt.LeftButton) {
                mouseButtonClicked = Qt.LeftButton


            } else if (pressedButtons & Qt.RightButton) {
                mouseButtonClicked = Qt.RightButton
            }
        }
        onReleased: {
            if (containsMouse)
                button.state="Hovering";
            else
                button.state="";
        }
    }
    Connections{
        target: buttonMouseArea
        onClicked: { button.clicked();
            if (mouseButtonClicked === Qt.LeftButton) {
                selectionLeftMouse(button.items[currentSelection]);

            } else if (mouseButtonClicked === Qt.RightButton) {
                selectionRightMouse();

            }
        }
    }
}

