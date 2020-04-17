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
            case "STATE_NUM": STATE_NUM=text.text;
                break;
            case "STATE_MAR": STATE_MAR=text.text;
                break;
            case "STATE_MAR_F": STATE_MAR_F=text.text;
                break;
            case "STATE_SL_KAT": STATE_SL_KAT=text.text;
                break;
            case "STATE_ZKR_KAT": STATE_ZKR_KAT=text.text;
                break;
            case "STATE_SL_KAT": STATE_SL_KAT=text.text;
                break;
            case "STATE_ZKR_KAT": STATE_ZKR_KAT=text.text;
                break;
            case "STATE_ZKR_BAZA": STATE_ZKR_BAZA=text.text;
                break;
            case "STATE_NAGON": STATE_NAGON=text.text;
                break;
            case "STATE_UR": STATE_UR=text.text;
                break;
            case "STATE_V": STATE_V=text.text;
                break;
            case "STATE_KZP": STATE_KZP=text.text;
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

