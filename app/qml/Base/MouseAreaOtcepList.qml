import QtQuick 2.0
import QtQuick.Controls 2.0
import SettingsModule 1.0
import Impl 1.0


MouseArea {
    id: mouseArea
    anchors.fill: parent
    acceptedButtons: Qt.LeftButton | Qt.Wheel
    onClicked: {
        if(manageModel.stateBt.bef_regim>=3 && manageModel.stateBt.bef_regim<=5)
            return;
        if (mouse.button === Qt.LeftButton)
        {
            manageModel.qmlCurentIndex=index;
            manageModel.qmlRegimEditing(10);
        }
    }
}
