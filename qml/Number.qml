import QtQuick 2.7
import QtQuick.Controls 2.0

Item {
    id: item
    width: 50
    height: 50
    property alias txt: text.text
    property color col
    property var name

    TextInput {
        id: text
        onEditingFinished: {
            switch(name) {
            case "n": n=text.text;
                break;
            case "mar": mar=text.text;
                break;
            case "mar_f": mar_f=text.text;
                break;
            case "len": len=text.text;
                break;
            case "len_f": len_f=text.text;
                break;
            case "kat": kat=text.text;
                break;
            case "kat_f": kat_f=text.text;
                break;
            case "baz": baz=text.text;
                break;
            case "nag": nag=text.text;
                break;
            case "ur": ur=text.text;
                break;
            case "V": V=text.text;
                break;
            case "kzp": kzp=text.text;
                break;

            }
        }
        font.bold: false
        font.pointSize: 18
        color: col
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter
    }
}

