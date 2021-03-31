import QtQuick 2.14
import QtQuick.Layouts 1.14
import SettingsModule 1.0
import Base 1.0

Number {
    id: state_sp;
    states:[
        State {
            name: "red"
            when: STATE_ERROR===1
            PropertyChanges {
                target: state_sp
                color:"red"
            }
        },
        State {
            name: "lightsteelblue"
            when: STATE_LOCATION===1 && delegate.ListView.isCurrentItem && manageModel.focus===1
            PropertyChanges {
                target: state_sp
                focus:true
                color:"lightsteelblue"
            }
        }
    ]
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton
        onClicked: {
            mouse.accepted = false;
            manageModel.focus=1;
        }
      }
    TextOut
    {
        text:STATE_SP ? STATE_SP:"";
    }
}
