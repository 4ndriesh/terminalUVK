import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14
import Base 1.0
import SettingsModule 1.0

Popup {
    id:keyboard
    parent: Overlay.overlay
    x: Math.round((parent.width-width)/2)
    y: Math.round((parent.height-height))-50
    height: parent.height/3
    width: parent.width/4
    background: Rectangle {color: "transparent"}
    Grid {
        id: panelKeyboard
        property int itemWidth: Math.round((width - spacing * (columns - 1)) / columns)
        property int itemHeight: Math.round((height - spacing * (rows - 1)) / rows)

        anchors.fill: parent
        spacing: 5

        columns: 5
        rows: 3
        //        columns: keyboard.inPortrait ? 1 : 2
        //        rows: keyboard.inPortrait ? 6 : 3
        ButtonKey{
            buttonText: "1"
            MouseKeyBoard{onClicked: manageModel.inputPut(1);}
        }
        ButtonKey{
            buttonText: "2"
            MouseKeyBoard{onClicked: manageModel.inputPut(2);}
        }
        ButtonKey{
            buttonText: "3"
            MouseKeyBoard{onClicked: manageModel.inputPut(3);}
        }

        ButtonKey{
            id:enter
            ImageSVG {
                source: Settings.keyboard.enter
                color: Settings.keyboard.overlay
                widthsvg: enter.height/1.5
                heightsvg:  enter.height/1.5
            }
            MouseKeyBoard{onClicked: manageModel.accept();}
        }
        ButtonKey{
            id:trash
            ImageSVG {
                source: Settings.keyboard.trash
                color: Settings.keyboard.overlay
                widthsvg: trash.height/1.5
                heightsvg:  trash.height/1.5
            }
            MouseKeyBoard{onClicked: manageModel.qmlRegimEditing(3);}

        }
        ButtonKey{
            buttonText: "4"
            MouseKeyBoard{onClicked: manageModel.inputPut(4);}
        }
        ButtonKey{
            buttonText: "5"
            MouseKeyBoard{onClicked: manageModel.inputPut(5);}
        }
        ButtonKey{
            buttonText: "6"
            MouseKeyBoard{onClicked: manageModel.inputPut(6);}
        }
        ButtonKey{
            id:upArrow
            ImageSVG {
                source: Settings.keyboard.upArrow
                color: Settings.keyboard.overlay
                widthsvg: upArrow.height/1.5
                heightsvg:  upArrow.height/1.5
            }
            MouseKeyBoard{onClicked: manageModel.keyUpDown(38);}
        }
        ButtonKey{
            id:insertUp
            ImageSVG {
                source: Settings.keyboard.insertDown
                rotation: 180
                color: Settings.keyboard.overlay
                widthsvg: insertUp.height/1.5
                heightsvg:  insertUp.height/1.5
            }
            MouseKeyBoard{onClicked: manageModel.qmlRegimEditing(4);}
        }

        ButtonKey{
            buttonText: "7"
            MouseKeyBoard{onClicked: manageModel.inputPut(7);}
        }
        ButtonKey{
            buttonText: "8"
            MouseKeyBoard{onClicked: manageModel.inputPut(8);}
        }
        ButtonKey{
            buttonText: "9"
            MouseKeyBoard{onClicked: manageModel.inputPut(9);}
        }
        ButtonKey{
            id:downArrow
            ImageSVG {
                source: Settings.keyboard.downArrow
                color: Settings.keyboard.overlay
                widthsvg: downArrow.height/1.5
                heightsvg:  downArrow.height/1.5
            }
            MouseKeyBoard{onClicked: manageModel.keyUpDown(40);}
        }
        ButtonKey{
            id: insertDown
            ImageSVG {
                source: Settings.keyboard.insertDown
                color: Settings.keyboard.overlay
                widthsvg: insertDown.height/1.5
                heightsvg:  insertDown.height/1.5
            }
            MouseKeyBoard{onClicked: manageModel.qmlRegimEditing(5);}
        }

    }
}
