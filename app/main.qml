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
    minimumWidth: 1000
    minimumHeight: 600
    color: Settings.window.backgroundColor
    title: qsTr("Терминал УВК")

    GridLayout{
        anchors.fill: parent
        rows: 6

        ButtonPanel {
            id: controlPanel
            Layout.row: 3
        }

        OtcepsView{
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.row: 4
        }

        ProgressBarPanel {
            Layout.fillWidth: true
            Layout.preferredHeight: 20
            Layout.row: 5
        }

        AlarmMessage {
            Layout.fillWidth: true
            Layout.row: 6
        }
    }
}
