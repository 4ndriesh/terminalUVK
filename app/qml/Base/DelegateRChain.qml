import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.1
import SettingsModule 1.0
import ResourceProvider 1.0

Rectangle {
    id: delegateRChain
    property int counter: 0
    property bool wink: rChain.wink_reset
    color: Settings.backgroundColor
    //        anchors.fill: parent
    width: parent.width; height: 40
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
//                    PropertyChanges { target: _opacitywink; running:false}
//                    PropertyChanges { target: listRChainView; currentIndex:index }
                },
                State {
                    name: "HOVER"
                    StateChangeScript {
                        name: "insertIndex2"
                        script: rChain.qmlChainItem=index
                    }
//                    PropertyChanges { target: _opacitywink; running:false}
//                    PropertyChanges { target: listRChainView; currentIndex:index }
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
                    counter=0;
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
                    if(counter===0){
                        rChain.wink_reset=true;
                        counter=1;
                    }
                    else if(counter===1){
                        //                    listRChainView.currentIndex=index;
                        rChain.resetRChain(_textRChain.text);
                        rChain.addRChain();
                        rChain.wink_reset=false;
                        counter=0;
                    }
                }
            }
        }
    }
}

