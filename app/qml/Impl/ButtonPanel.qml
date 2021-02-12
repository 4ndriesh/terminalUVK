import QtQuick 2.14
import QtQuick.Layouts 1.1
import "terminalUVK.js" as MyScript
import Base 1.0
import SettingsModule 1.0
import ResourceProvider 1.0
import QtQuick.Controls 1.4

Item{
    id:bt
    property int regim: manageModel.stateBt.regim
    property int bef_putNadviga: manageModel.stateBt.bef_putNadviga
    property int putNadviga: manageModel.stateBt.putNadviga
    property int wink_pause: manageModel.stateBt.wink_Pause
    property int wink_stop: manageModel.stateBt.wink_Stop
    property int wink_nadvig: manageModel.stateBt.wink_Nadvig
    property int editing: manageModel.stateBt.editing

    property int qmlnewList: manageModel.newList
    property int qmluvkLive: manageModel.uvkLive

    PopupRChain{id:_rchaindialog}

    RowLayout {
        spacing: 5


        MultiButton {
            id: edirSortList
            buttonText: "ВВОД СЛ"
            color: editing ? Settings.themeRegimColor:Settings.themeHeaderColor
            wink: false
            EventMouseArea{
                onEntered: { edirSortList.state='Hovering'}
                onExited: { edirSortList.state='Exited'}
                onClicked: manageModel.setRegimEdit()
            }
        }

        MultiButton {
            id: putnadviga
            opacity: 1.0
            Layout.leftMargin:100
            buttonText: "РОСПУСК: 1"
            //            color: Settings.themeHeaderColor
            color: (regim===1 && putNadviga===1) ? Settings.themeRegimColor:Settings.themeHeaderColor
//            color: MyScript.getColore(regim, putNadviga)
            wink: (regim===1 && putNadviga===1) ?false:wink_nadvig
//            onSetWink: manageModel.qmlRegim(11);
//            onSetWink: manageModel.stateBt.wink_Nadvig=false

            EventMouseArea {
                onEntered: { putnadviga.state='Hovering';}
                onExited: { putnadviga.state='Exited';}
                onClicked: {
                    manageModel.qmlRegim(11);
                    manageModel.qmlRegim(1);
                }
            }

        }

        MultiButton {
            id: stop
            buttonText: "СТОП"
            //            color: Settings.themeHeaderColor
            color: regim===0 ? Settings.themeRegimColor:Settings.themeHeaderColor
            wink: regim===0 ? false:wink_stop
//            onSetWink: manageModel.qmlRegim(11);
//            onSetWink: manageModel.stateBt.wink_Stop=false
            EventMouseArea {
                onEntered: { stop.state='Hovering'}
                onExited: { stop.state='Exited'}
                onClicked: {
                    manageModel.qmlRegim(11);
                    manageModel.qmlRegim(0);
                }
            }
        }

        MultiButton {
            id: pause
            buttonText: "ПАУЗА"
            //            color: Settings.themeHeaderColor
            color: regim===2 ? Settings.themeRegimColor:Settings.themeHeaderColor
            wink: regim===2 ? false:wink_pause
//            onSetWink: manageModel.qmlRegim(11);
//            onSetWink: manageModel.stateBt.wink_Pause=false

            EventMouseArea {
                onEntered: { pause.state='Hovering'}
                onExited: { pause.state='Exited'}
                onClicked: {
                    manageModel.qmlRegim(11);
                    manageModel.qmlRegim(2);
                }
            }
        }
        MultiButton {
            id: rchain
            buttonText: "РЦ"
            Layout.alignment: Qt.AlignRight
            //            color: Settings.themeHeaderColor
            wink: false
            EventMouseArea {
                onEntered: { rchain.state='Hovering'}
                onExited: { rchain.state='Exited'}
                onClicked: {
                    //                    Settings.visibleInputPanel=false;
                    manageModel.addRChain();
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
            //            buttonText: "Новый Лист"
            color: qmlnewList ? Settings.themeBtSignalColorAct:Settings.themeBtSignalColorDAct
            wink: false
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
            //            buttonText: "УВК"
            color: qmluvkLive ?  Settings.themeBtSignalColorAct:Settings.themeBtSignalColorDAct
            wink: false
            ImageSVG {
                source: Resources.contacts.defaulticonConnect
                widthsvg: newSortList.height/1.5
                heightsvg:  newSortList.height/1.5
                //                    color: "#dc143c"
            }
        }
    }
}
