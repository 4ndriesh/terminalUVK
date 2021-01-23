import QtQuick 2.14
import QtQuick.Layouts 1.14
import SettingsModule 1.0
import "Binding.js" as MyScript
//import QtQuick.VirtualKeyboard 2.14

Rectangle {
    id: textField
    property alias txt: _textPut.text
    Layout.fillWidth: true
    Layout.preferredWidth: delegate.width/12
    height: Settings.baseHeight
    color: delegate.color
    enabled: true
    border.width: Settings.borderWidth

    states:
        [
        State {
            name: "focus"
            when: delegate.ListView.isCurrentItem
                  && manageModel.stateBt.editing===1
                  && textField===state_sp
            PropertyChanges {
                target: _textPut
                enabled:true
                focus: MyScript.borderGreen()
            }

        },
        State {
            name: "focusoff"
            when: (!delegate.ListView.isCurrentItem
                   || manageModel.stateBt.editing===0)
                  && textField===state_sp
            PropertyChanges {
                target: _textPut;
                focus: MyScript.borderBlack();
                cursorVisible:false;
                enabled:false
            }
        }
    ]

    TextInput {
        id: _textPut
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        font.pointSize: parent.height/3
        enabled: true
        inputMethodHints:Qt.ImhFormattedNumbersOnly


        onEditingFinished: {
            switch(textField) {
            case state_sp:
                STATE_SP=_textPut.text;
                break;
            case state_sp_f: STATE_SP_F=_textPut.text;
                break;
            }
        }

    }
    Connections{
        target: manageModel
        function onTextInputChanged(){
            if(manageModel.qmlCurentIndex === index
                    && textField===state_sp
                    && manageModel.stateBt.editing===1){
                _textPut.cursorVisible=true;
                _textPut.cursorPosition= _textPut.text.length;
                _textPut.text=manageModel.textInput;
                _textPut.focus=true;

            }
        }
    }

}
