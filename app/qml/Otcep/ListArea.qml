import QtQuick 2.0

MouseArea {
    id: mouseArea
    anchors.fill: parent
    acceptedButtons: Qt.LeftButton | Qt.Wheel
    onClicked: {
//        if(manageModel.stateBt.bef_regim>=3 && manageModel.stateBt.bef_regim<=5)
//            return;
        if(manageModel.stateBt.regim===1)return;
        if (mouse.button === Qt.LeftButton)
        {
            manageModel.qmlCurrentIndex=index;
            manageModel.qmlRegim(10);
        }
    }

}
