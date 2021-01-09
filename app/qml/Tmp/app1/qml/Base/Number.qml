import QtQuick 2.14
import QtQuick.Layouts 1.14
import StyleModule 1.0

Rectangle {
    id: textField

    color: delegate.color
    border.width: Style.borderWidth

    Layout.fillWidth: true
    Layout.preferredWidth: parent.width/12
    height: Style.baseHeight

    property alias txt: text.text

    function getVisible()
    {
        var Visible=true;
        if(textField.objectName==='STATE_SP_F' )
            return false
        return true
    }

    states:
        [
        State {
            name: "join"
            when: STATE_SP===STATE_SP_F
            PropertyChanges {
                target: textField
                visible: getVisible()
            }
        }
    ]

    TextInput {
        id: text
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        font.pointSize: parent.height/3
        enabled: otcepsModel.qmlVisibleObject

        onEditingFinished: {
            switch(textField.objectName) {
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
    }

    Connections{
        target: otcepsModel
        onQmlCurrentItemChanged:{

            if(otcepsModel.qmlCurentIndex === index &&
                    textField.objectName==='STATE_SP'
                    && otcepsModel.qmlVisibleObject===1){
                text.forceActiveFocus();
                text.cursorPosition= text.text.length
                textField.border.color = "green"
                textField.border.width = 5
                num2.visible = true
            }else{
                textField.border.color = "black"
                textField.border.width = 1
            }
        }
    }
}
