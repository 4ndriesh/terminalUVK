import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Window 2.14
import Impl 1.0
import Base 1.0
import StyleModule 1.0

Window {
    visible: true
    minimumWidth: 1200
    minimumHeight: 600
    color: Style.backgroundColor
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
            Layout.preferredHeight: 50
            Layout.columnSpan:3
            Layout.row: 5
        }
    }
}
