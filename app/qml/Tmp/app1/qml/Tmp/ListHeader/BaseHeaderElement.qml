import QtQuick 2.0
import StyleModule 1.0

Rectangle {
    property string nameColumns
    property bool visibleColumns
    color:  Style.themeDefaultColor
    visible: visibleColumns
    Text { text: nameColumns; anchors.centerIn: parent;font.pointSize: Math.min(parent.height,parent.width)/3 }
}
