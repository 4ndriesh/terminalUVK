import QtQuick 2.14
import SettingsModule 1.0
import Base 1.0

Rectangle {
    id: delegateRChain
    property bool wink: rChain.wink_reset
    width: _rchain.width;
    height: 40
    color: Settings.rChain.background
    enabled: true
    border.width: Settings.rChain.borderWidth

    Text {
        id: _textRChain
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        text: modelData
        font.pointSize: delegateRChain.height/3
        color: "black"
    }

    states: [
        State {
            name: "NORMAL"
            StateChangeScript {
                name: "insertIndex"
                script: {
                    rChain.qmlChainItem=index
                    rChain.wink_reset=false;
                }
            }
        },
        State {
            name: "HOVER"
            StateChangeScript {
                name: "insertIndex2"
                script: {
                    rChain.qmlChainItem=index;
                    rChain.wink_reset=false;
                }
            }
        }
    ]

    Timer {
        id: _timerwink
        interval: Settings.buttonPanel.timeWink
        running: wink
        onTriggered: {
            rChain.wink_reset=false;
        }
    }

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
            if(!rChain.wink_reset){
                rChain.wink_reset=true;
            }
            else {
                rChain.resetRChain(_textRChain.text);
                rChain.addRChain();
            }
        }
    }
}



