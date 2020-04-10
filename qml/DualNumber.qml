import QtQuick 2.0

Item {
    id: container
    width: 110
    //    height: parent.height
    height: 60

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

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            spacing: 4

            Number { id: num1; name: name1}
            Number { id: num2; name: name2;visible: getVisible(); }

        }
    }

}
