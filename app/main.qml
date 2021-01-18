import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Window 2.14
import Impl 1.0
import Base 1.0
import SettingsModule 1.0
import QtQuick.Controls 2.3
import QtQuick.VirtualKeyboard 2.1
import QtQuick.VirtualKeyboard.Settings 2.2

Window {
    id:mainwindow
    visible: true
//    visibility: "Maximized"
    minimumWidth: 1200
    minimumHeight: 1000
    color: Settings.backgroundColor
    //    title: qsTr("Терминал УВК")

    GridLayout{
        anchors.fill: parent
        rows: 5
        columns: 3

        Title {
            Layout.fillWidth: true
            Layout.preferredHeight: 50
            Layout.columnSpan:3
            Layout.row: 1
        }

        ButtonPanel {
            id: controlPanel
            Layout.fillWidth: true
            Layout.preferredHeight: 50
            Layout.columnSpan:3
            Layout.row: 2
        }

        OtcepsView{
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.columnSpan:3
            Layout.row: 3
        }

        ProgressBar {
            Layout.fillWidth: true
            Layout.preferredHeight: 20
            Layout.columnSpan:3
            Layout.row: 4
        }

        AlarmMessage {
            Layout.fillWidth: true
            Layout.columnSpan:3
            Layout.row: 5
        }
    }

    InputPanel {
            id: inputPanel
            y: Qt.inputMethod.visible ? parent.height - inputPanel.height : parent.height
            anchors.left: parent.left
            anchors.right: parent.right
        }

}
