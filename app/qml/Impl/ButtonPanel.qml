import QtQuick 2.14
import "terminalUVK.js" as MyScript
import Base 1.0
import SettingsModule 1.0

Item{
    id:bt
    property int regim: manageModel.stateBt.regim
    property int bef_putNadviga: manageModel.stateBt.bef_putNadviga
    property int putNadviga: manageModel.stateBt.putNadviga
    property int wink_pause: manageModel.stateBt.wink_Pause
    property int wink_stop: manageModel.stateBt.wink_Stop
    property int wink_nadvig: manageModel.stateBt.wink_Nadvig
    property int editing: manageModel.stateBt.editing
    property variant n_rospusk: ["РОСПУСК: 2","РОСПУСК: 1"]
    property int currentSelection: 0

    Row {

        spacing: 5
        MultiButton {
            id: edirSortList
            buttonText: "ВВОД СЛ"
            color: editing ? Settings.themeRegimColor:Settings.themeHeaderColor
            wink: false
        }

        MultiButton {
            id: putnadviga
            buttonText: n_rospusk[bef_putNadviga%2]
            color: MyScript.getColore(regim, putNadviga)
            wink: wink_nadvig
            onSetWink: manageModel.stateBt.wink_Nadvig=false
            EventMouseArea {
                onClicked: {manageModel.qmlRegim(1)
                    currentSelection=currentSelection % n_rospusk.length+1
                    manageModel.stateBt.bef_putNadviga=currentSelection
                }
            }
        }

        MultiButton {
            id: stop
            buttonText: "СТОП"
            color: regim ? Settings.themeHeaderColor:Settings.themeRegimColor
            wink: regim ? wink_stop:false
            onSetWink: manageModel.stateBt.wink_Stop=false
            EventMouseArea {
                onClicked: manageModel.qmlRegim(0)
            }
        }


        MultiButton {
            id: pause
            buttonText: "ПАУЗА"
            color: regim<2 ? Settings.themeHeaderColor:Settings.themeRegimColor
            wink: regim<2 ? wink_pause:false
            onSetWink: manageModel.stateBt.wink_Pause=false
            EventMouseArea {
                onClicked: manageModel.qmlRegim(2)
            }
        }
    }
}
