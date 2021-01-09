import QtQuick 2.14
import QtQuick.Layouts 1.4
import Base 1.0
import StyleModule 1.0

GridLayout {
    id: _header
    width: parent.width
//    property int heightHeader: listView.height/6
    height: Style.baseHeight+20
    rows: 2
    columns: 13
    columnSpacing:0
    rowSpacing: 0

    Repeater {
        model:ListModelHeader{}
        Rectangle {
            id: _number
            border.width: Style.borderWidth
            Layout.rowSpan: rowSpan
            Layout.columnSpan: columnSpan
            Layout.column: column
            Layout.row: row
            Layout.fillWidth: true
            Layout.fillHeight: true
            color:  Style.themeHeaderColor
            Text { text: name;
                anchors.centerIn: parent;
                font.pointSize: parent.height/3
            }
        }
    }
}

