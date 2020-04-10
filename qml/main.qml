import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls 1.4
import QtQuick.Controls 2.4


ApplicationWindow {
    visible: true
    width: 1200
    height: 600
    title: qsTr("Терминал УВК")

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
                Layout.minimumWidth: 100
                Layout.maximumWidth: 200
                Text {
                    text: "View 1"
                    anchors.centerIn: parent
                }
            }

            StackLayout {
                id: layout
                Layout.fillHeight: true
                Layout.fillWidth: true
                currentIndex: bar.currentIndex
                TuvkMainPage{
                }

                TuvkChangePage{
                }
            }

            Rectangle {
                color: "#565656"
                //Layout.fillHeight: true
                Layout.minimumWidth: 100
                Layout.maximumWidth: 200
                Text {
                    text: "View 2"
                    anchors.centerIn: parent
                }
            }
        }

        Rectangle {
            id: showmessage
            color: "#FFFFE0"
            Layout.fillWidth: true
            Layout.minimumHeight: 50
            Layout.maximumHeight:100
            Text {
                id:textMsg
                text: "<....................>!?"
                anchors.centerIn: parent
            }
        }
    }

    footer:TabBar {
        id: bar
        width: parent.width
        TabButton {
            id:tab1
            text: qsTr("Роспуск")
        }
        TabButton {
            id:tab2
            text: qsTr("Редактировать")
        }
    }
}

