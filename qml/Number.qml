import QtQuick 2.7
import QtQuick.Layouts 1.3
Rectangle {
    id: textField

    Layout.fillWidth: true
    Layout.minimumWidth: 60
    Layout.maximumWidth: 300
    Layout.minimumHeight: 60
    color: delegate.color
    border.width: 1
    //    radius: height/4
    smooth: true
    property alias txt: text.text
    property int echoMode: TextInput.Normal
    property color col
    property var name
    TextInput {
        id: text
        enabled: otcepsModel.qmlVisibleObject
        onEditingFinished: {
            switch(name) {
            case "STATE_NUM": STATE_NUM=text.text;
                break;
            case "STATE_SP": STATE_SP=text.text;
                break;
            case "STATE_SP_F": STATE_SP_F=text.text;
                break;
            case "STATE_SL_VES": STATE_SL_VES=text.text;
                break;
            case "STATE_ZKR_VES": STATE_ZKR_VES=text.text;
                break;
            case "STATE_SL_VES": STATE_SL_VES=text.text;
                break;
            case "STATE_ZKR_VES": STATE_ZKR_VES=text.text;
                break;
            case "STATE_ZKR_BAZA": STATE_ZKR_BAZA=text.text;
                break;
            case "STATE_NAGON": STATE_NAGON=text.text;
                break;
            case "STATE_SL_UR": STATE_SL_UR=text.text;
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


        echoMode: textField.echoMode

        //                onTextChanged: textField.textChanged(text)

        onFocusChanged: {
            otcepsModel.qmlCurentIndex=index;
            if(focus && otcepsModel.qmlVisibleObject===1){
                textField.border.color = "red"
                textField.border.width = 5
                num2.visible = true
            }else{
                textField.border.color = "grey"
                textField.border.width = 1
            }
        }

    }
//    Connections {
//        target: otcepsModel
//        onSetEnabledEdit: {
//            visibleIcon=qmlVisible
//            textField.border.color = "grey"
//            textField.border.width = 1
//            text.enabled = visibleIcon
//        }
//    }
}
