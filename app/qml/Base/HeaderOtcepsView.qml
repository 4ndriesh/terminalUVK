import QtQuick 2.14
import QtQuick.Layouts 1.4
import Base 1.0
import SettingsModule 1.0

Rectangle{
    height: Settings.header.height
    GridLayout {
        id: _header
        //    width: parent.width
        //    property int heightHeader: listView.height/6

        anchors.fill: parent
        rows: 2
        columns: 13
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
                Text {
                    text: name;
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.family: Settings.header.fontFamily;
                    color: Settings.header.textColor;
                    font.letterSpacing : 3
                    font.pointSize: parent.height/2;
                    fontSizeMode: Text.Fit
                }
            }
        }
    }
}

