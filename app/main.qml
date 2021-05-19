import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Window 2.14
import Otcep 1.0
import Vagons 1.0
import Base 1.0
import SettingsModule 1.0

Window {
    id:mainwindow
    visible: true
    visibility: "Maximized"
    minimumWidth: 1000
    minimumHeight: 600
    //    height: 1024
    //    width: 1280
    color: Settings.window.backgroundColor
    title: qsTr("Терминал УВК")

    GridLayout{
        anchors.fill: parent
        rows: 7
        columns:2
        columnSpacing:0
        rowSpacing: 5

        ButtonPanel {
            id: controlPanel
            Layout.row: 1
            Layout.columnSpan: 2
        }

        Header {
            Layout.fillWidth: true
            Layout.row: 2
            Layout.columnSpan: 2
        }

        OtcepsView{
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.row: 3
            Layout.column: 0
        }

        VagonsView{
            Layout.preferredWidth: parent.width/Settings.header.column
            Layout.fillHeight: true
            Layout.row: 3
            Layout.column: 1
        }

        ProgressBarPanel {
            Layout.fillWidth: true
            Layout.preferredHeight: 20
            Layout.row: 4
            Layout.columnSpan: 2
        }

        AlarmMessage {
            Layout.fillWidth: true
            Layout.row: 5
            Layout.columnSpan: 2
        }

        InfoRospusk {
            Layout.fillWidth: true
            Layout.row: 6
            Layout.columnSpan: 2
        }
    }
}
