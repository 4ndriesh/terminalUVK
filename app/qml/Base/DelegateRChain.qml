import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.1
import SettingsModule 1.0
import ResourceProvider 1.0

Rectangle {
    id: delegateRChain
    color: Settings.backgroundColor
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
            color: Settings.backgroundListViewRChain
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

            states: [
                State {
                    name: "NORMAL"
                    PropertyChanges { target: textField; border.width: Settings.borderWidth }
                },
                State {
                    name: "HOVER"
                    PropertyChanges { target: textField; border.width: 4 }
                }
            ]

            MouseArea{
                anchors.fill: parent;

                hoverEnabled: true

                onEntered: {
                    parent.state = "HOVER";
                }
                onExited: {
                    parent.state = "NORMAL";
                }
                onClicked: {
                    listRChainView.currentIndex=index;
                    manageModel.resetRChain(_textRChain.text);
                    manageModel.addRChain();
                }
            }
        }
    }
}

