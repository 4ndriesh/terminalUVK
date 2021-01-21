import QtQuick 2.14
import QtQuick.Layouts 1.14
import SettingsModule 1.0
//import QtQuick.VirtualKeyboard 2.15

Rectangle {
    id: textField
    property alias txt: text.text

    Layout.fillWidth: true
    Layout.preferredWidth: parent.width/12
    height: Settings.baseHeight
    color: delegate.color
    border.width: Settings.borderWidth
    states:
        [
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
            //        },
            //        State {
            //            name: "focus"
            //            when: manageModel.qmlCurentIndex === index
            //                  && manageModel.stateBt.editing===1
            //            PropertyChanges {
            //                target: state_sp
            //                enabled:true;
            //                border.color: "green";
            //                border.width: 5;
            //            }
            //        },
            //        State {
            //            name: "focusoff"
            //            when: manageModel.qmlCurentIndex !== index
            //                  || manageModel.stateBt.editing===0
            //            PropertyChanges {
            //                target: state_sp
            //                border.color: "black";
            //                border.width: 1;
            //                enabled:false;
            //            }
            //        }
    ]

            TextInput {
                id: text
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                font.pointSize: parent.height/3
                enabled: false
                inputMethodHints:Qt.ImhFormattedNumbersOnly

                //        EnterKeyAction.enabled: true
//                EnterKeyAction.enabled: text.text.length > 0 || text.inputMethodComposing

                //        Keys.onReleased: {
                //            if (event.key === Qt.Key_Up) {
                //                event.accepted=false;
                ////                manageModel.qmlCurentIndex--
                //            }
                //            if (event.key === Qt.Key_S) {
                //                manageModel.qmlCurentIndex++
                //            }
                //        }

                onEditingFinished: {
                    switch(textField) {
                    case state_sp: STATE_SP=text.text;
                        break;
                    case state_sp_f: STATE_SP_F=text.text;
                        break;
                    }
                }


                //        onEditingFinished: {
                //            switch(textField.objectName) {
                //            case "STATE_NUM": STATE_NUM=text.text;
                //                break;
                //            case "STATE_SP": STATE_SP=text.text;
                //                break;
                //            case "STATE_SP_F": STATE_SP_F=text.text;
                //                break;
                //            case "STATE_SL_VES": STATE_SL_VES=text.text;
                //                break;
                //            case "STATE_ZKR_VES": STATE_ZKR_VES=text.text;
                //                break;
                //            case "STATE_SL_VES": STATE_SL_VES=text.text;
                //                break;
                //            case "STATE_ZKR_VES": STATE_ZKR_VES=text.text;
                //                break;
                //            case "STATE_ZKR_BAZA": STATE_ZKR_BAZA=text.text;
                //                break;
                //            case "STATE_NAGON": STATE_NAGON=text.text;
                //                break;
                //            case "STATE_SL_UR": STATE_SL_UR=text.text;
                //                break;
                //            case "STATE_V": STATE_V=text.text;
                //                break;
                //            case "STATE_KZP": STATE_KZP=text.text;
                //                break;

                //            }
                //        }
            }

            Connections{
                target: manageModel
                function onQmlCurrentItemChanged(){

                    if(manageModel.qmlCurentIndex === index &&
                            textField.objectName==='STATE_SP'
                            && manageModel.stateBt.editing===1){
                        text.forceActiveFocus();
                        //                    text.selectAll();
                        text.enabled=true;
                        text.cursorVisible=true;
                        text.cursorPosition= text.text.length;
                        textField.border.color = "green";
                        textField.border.width = 5;
                        //                num2.visible = true
                    }else{
                        text.enabled=false;
                        text.cursorVisible=false;
                        textField.border.color = "black"
                        textField.border.width = 1
                    }
                }
            }

            Connections{
                target: manageModel
                function onTextInputChanged(){

                    if(manageModel.qmlCurentIndex === index &&
                            textField.objectName==='STATE_SP'
                            && manageModel.stateBt.editing===1){
                        text.text=manageModel.textInput;
                    }
                }
            }

        }
