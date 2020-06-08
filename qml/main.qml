import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls 1.4
import QtQuick.Controls 2.4


ApplicationWindow {
    visible: true
    width: 1400
    height: 600
    //    title: qsTr("Терминал УВК")

    Connections{
        target: otcepsModel
        onShowMessage: {
            showmessage.color=colorMessage
            textMsg.text=textMessage
        }
    }

    SplitView {
        id: splitView1
        anchors.fill: parent
        Layout.fillWidth: true
        orientation: Qt.Vertical
        SplitView {
            id: splitView
            Layout.fillHeight: true
            Layout.fillWidth: true
            orientation: Qt.Horizontal
            Rectangle {
                color: "#565656"
                Layout.fillHeight: true
                Layout.minimumWidth: 200
                Layout.maximumWidth: 400
                ChartSpeed{
                    id: idChartView
                }
                //                Text {
                //                    text: "View 1"
                //                    anchors.centerIn: parent
                //                }
            }

            StackLayout {
                id: layout
                Layout.fillHeight: true
                Layout.fillWidth: true
//                currentIndex: bar.currentIndex
                TuvkMainPage{
                }


                //                TuvkChangePage{
                //                }

            }

            Rectangle {
                color: "#565656"
                //Layout.fillHeight: true
                Layout.minimumWidth: 200
                Layout.maximumWidth: 400
                ChartSpeed{
                    id: idChartView2
                }
            }
        }

        Rectangle {
            id: showmessage
            color: "#FFFFE0"
            Layout.fillWidth: true
            Layout.minimumHeight: 50
            Layout.maximumHeight:100
            ListView{
                id:listMsgView
                anchors.fill: parent
                model:otcepsModel.listMsg
                delegate: MsgDelegate{}
            }
        }
        Timer {
            id: msgTimer
            interval: 1000
            repeat: true
            running: otcepsModel.timerDelMsg
            onTriggered: otcepsModel.deleteMsg();
        }
    }

//    footer:TabBar {
//        id: bar
//        width: parent.width
//        TabButton {
//            id:tab1
//            text: qsTr("Роспуск")
//        }
//        TabButton {
//            id:tab2
//            text: qsTr("Редактировать")
//        }
//    }
}

