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
    ListView{
        id:listMsgView
        anchors.fill: parent
//        model:displayDelegateModel
//                model:manageModel.listMsg
                    model:manageModel.qmlRChain
                delegate: DelegateRChain{}
    }
    Component.onCompleted: {visible=false;
//        _rchaindialog.close();
//        manageModel.addRChain();
    }
}

