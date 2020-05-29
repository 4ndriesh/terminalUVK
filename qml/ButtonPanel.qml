import QtQuick 2.1
import QtQuick.Layouts 1.0
import "terminalUVK.js" as MyScript
RowLayout {
    property alias openGLButton: putnadviga
    signal setRegime(bool enabled)
    signal setPutNadviga(bool enabled)
    signal setStopPause()
    signal setFocus()
    DialogWin{
        id: dialselectputinadviga

    }
    Text {
        text: "Scope"
        font.pointSize: 18
        color: "white"
    }

    MultiButton {
        id: edirSortList
        property variant visibleForEdit: [false,true]
        text: ""
        //        items:[1, 2]
        items: ["ВВОД СЛ", "ВВОД СЛ"]
        currentSelection: 0
        onSelectionLeftMouse:setFocus(currentSelection = (currentSelection + 1) % visibleForEdit.length,
                                      edirSortList.colorRect =MyScript.getColoreedirSortList(visibleForEdit[currentSelection]),
                                      otcepsModel.editSortir(visibleForEdit[currentSelection]))

        //        onSelectionRightMouse:

    }

    MultiButton {
        id: putnadviga
        text: "РОСПУСК: "
        items: [1, 2]
        currentSelection: 0
        onSelectionLeftMouse: setRegime(currentSelection == 1,
                                        otcepsModel.setPutNadviga(items[currentSelection]),
                                        putnadviga.colorRect =MyScript.getColore(otcepsModel.getPutNadviga()))
        onSelectionRightMouse: setPutNadviga(
                                   dialselectputinadviga.name=putnadviga.text + putnadviga.items[(currentSelection + 1) % items.length],
                                   dialselectputinadviga.open());
        Connections {
            target: otcepsModel
            onSetColorPutNadviga: {
                putnadviga.colorRect =MyScript.getColore(qmlPUT_NADVIG)

            }
        }
    }

    MultiButton {
        id: stop
        text: "СТОП"
        items: [""]
        currentSelection: 0
        onSelectionLeftMouse: setStopPause(otcepsModel.setStopPause(0))
        Connections {
            target: otcepsModel
            onSetColorStop: {
                stop.colorRect =MyScript.getColoreStop(qmlStopPause)

            }
        }


    }
    MultiButton {
        id: pause
        text: "ПАУЗА"
        items: [""]
        currentSelection: 0
        onSelectionLeftMouse: setStopPause(otcepsModel.setStopPause(2),
                                           pause.colorRect =MyScript.getColorePause(otcepsModel.getStopPause()))
        Connections {
            target: otcepsModel
            onSetColorPause: {
                pause.colorRect =MyScript.getColorePause(qmlStopPause)
            }
        }
    }
}
