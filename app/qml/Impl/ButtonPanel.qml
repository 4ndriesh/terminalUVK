import QtQuick 2.14
import "terminalUVK.js" as MyScript
import Base 1.0
import SettingsModule 1.0

Item{
    property int regim: manageModel.stateBt.regim
    property int putNadviga: manageModel.stateBt.putNadviga
    property int wink_pause: manageModel.stateBt.wink_Pause
    property int wink_stop: manageModel.stateBt.wink_Stop
    property int wink_nadvig: manageModel.stateBt.wink_Nadvig
    property int editing: manageModel.stateBt.editing

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
            buttonText: putNadviga%2 ? "РОСПУСК: 1":"РОСПУСК: 2"
            color: MyScript.getColore(regim, putNadviga)
            wink: wink_nadvig
            onSetWink: manageModel.stateBt.wink_Nadvig=false
        }

        MultiButton {
            id: stop
            buttonText: "СТОП"
            color: regim ? Settings.themeHeaderColor:Settings.themeRegimColor
            wink: regim ? wink_stop:false
            onSetWink: manageModel.stateBt.wink_Stop=false

        }
        MultiButton {
            id: pause
            buttonText: "ПАУЗА"
            color: regim<2 ? Settings.themeHeaderColor:Settings.themeRegimColor
            wink: regim<2 ? wink_pause:false
            onSetWink: manageModel.stateBt.wink_Pause=false
        }
    }
}
