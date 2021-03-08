import QtQuick 2.14
import QtQuick.Layouts 1.14
import SettingsModule 1.0

Rectangle   {
    id: delegate
    width: listEdit.width;
    height: 60;
//    states: [
//        State {
//            name: "NORMAL"
//            StateChangeScript {
//                name: "insertIndex"
//                script: editModel.qmlEditOtcepItem=index
//            }
//        },
//        State {
//            name: "HOVER"
//            StateChangeScript {
//                name: "insertIndex2"
//                script: editModel.qmlEditOtcepItem=index
//            }
//        }
//    ]
    MouseArea{
        id: mouseArea1
        anchors.fill: delegate;
//        hoverEnabled: true
        acceptedButtons: Qt.LeftButton | Qt.Wheel
//        onEntered: {
//            parent.state = "HOVER";
//        }
//        onExited: {
//            parent.state = "NORMAL";
//        }
        onClicked: {
            if (mouse.button === Qt.LeftButton)
            {
                console.log(index);
                editModel.qmlEditOtcepItem=index;
            }
        }
    }
        RowLayout   {
            id: layout
            anchors.fill:parent
            spacing: 0
            NumberE {txt: index+1;}
            NumberE {id: state_sp;txt: sp;}
            NumberE {id: state_sp_f;txt: sl_vagon_cnt;}
        }

}







