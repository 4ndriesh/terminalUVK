import QtQuick 2.0
import QtQuick.Controls 2.0
import SettingsModule 1.0

MouseArea {
    id: mouseArea

    anchors.fill: delegate
    enabled: manageModel.stateBt.editing
//    propagateComposedEvents: true
    acceptedButtons: Qt.LeftButton | Qt.Wheel
    onClicked: {
        if (mouse.button === Qt.LeftButton)
        {
            Number.clickActiveKB=true;
            manageModel.qmlCurentIndex=index;
        }
    }
    onWheel: {
//        manageModel.qmlCurentIndex=index;
        }
}
