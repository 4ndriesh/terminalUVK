import QtQuick 2.14
import "terminalUVK.js" as MyScript
import Base 1.0
import StyleModule 1.0

Rectangle{
    property variant name1
    Row {

        spacing: 5
        MultiButton {
            id: edirSortList
            buttonText: "ВВОД СЛ"
            color: manageModel.qmlVisibleObject ? Style.themeRegimColor:Style.themeHeaderColor
        }

        MultiButton {
            id: putnadviga
            buttonText: manageModel.qmlPutNadviga.set_putnadviga%2 ? "РОСПУСК: 1":"РОСПУСК: 2"
            color: MyScript.getColore(otcepsModel.qmlRegim, manageModel.qmlPutNadviga.set_putnadviga)
        }

        MultiButton {
            id: stop
            buttonText: "СТОП"
            color: name1 ? Style.themeHeaderColor:Style.themeRegimColor

        }
        MultiButton {
            id: pause
            buttonText: "ПАУЗА"
            color: name1<2 ? Style.themeHeaderColor:Style.themeRegimColor
        }
    }
}
