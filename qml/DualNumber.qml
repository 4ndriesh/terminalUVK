import QtQuick 2.0
import QtQuick.Layouts 1.14
Item {
    id: container
    Layout.fillWidth: true
    Layout.minimumWidth: 120
    Layout.maximumWidth: 600
    Layout.minimumHeight: 60

    property alias  txt1: num1.txt
    property alias  txt2: num2.txt
    property var name1
    property var name2

    function getVisible()
    {
        var Visible=true;
        if(txt1 == txt2)
        {
            Visible=false;
        }
        else
        {
            Visible=true;
        }
        return Visible
    }

    Rectangle {
        id: rectangle
        anchors.fill: parent
        clip: true
        radius: 4


        RowLayout {
            id: layout
            anchors.fill: parent
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            spacing: 1

            Number { id: num1; name: name1}
            Number { id: num2; name: name2;visible: getVisible(); }

        }
    }

}
