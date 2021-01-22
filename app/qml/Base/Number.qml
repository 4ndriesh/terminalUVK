import QtQuick 2.14
import QtQuick.Layouts 1.14
import SettingsModule 1.0
//import QtQuick.VirtualKeyboard 2.14

Rectangle {
    id: textField
    property alias txt: _textPut.text
    property bool clickActiveKB: false
    Layout.fillWidth: true
    Layout.preferredWidth: parent.width/12
    height: Settings.baseHeight
    color: delegate.color
    enabled: true
    border.width: Settings.borderWidth
    states:
        State {
        name: "join"
        when: STATE_SP===STATE_SP_F
        PropertyChanges {
            target: state_sp_f
            visible: false
        }
        PropertyChanges {
            target: state_sp
            Layout.minimumWidth:(parent.width/12)*2
        }
    }

    TextInput {
        id: _textPut
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        font.pointSize: parent.height/3
        enabled: false
        inputMethodHints:Qt.ImhFormattedNumbersOnly
        states:
            [
            State {
                name: "focus"
                when: manageModel.qmlCurentIndex === index
                      && manageModel.stateBt.editing===1
                      && textField===state_sp
                PropertyChanges {
                    target: _textPut
                    enabled:true
                    focus: true
                }

                PropertyChanges {
                    target: state_sp
                    enabled:true;
                    border.color: "green";
                    border.width: 5;

                }



            },
            State {
                name: "focusoff"
                when: (manageModel.qmlCurentIndex !== index
                       || manageModel.stateBt.editing===0)
                      && textField===state_sp
                PropertyChanges {
                    target: state_sp
                    border.color: "black";
                    border.width: 1;
                }
                PropertyChanges {
                    target: _textPut;
                    focus: false;
                    cursorVisible:false;
                    enabled:false
                }
            }
        ]

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
            if(manageModel.qmlCurentIndex === delegate.index
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
