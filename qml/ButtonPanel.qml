import QtQuick 2.1
import QtQuick.Layouts 1.0
import "terminalUVK.js" as MyScript


RowLayout {
    signal setRegime(bool enabled)
    signal setPutNadviga(bool enabled)

    DialogWin{
        id: dialselectputinadviga
    }

    MultiButton {
        id: edirSortList
        text: "ВВОД СЛ"
        onSelectionLeftMouse: otcepsModel.qmlVisibleObject=(otcepsModel.qmlVisibleObject+1)%2;
        colorRect: otcepsModel.qmlVisibleObject ? "orange":"lightsteelblue"
    }

    MultiButton {
        id: putnadviga
        buttonText: otcepsModel.qmlPutNadviga.select_putnadviga ? "РОСПУСК: 2":"РОСПУСК: 1"
        onSelectionLeftMouse:
            otcepsModel.qmlPutNadviga.set_putnadviga=otcepsModel.qmlPutNadviga.select_putnadviga+1

        onSelectionRightMouse:
            otcepsModel.qmlPutNadviga.select_putnadviga=(otcepsModel.qmlPutNadviga.select_putnadviga+1)%2

        colorRect: MyScript.getColore(otcepsModel.qmlRegim, otcepsModel.qmlPutNadviga.set_putnadviga)
    }



    MultiButton {
        id: stop
        text: "СТОП"
        onSelectionLeftMouse:otcepsModel.qmlRegim=0;
        colorRect: otcepsModel.qmlRegim ? "lightsteelblue":"orange"

    }
    MultiButton {
        id: pause
        text: "ПАУЗА"
        onSelectionLeftMouse: otcepsModel.qmlRegim=2;
        colorRect: otcepsModel.qmlRegim<2 ? "lightsteelblue":"orange"
    }
}
