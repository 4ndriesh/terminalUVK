import QtQuick 2.14
import QtQuick.Layouts 1.14
import Base 1.0
import SettingsModule 1.0

Rectangle{
    height: Settings.header.height

    GridLayout {
        id: _header
        anchors.fill: parent
        rows: 2
        columns: Settings.header.column
        columnSpacing:0
        rowSpacing: 0

        Repeater {
            model: ListModelHeader{}
            Rectangle {
                id: _number
                border.width: Settings.header.borderWidth
                Layout.rowSpan: rowSpan
                Layout.columnSpan: columnSpan
                Layout.column: column
                Layout.row: row
                Layout.fillWidth: true
                Layout.fillHeight: true
                height: minimumHeight
                color:  Settings.header.baseColor
                TextOut {
                    text: name;
                    color: Settings.header.textColor;
                    font.letterSpacing : 3
                }
            }
        }
        Rectangle {
            id: _numberVag
            border.width: Settings.header.borderWidth
            Layout.rowSpan: 1
            Layout.columnSpan: 1
            Layout.column: 9
            Layout.row: 1
            Layout.fillWidth: true
            Layout.fillHeight: true
            height: 30
            color:  Settings.isVisibleAllVag ? Settings.header.allVagColor:Settings.header.baseColor
            TextOut {
                text: "номер";
                color: Settings.header.textColor;
                font.letterSpacing : 3
            }
            MouseArea{
                id: mouseArea
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton
                onClicked: {
                    if (mouse.button === Qt.LeftButton)
                    {
                     Settings.isVisibleAllVag=!Settings.isVisibleAllVag;
                    }
                }
            }
        }
    }
}

