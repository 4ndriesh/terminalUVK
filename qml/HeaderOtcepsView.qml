import QtQuick.Layouts 1.3
import QtQuick 2.11
import QtQuick.Controls 2.4

GridLayout {
    id: mainLayout
    //    anchors.verticalCenter: parent.verticalCenter
    anchors.horizontalCenter: parent.horizontalCenter
    property alias visibledel: del.visible
    property alias visibleadd: add.visible
    anchors.leftMargin: 5
    width: parent.width
    height: 60
    rows: 2
    columns: 15
    columnSpacing: 1
    rowSpacing: 1
    Connections {
        target: otcepsModel
        onSetEnabledEdit: {
            visibleIcon=qmlVisible
            visibledel.visible=visibleIcon
            visibleadd.visible=visibleIcon
        }
    }
    Rectangle {

        color: "lightsteelblue"
        Layout.fillWidth: true
        Layout.minimumWidth: 60
        Layout.preferredWidth: 60
        Layout.maximumWidth: 300
        Layout.minimumHeight: 61

        //        width: 60
        //        Layout.fillHeight: true
        Layout.rowSpan: 2
        Layout.row: 1
        Layout.column: 1
        Text { text: "№"; anchors.centerIn: parent;font.pointSize: 16 }
    }

    Repeater {
        model: ["МАРШРУТ", "ДЛИНА", "ВЕС"]
        Rectangle {
            color: "lightsteelblue"
            Layout.fillWidth: true
            Layout.minimumWidth: 120
            Layout.preferredWidth: 120
            Layout.maximumWidth: 600
            Layout.minimumHeight: 30

            Layout.columnSpan: 2
            Layout.row: 1
            Layout.column:index*2+2
            Text { text: modelData ; anchors.centerIn: parent; font.pointSize: 16 }
        }

    }
    Repeater {
        model: ["Задн", "Факт","Задн", "Факт","Задн", "Факт"]
        Rectangle {
            color: "lightsteelblue"
            Layout.fillWidth: true
            Layout.minimumWidth: 60
            //            Layout.preferredWidth: 60
            Layout.maximumWidth: 300
            Layout.minimumHeight: 30
            Layout.row: 2
            Layout.column: index+2
            Text { text: modelData ; anchors.centerIn: parent; font.pointSize: 16 }
        }

    }

    Repeater {
        model: ["3ТП", "3ТП", "3ТП", "3ТП", "3ТП"]
        Rectangle {
            color: "lightsteelblue"
            Layout.fillWidth: true
            Layout.minimumWidth: 60
            //            Layout.preferredWidth: 60
            Layout.maximumWidth: 300
            Layout.minimumHeight: 60

            Layout.rowSpan: 2
            Layout.row: 1
            Layout.column: index+8
            Text { text: modelData ; anchors.centerIn: parent; font.pointSize: 16 }
        }
    }
    //    Repeater {
    //        id:rep
    //        model: ["",""]

    //        Rectangle {
    //            id:icon
    //            visible: false
    //            color: "lightsteelblue"
    //            Layout.fillWidth: true
    //            Layout.minimumWidth: 60
    //            //            Layout.preferredWidth: 60
    //            Layout.maximumWidth: 300
    //            Layout.minimumHeight: 60

    //            Layout.rowSpan: 2
    //            Layout.row: 1
    //            Layout.column: index+13
    //            Text { text: modelData ; anchors.centerIn: parent; font.pointSize: 16 }
    //        }
    //    }
    Rectangle {
        id:del
        visible: visibleIcon
        color: "lightsteelblue"
        Layout.fillWidth: true
        Layout.minimumWidth: 60
        //            Layout.preferredWidth: 60
        Layout.maximumWidth: 300
        Layout.minimumHeight: 60

        Layout.rowSpan: 2
        Layout.row: 1
        Layout.column: 13
    }

    Rectangle {
        id:add
        visible: visibleIcon
        color: "lightsteelblue"
        Layout.fillWidth: true
        Layout.minimumWidth: 60
        //            Layout.preferredWidth: 60
        Layout.maximumWidth: 300
        Layout.minimumHeight: 60

        Layout.rowSpan: 2
        Layout.row: 1
        Layout.column: 14
    }


}
