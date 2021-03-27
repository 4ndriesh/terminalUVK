import QtQuick 2.14
import QtQuick.Layouts 1.14
import SettingsModule 1.0
import Base 1.0

Rectangle {
    id: state_sp;
    Layout.fillHeight: true
    Layout.fillWidth: true
    Layout.preferredWidth:_otceps.prefWidthState
    height: Settings.listView.height;
    color: delegate.color
    border.width: Settings.listView.borderWidth

    states:[
        State {
            name: "red"
            when: STATE_ERROR===1
            PropertyChanges {
                target: state_sp
                color:delegate.items_color[0]
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

    TextOut
    {
        text:STATE_SP ? STATE_SP:"";
    }
}
