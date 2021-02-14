import QtQuick 2.14

MouseArea {
    id: eventmouse
    anchors.fill: parent
    hoverEnabled: true
    property int setRegim: 11
    onEntered: { parent.state='Hovering';}
    onExited: { parent.state='';}
    onClicked: {

        if(parent.wink===false){
            manageModel.qmlRegim(11);
            manageModel.qmlRegim(setRegim);
        }
        else if(parent.wink===true){
            manageModel.accept();
        }
    }
}
