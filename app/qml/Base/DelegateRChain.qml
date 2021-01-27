import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.1
import SettingsModule 1.0
import ResourceProvider 1.0

Rectangle {
    id: delegateRChain
    color: "grey"
    //        anchors.fill: parent
    width: parent.width; height: 30
    clip: true
    RowLayout   {
        id: layout
        anchors.fill: parent
        spacing: 5
        Rectangle{
            id: textField
            Layout.fillWidth: true
            Layout.fillHeight: true
            //            Layout.preferredWidth: parent.width/2
            color: "grey"
            enabled: true
            border.width: Settings.borderWidth
            Text {
                id: _textRChain
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: modelData
                font.pointSize: parent.height/3
                color: "black"
            }
            MouseArea{
                anchors.fill: parent;
                onClicked: manageModel.resetRChain(_textRChain.text)
            }
        }


        //        Item{
        //            id: _resetRChain
        //            //            Layout.fillWidth: true
        //            Layout.preferredWidth: parent.width/8
        //            Layout.fillHeight: true
        //            Image {
        //                id: _rcreset
        //                anchors.horizontalCenter: parent.horizontalCenter
        //                anchors.verticalCenter: parent.verticalCenter
        //                source: Resources.contacts.defaultDelIcon
        //                MouseArea{
        //                    anchors.fill: parent;
        //                    onClicked: manageModel.resetRChain(_textRChain.text)
        //                }
        //            }
        //        }
    }
}
