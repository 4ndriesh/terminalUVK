import QtQuick 2.3
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.15
import Base 1.0
import SettingsModule 1.0

Popup {
    id:_listNewEdit
    parent: Overlay.overlay
    x: Math.round((parent.width-width)/2)
    y: Math.round((parent.height-height)/2)
    height: parent.height/2
    width: parent.width/2
    focus: true
    //    background: Rectangle {color: "red"}
    RowLayout{
        anchors.fill: parent
        ListView{
            id:listEdit
            Layout.fillWidth: true
            Layout.fillHeight: true
            highlightFollowsCurrentItem: true
            clip: true
                        currentIndex: editModel.qmlEditOtcepItem
            focus: true
            model:editModel
            delegate: DelegateEditSortList{}
            highlight:
                Rectangle {

                id: delegateRChain
                z:2
                width: parent.width; height: 60
                color: "transparent"
                enabled: true
                border.width: 5
                border.color: "red"
            }

        }

        ColumnLayout{
            Layout.fillWidth: true
            Layout.fillHeight: true
            MultiButton {
                id: clearAll
                buttonText: "Очистить все"
                colorButton: editing ? Settings.buttonColor.regim:Settings.buttonColor.baseColor
                wink: false
                EventMouseArea{
                    onClicked: {
                        editModel.clearAll();
                    }
                }
            }
            MultiButton {
                id: insetUp
                buttonText: "Вставить ДО"
                colorButton: editing ? Settings.buttonColor.regim:Settings.buttonColor.baseColor
                wink: false
                EventMouseArea{
                    onClicked: {
                        editModel.insertOtcep(editModel.qmlEditOtcepItem-1);
                    }
                }
            }
            MultiButton {
                id: insetDown
                buttonText: "Вставить после"
                colorButton: editing ? Settings.buttonColor.regim:Settings.buttonColor.baseColor
                wink: false
                EventMouseArea{
                    onClicked: {
                        editModel.insertOtcep(editModel.qmlEditOtcepItem);
                    }
                }
            }
            MultiButton {
                id: edirSortList
                buttonText: "ВВОД СЛ"
                colorButton: editing ? Settings.buttonColor.regim:Settings.buttonColor.baseColor
                wink: false
                EventMouseArea{
                    onClicked: {
                        editModel.addDataObject();
                    }
                }
            }
        }

    }
    onClosed: {
        editModel.qmlEditOtcepItem=0;
        manageModel.selectHook=0;
    }
    onOpened: {
        manageModel.selectHook=2;
    }
//    Connections{
//        target: editModel
//        function qmlEditOtcepItemChanged(){listEdit.currentIndex=editModel.qmlEditOtcepItem}
////        function onCloseRChainChanged(){_rchaindialog.close();}
//    }

}
