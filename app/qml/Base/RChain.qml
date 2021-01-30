import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import QtQml.Models 2.14
import Message 1.0

Dialog {
    id:_rchaindialog
    height: 400
    width: 600
    //    visible: true
    title: "Рельсовые цепи"
    modality: Qt.WindowModal
    standardButtons: StandardButton.Close
    ListView{
        id:listRChainView
        anchors.fill: parent
//        highlightFollowsCurrentItem: true
//        highlight:
//            Rectangle {
//            id:highlight;
//            z:10;
//            width:listRChainView.width;
//            color: "transparent"
//            border.color: "black";
//            border.width: 4;
//            radius: 5;
//        }
        focus: true
        //        model:displayDelegateModel
        //                        model:manageModel.listMsg
        model:manageModel.qmlRChain
        delegate: DelegateRChain{}
    }
    Component.onCompleted: {visible=false;
        //        _rchaindialog.close();
        //        manageModel.addRChain();
    }
}

