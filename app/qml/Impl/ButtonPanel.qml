import QtQuick 2.14
import QtQuick.Layouts 1.1
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
    RowLayout {
        spacing: 5
        MultiButton {
            id: edirSortList
            buttonText: "ВВОД СЛ"
            color: editing ? Settings.themeRegimColor:Settings.themeHeaderColor
            wink: false
            EventMouseArea {
                onClicked: manageModel.stateBt.editing=!manageModel.stateBt.editing
            }
        }

        MultiButton {
            id: putnadviga
            Layout.leftMargin:100
            buttonText: "РОСПУСК: 1"
            color: MyScript.getColore(regim, putNadviga)
            wink: wink_nadvig
            onSetWink: manageModel.stateBt.wink_Nadvig=false
            EventMouseArea {
                onClicked: {
                    if(editing===0){
                        manageModel.qmlRegim(1)
                        manageModel.stateBt.bef_putNadviga=1
                    }
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
                onClicked: if(editing===0)manageModel.qmlRegim(0)
            }
        }


        MultiButton {
            id: pause
            buttonText: "ПАУЗА"
            color: regim<2 ? Settings.themeHeaderColor:Settings.themeRegimColor
            wink: regim<2 ? wink_pause:false
            onSetWink: manageModel.stateBt.wink_Pause=false
            EventMouseArea {
                onClicked: if(regim===1 && editing===0)manageModel.qmlRegim(2)
            }
        }
    }
}
