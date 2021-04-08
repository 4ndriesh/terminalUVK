import QtQuick 2.14
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

        columns: 9
        rows: 3
        //        columns: keyboard.inPortrait ? 1 : 2
        //        rows: keyboard.inPortrait ? 6 : 3
        Item{width: panelKeyboard.itemWidth; height: panelKeyboard.itemHeight}
        ButtonKey{
            buttonText: "1"
            MouseKeyBoard{onClicked: manageModel.keyDown(81,true);}
        }
        ButtonKey{
            buttonText: "2"
            MouseKeyBoard{onClicked: manageModel.keyDown(87,true);}
        }
        ButtonKey{
            buttonText: "3"
            MouseKeyBoard{onClicked: manageModel.keyDown(69,true);}
        }

        ButtonKey{
            id:enter
            ImageSVG {
                source: Settings.keyboard.enter
                widthsvg: enter.width/1.5
                heightsvg:  enter.width/1.5
            }
            MouseKeyBoard{onClicked: manageModel.accept();}
        }

        ButtonKey{
            id:del
            ImageSVG {
                source: Settings.keyboard.del
                widthsvg: del.width/1.5
                heightsvg:  del.width/1.5
            }
            MouseKeyBoard{onClicked: manageModel.keyDown(46,false);}

        }
        ButtonKey{
            id:trash
            ImageSVG {
                source: Settings.keyboard.trash
                widthsvg: trash.width/1.5
                heightsvg:  trash.width/1.5
            }
            MouseKeyBoard{onClicked: manageModel.keyDown(46,true);}

        }
        //        Item{width: panelKeyboard.itemWidth; height: panelKeyboard.itemHeight}
        ButtonKey{
            id: setCurrentOtcep
            ImageSVG {
                source: Settings.keyboard.setCurrentOtcep
                widthsvg: insertDown.width/1.5
                heightsvg:  insertDown.width/1.2
            }
            MouseKeyBoard{onClicked: manageModel.qmlRegim(8);}
        }
        ButtonKey{
            id: lightPlus
//            buttonText: "+"
            ImageSVG {
                source: Settings.keyboard.brightness
                widthsvg: insertDown.width/1.1
                heightsvg:  insertDown.width/1.1
            }
            MouseKeyBoard{onClicked: manageModel.setBrightness(7)}
        }

        Item{width: panelKeyboard.itemWidth; height: panelKeyboard.itemHeight}
        ButtonKey{
            buttonText: "4"
            MouseKeyBoard{onClicked: manageModel.keyDown(82,true);}
        }
        ButtonKey{
            buttonText: "5"
            MouseKeyBoard{onClicked: manageModel.keyDown(84,true);}
        }
        ButtonKey{
            buttonText: "6"
            MouseKeyBoard{onClicked: manageModel.keyDown(89,true);}
        }
        ButtonKey{
            id:insertUp
            ImageSVG {
                source: Settings.keyboard.insertDown
                rotation: 180
                widthsvg: insertUp.width/1.5
                heightsvg:  insertUp.width/1.5
            }
            MouseKeyBoard{onClicked: manageModel.keyDown(45,false);}
        }
        Item{width: panelKeyboard.itemWidth; height: panelKeyboard.itemHeight}
        ButtonKey{
            id:upArrow
            ImageSVG {
                source: Settings.keyboard.upArrow
                widthsvg: upArrow.width/1.5
                heightsvg:  upArrow.width/1.5
            }
            MouseKeyBoard{onClicked: manageModel.keyDown(38,false);}
        }

        Item{width: panelKeyboard.itemWidth; height: panelKeyboard.itemHeight}
        ButtonKey{
            id: lightMinus
//            buttonText: "-"
            ImageSVG {
                source: Settings.keyboard.brightness
                widthsvg: insertDown.width/1.5
                heightsvg:  insertDown.width/1.5
            }
            MouseKeyBoard{onClicked: manageModel.setBrightness(5)}
        }
        ButtonKey{
            buttonText: "0"
            MouseKeyBoard{onClicked: manageModel.keyDown(80,true);}
        }
        ButtonKey{
            buttonText: "7"
            MouseKeyBoard{onClicked: manageModel.keyDown(85,true);}
        }
        ButtonKey{
            buttonText: "8"
            MouseKeyBoard{onClicked: manageModel.keyDown(73,true);}
        }
        ButtonKey{
            buttonText: "9"
            MouseKeyBoard{onClicked: manageModel.keyDown(79,true);}
        }
        ButtonKey{
            id: insertDown
            ImageSVG {
                source: Settings.keyboard.insertDown
                widthsvg: insertDown.width/1.5
                heightsvg:  insertDown.width/1.5
            }
            MouseKeyBoard{onClicked: manageModel.keyDown(45,true);}
        }
        ButtonKey{
            id:leftArrow
            ImageSVG {
                source: Settings.keyboard.downArrow
                rotation: 90
                widthsvg: downArrow.width/1.5
                heightsvg:  downArrow.width/1.5
            }
            MouseKeyBoard{onClicked: manageModel.keyDown(37,false);}
        }
        ButtonKey{
            id:downArrow
            ImageSVG {
                source: Settings.keyboard.downArrow
                widthsvg: downArrow.width/1.5
                heightsvg:  downArrow.width/1.5
            }
            MouseKeyBoard{onClicked: manageModel.keyDown(40,false);}
        }

        ButtonKey{
            id:rightArrow
            ImageSVG {
                source: Settings.keyboard.downArrow
                rotation: -90
                widthsvg: downArrow.width/1.5
                heightsvg:  downArrow.width/1.5
            }
            MouseKeyBoard{onClicked: manageModel.keyDown(39,false);}
        }
        Item{width: panelKeyboard.itemWidth; height: panelKeyboard.itemHeight}


    }
}
