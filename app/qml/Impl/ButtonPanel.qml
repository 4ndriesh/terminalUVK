import QtQuick 2.14
import QtQuick.Layouts 1.1
import Base 1.0
import SettingsModule 1.0
import ResourceProvider 1.0
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
            colorButton: editing ? Settings.themeRegimColor:Settings.themeHeaderColor
            wink: false
            EventMouseArea{
                onClicked: {
                    Settings.visibleInputPanel=false;
                    manageModel.setRegimEdit();
                }
            }
        }

        MultiButton {
            id: putnadviga
            opacity: 1.0
            Layout.leftMargin:100
            buttonText: "РОСПУСК: 1"
            colorButton: (regim===1 && putNadviga===1) ? Settings.themeRegimColor:Settings.themeHeaderColor
            wink: (regim===1 && putNadviga===1) ?false:wink_nadvig

            EventMouseArea {setRegim: 1}

        }

        MultiButton {
            id: stop
            buttonText: "СТОП"
            colorButton: regim===0 ? Settings.themeRegimColor:Settings.themeHeaderColor
            wink: regim===0 ? false:wink_stop
            EventMouseArea {setRegim: 0}
        }

        MultiButton {
            id: pause
            buttonText: "ПАУЗА"
            colorButton: regim===2 ? Settings.themeRegimColor:Settings.themeHeaderColor
            wink: regim===2 ? false:wink_pause

            EventMouseArea {setRegim: 2}
        }
        MultiButton {
            id: rchain
            buttonText: "РЦ"
            Layout.alignment: Qt.AlignRight
            wink: false
            EventMouseArea {
                onClicked: {                    //                    Settings.visibleInputPanel=false;
                    _rchaindialog.open();
                }
            }
        }

    }
    RowLayout {
        spacing: 5
        anchors.right: parent.right
        width: 220
        MultiButton {
            id: newSortList
            Layout.alignment: Qt.AlignRight
            colorButton: qmlnewList ? Settings.themeBtSignalColorAct:Settings.themeBtSignalColorDAct
            wink: qmlnewList ? true:false
            ImageSVG {
                source: Resources.contacts.defaulticonList
                widthsvg: newSortList.height/1.5
                heightsvg:  newSortList.height/1.5
                //                    color: "#228b22"
            }
        }

        MultiButton {
            id: _uvkLive
            Layout.alignment: Qt.AlignRight
            Layout.rightMargin:10
            colorButton: qmluvkLive ?  Settings.themeBtSignalColorAct:Settings.themeBtSignalColorDAct
            wink: qmluvkLive ? false:true
            ImageSVG {
                source: Resources.contacts.defaulticonConnect
                widthsvg: newSortList.height/1.5
                heightsvg:  newSortList.height/1.5
                //                    color: "#dc143c"
            }
        }
    }
}
