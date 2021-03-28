import QtQuick 2.14

MouseArea {
    id: eventmouse
    property int setRegim: 11
    anchors.fill: parent
    hoverEnabled: true
    onEntered: { parent.state='Hovering';}
    onExited: { parent.state='';}
    onClicked: {
        if(parent.wink===false){
            manageModel.qmlRegim(10);
            manageModel.qmlRegim(setRegim);
        }
        else if(parent.wink===true){
            manageModel.accept();
        }
    }
}
