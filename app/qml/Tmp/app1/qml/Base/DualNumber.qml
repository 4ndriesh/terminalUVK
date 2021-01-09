import QtQuick 2.14
import QtQuick.Layouts 1.4

Rectangle {
    id: container
    color: delegate.color
    Layout.fillWidth: true
    Layout.preferredWidth: parent.width/6
    height: 60
    property alias objN1:num1.objectName
    property alias objN2:num2.objectName
    property alias  txt1: num1.txt
    property alias  txt2: num2.txt

    RowLayout {
        id: layout

        anchors.fill: parent
        spacing: 0

        Number { id: num1; }
        Number { id: num2; }
    }
}

