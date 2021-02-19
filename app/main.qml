import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Window 2.14
import Impl 1.0
import Base 1.0
import SettingsModule 1.0
import QtQuick.Controls 2.3

//import QtQuick.VirtualKeyboard.Settings 2.14

Window {
    id:mainwindow
    visible: true
    visibility: "Maximized"
    minimumWidth: 800
    minimumHeight: 600
    color: Settings.backgroundColor

    MButton {
        id: manage
    }
    property int hour:manage.hour
    property int minute:manage.minute
    title: qsTr(hour+":"+minute);
//    title: qsTr("Терминал УВК")

    //    name: manage.qmlManagerButton.regim
//    property int hour:manage.hour
//    property int minute:manage.minute
//    property int second:manage.second
    GridLayout{
        anchors.fill: parent
        rows: 6
        //        columns: 3

        //        Title {
        //            Layout.fillWidth: true
        //            Layout.preferredHeight: 50
        //            Layout.columnSpan:3
        //            Layout.row: 1
        //        }
        //        SignalPanel {
        //            id: signalPanel
        //            Layout.fillWidth: true
        //            Layout.preferredHeight: 50
        //            Layout.columnSpan:3
        //            Layout.row: 2
        //        }
//        Rectangle{
//            Layout.fillWidth: true
//            Layout.preferredHeight: 50
//            Layout.row: 2
//            Label {
//                anchors.fill: parent
//                verticalAlignment: Text.AlignVCenter
//                horizontalAlignment: Text.AlignHCenter
//                text: manageModel.stateBt.code
//                font.pixelSize: 22
//                font.italic: true
//            }

//        }
        ButtonPanel {
            id: controlPanel
            Layout.fillWidth: true
            Layout.preferredHeight: 50
            //            Layout.columnSpan:3
            Layout.row: 3
        }

        OtcepsView{
            Layout.fillWidth: true
            Layout.fillHeight: true
            //            Layout.columnSpan:3
            Layout.row: 4
        }

        ProgressBarPanel {
            Layout.fillWidth: true
            Layout.preferredHeight: 20
            //            Layout.columnSpan:3
            Layout.row: 5
        }

        AlarmMessage {
            Layout.fillWidth: true
            //            Layout.columnSpan:3
            Layout.row: 6
        }
    }

    //    RChain{id:_rchaindialog}
    InputPanelKB{}
}
