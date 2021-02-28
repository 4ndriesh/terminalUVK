import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.1
import SettingsModule 1.0

Rectangle {
    id: delegateRChain
    property bool wink: rChain.wink_reset
    width: parent.width; height: 40
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
                script: rChain.qmlChainItem=index
            }
        },
        State {
            name: "HOVER"
            StateChangeScript {
                name: "insertIndex2"
                script: rChain.qmlChainItem=index
            }
        }
    ]
    OpacityAnimator on opacity{
        id: _opacitywink
        target: delegateRChain
        loops: Animation.Infinite;
        from: 0.4;
        to: 1;
        duration: 500
        running: listRChainView.currentIndex===index ? wink:false
        onStopped: {
            delegateRChain.opacity=1;
        }
    }

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



