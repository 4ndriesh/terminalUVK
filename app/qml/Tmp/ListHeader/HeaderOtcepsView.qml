import QtQuick.Layouts 1.3
import QtQuick 2.11
import QtQuick.Controls 2.4
import Base 1.0
import StyleModule 1.0

GridLayout {
    id: root
    width: listView.width
    property int heightHeader: listView.height/6
    height: heightHeader>100 ? 100: heightHeader
    rows: 2
    columns: 15

    Repeater {
        model:ListModelHeader{}
        Rectangle {
            id: _number
            Layout.minimumWidth: minimumWidth
            Layout.minimumHeight: minimumHeight
            Layout.maximumHeight: maximumHeight
            Layout.rowSpan: rowSpan
            Layout.columnSpan: columnSpan
            Layout.column: column
            Layout.row: row
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.rightMargin: -4
            Layout.topMargin: -4
            color:  Style.themeDefaultColor
            visible: visibleColumns
            Text { text: name; anchors.centerIn: parent;font.pointSize: Math.min(parent.height,parent.width)/3 }
//            visibleColumns: column>12 ? otcepsModel.qmlVisibleObject:true
        }
    }
}
