import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14
import Base 1.0
import SettingsModule 1.0
import RChain 1.0

RowLayout {
    Layout.fillWidth: true
    height: 50
    spacing: 5
    property color colorRegimRospusk: manageModel.stateBt.regim_Finish ? Settings.buttonColor.regim : Settings.buttonColor.regimRospusk
    property int regim: manageModel.stateBt.regim
    property int bef_putNadviga: manageModel.stateBt.bef_putNadviga
    property int putNadviga: manageModel.stateBt.putNadviga
    property bool wink_pause: manageModel.stateBt.wink_Pause
    property bool wink_stop: manageModel.stateBt.wink_Stop
    property bool wink_nadvig: manageModel.stateBt.wink_Nadvig
    property bool wink_GetList: manageModel.stateBt.wink_GetList
    property bool newList: manageModel.newList
    property int qmluvkLive: manageModel.uvkLive
    RChainView{id:_rchaindialog}
    Clock {
        id: timer
    }

    property var timeFormat:timer.timeFormat

    MultiButton {
        id: putnadviga
        Layout.leftMargin: 10
        buttonText: "РОСПУСК"
        colorButton: (regim===1 && putNadviga===1) ? colorRegimRospusk: Settings.buttonColor.baseColor

        wink: (regim===1 && putNadviga===1) ?false:wink_nadvig

        ButtonArea {setRegim: 1}

    }

    MultiButton {
        id: stop
        buttonText: "СТОП"
        colorButton: regim===0 ? Settings.buttonColor.regim:Settings.buttonColor.baseColor
        wink: regim===0 ? false:wink_stop
        ButtonArea {setRegim: 0}
    }

    MultiButton {
        id: pause
        buttonText: "ПАУЗА"
        colorButton: regim===2 ? Settings.buttonColor.regim:Settings.buttonColor.baseColor
        wink: regim===2 ? false:wink_pause
        ButtonArea {setRegim: 2}
    }

    Rectangle{
        id:clock
        Layout.fillWidth: true
        Layout.minimumWidth: 100
        height: parent.height
        Label {
            anchors.centerIn: parent
            text: timeFormat
            font.pointSize:  parent.height/2;
        }
    }

    MultiButton {
        id: rchain
        buttonText: "РЦ"
        Layout.alignment: Qt.AlignRight
        Layout.rightMargin:50
        ButtonArea {
            onClicked: {
                _rchaindialog.open();
            }
        }
    }

    MultiButton {
        id: newSortList
        Layout.alignment: Qt.AlignRight
        colorButton: newList ? Settings.newSortList.actColor:Settings.newSortList.baseColor
        wink: wink_GetList
        ImageSVG {
            source: Settings.newSortList.svgSortList
            widthsvg: parent.height/1.5
            heightsvg:  parent.height/1.5
        }
        ButtonArea {setRegim: 12}
    }

    MultiButton {
        id: _uvkLive
        Layout.alignment: Qt.AlignRight
        colorButton: qmluvkLive ?  Settings.aliveUvk.actColor:Settings.aliveUvk.baseColor
        wink: qmluvkLive ? false:true        
        ImageSVG {
            source: Settings.aliveUvk.svgAliveUvk
            widthsvg: parent.height/1.5
            heightsvg:  parent.height/1.5
        }
        ButtonArea {
            onClicked: {
                if(qmluvkLive)
                    manageModel.updateOtcep();
            }
        }
    }
}

