import QtQuick 2.14
import QtQuick.Layouts 1.14
import SettingsModule 1.0

Rectangle {
    id: textField
    property alias txt: _textPut.text
    property alias textEnabled: _textPut.enabled
    property alias textPutfocus: _textPut.focus
    property alias visibleCursor: _textPut.cursorVisible

    Layout.fillWidth: true
    Layout.fillHeight: true
    Layout.preferredWidth: listView.width/10
    height: 60
    color: delegate.color
    enabled: false
    border.width: Settings.borderWidth
    states:
        [
        State {
            name: "join"
            when: STATE_SP===STATE_SP_F
            PropertyChanges {
                target: state_sp_f
                visible: false
                //                visible: MyScript.state_spWidth()
            }
            PropertyChanges {
                target: state_sp
                Layout.preferredWidth: (listView.width/10)*2;
                //                visible: MyScript.state_spWidth()
            }
        },
        State {
            name: "joinoff"
            when: STATE_SP!==STATE_SP_F
            PropertyChanges {
                target: state_sp_f
                visible: true
                //                visible: MyScript.state_spWidthmin()
            }
            PropertyChanges {
                target: state_sp
                Layout.preferredWidth:(listView.width/10);
                //                visible: MyScript.state_spWidthmin()
            }
        }
    ]

    TextInput {
        id: _textPut
        anchors.fill: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.family: Settings.fontFamily;
        font.pointSize: parent.height/3
        enabled: false
        inputMethodHints:Qt.ImhFormattedNumbersOnly
        focus: false

        onEditingFinished: {
            STATE_SP=_textPut.text;
        }
    }
    Connections{
        target: manageModel
        function onTextInputChanged(){
            if(manageModel.qmlCurentIndex === index
                    && textField===state_sp
                    //                    && manageModel.stateBt.editing===1
                    && state_sp.enabled===true)
            {
                _textPut.cursorVisible=true;
                _textPut.cursorPosition= _textPut.text.length;
                _textPut.text=manageModel.textInput;
                _textPut.forceActiveFocus()
            }
        }
    }
}
