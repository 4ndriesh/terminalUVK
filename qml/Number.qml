import QtQuick 2.7
import QtQuick.Layouts 1.14
Rectangle {
    id: textField

    Layout.fillWidth: true
    Layout.minimumWidth: 60
    Layout.maximumWidth: 300
    Layout.minimumHeight: 60
    color: delegate.color
    border.width: 1
    border.color: "grey"
    //    radius: height/4
    smooth: true

    property alias txt: text.text
    property int echoMode: TextInput.Normal
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
        //        width: parent.width - (2 * font.pointSize)

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 18


//        echoMode: textField.echoMode

//                onTextChanged: textField.textChanged(text)

        onFocusChanged: {
            if(focus){
                textField.border.color = "red"
                textField.border.width = 5
            }else{
                textField.border.color = "grey"
                textField.border.width = 1
            }
        }
    }
}
