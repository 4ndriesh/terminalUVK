import QtQuick 2.14
import QtQuick.Layouts 1.1
import Base 1.0
import SettingsModule 1.0
//import ResourceProvider 1.0
import QtQuick.Controls 1.4


Item{
    id:bt
    property int regim: manageModel.stateBt.regim
    property int bef_putNadviga: manageModel.stateBt.bef_putNadviga
    property int putNadviga: manageModel.stateBt.putNadviga
    property bool wink_pause: manageModel.stateBt.wink_Pause
    property bool wink_stop: manageModel.stateBt.wink_Stop
    property bool wink_nadvig: manageModel.stateBt.wink_Nadvig
    property bool editing: manageModel.stateBt.editing

    property int qmlnewList: manageModel.newList
    property int qmluvkLive: manageModel.uvkLive

    PopupRChain{id:_rchaindialog}

    RowLayout {
        spacing: 5
        MultiButton {
            id: edirSortList
            buttonText: "ВВОД СЛ"
            colorButton: editing ? Settings.buttonColor.regim:Settings.buttonColor.baseColor
            wink: false
            EventMouseArea{
                onClicked: {
                    manageModel.setRegimEdit();
                }
            }
        }

        MultiButton {
            id: putnadviga
            Layout.leftMargin:100
            buttonText: "РОСПУСК: 1"
            colorButton: (regim===1 && putNadviga===1) ? Settings.buttonColor.regimRospusk:Settings.buttonColor.baseColor
            wink: (regim===1 && putNadviga===1) ?false:wink_nadvig

            EventMouseArea {setRegim: 1}

        }

        MultiButton {
            id: stop
            buttonText: "СТОП"
            colorButton: regim===0 ? Settings.buttonColor.regim:Settings.buttonColor.baseColor
            wink: regim===0 ? false:wink_stop
            EventMouseArea {setRegim: 0}
        }

        MultiButton {
            id: pause
            buttonText: "ПАУЗА"
            colorButton: regim===2 ? Settings.buttonColor.regim:Settings.buttonColor.baseColor
            wink: regim===2 ? false:wink_pause

            EventMouseArea {setRegim: 2}
        }

    }
    RowLayout {
        spacing: 5
        anchors.right: parent.right
        width: 380

        MultiButton {
            id: rchain
            buttonText: "РЦ"
            Layout.alignment: Qt.AlignRight
            Layout.rightMargin:60
            wink: false
            EventMouseArea {
                onClicked: {
                    _rchaindialog.open();
                }
            }
        }

        MultiButton {
            id: newSortList
            Layout.alignment: Qt.AlignRight
            colorButton: qmlnewList ? Settings.newSortList.actColor:Settings.newSortList.baseColor
            wink: qmlnewList ? true:false
            ImageSVG {
                source: Settings.newSortList.svgSortList
                widthsvg: parent.height/1.5
                heightsvg:  parent.height/1.5
            }
        }

        MultiButton {
            id: _uvkLive
            Layout.alignment: Qt.AlignRight
            Layout.rightMargin:10
            colorButton: qmluvkLive ?  Settings.aliveUvk.actColor:Settings.aliveUvk.baseColor
            wink: qmluvkLive ? false:true
            ImageSVG {
                source: Settings.aliveUvk.svgAliveUvk
                widthsvg: parent.height/1.5
                heightsvg:  parent.height/1.5
            }
        }
    }
}
