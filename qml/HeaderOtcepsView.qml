import QtQuick.Layouts 1.3
import QtQuick 2.11
import QtQuick.Controls 2.4

GridLayout {
    id: mainLayout
    //    anchors.verticalCenter: parent.verticalCenter
    anchors.horizontalCenter: parent.horizontalCenter
    height: 50
    rows: 2
    columns: 15
    columnSpacing: 1
    rowSpacing: 1
    Rectangle {
        color: "lightsteelblue"
        width: 60
        Layout.fillHeight: true
        Layout.rowSpan: 2
        Layout.row: 1
        Layout.column: 1
        Text { text: "№"; anchors.centerIn: parent }
    }

    Repeater {
        model: ["МАРШРУТ", "ДЛИНА", "ВЕС"]
        Rectangle {
            color: "lightsteelblue"
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.columnSpan: 2
            Layout.row: 1
            Layout.column:index*2+2
            Text { text: modelData ; anchors.centerIn: parent }
        }

    }
    Repeater {
        model: ["Задн", "Факт","Задн", "Факт","Задн", "Факт"]
        Rectangle {
            color: "lightsteelblue"
            Layout.fillHeight: true
            width: 55
            Layout.row: 2
            Layout.column: index+2
            Text { text: modelData ; anchors.centerIn: parent }
        }

    }

    Repeater {
        model: ["3ТП", "3ТП", "3ТП", "3ТП", "3ТП","",""]
        Rectangle {
            color: "lightsteelblue"
            Layout.fillHeight: true
            width: 50
            Layout.rowSpan: 2
            Layout.row: 1
            Layout.column: index+8
            Text { text: modelData ; anchors.centerIn: parent }
        }
    }

}
