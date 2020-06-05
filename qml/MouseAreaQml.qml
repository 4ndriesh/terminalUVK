import QtQuick 2.0
import QtQuick.Controls 2.0

MouseArea {
    id: mouseArea
    anchors.fill: parent
    enabled: otcepsModel.qmlVisibleObject
    acceptedButtons: Qt.LeftButton | Qt.RightButton
    onClicked: {
        if (mouse.button === Qt.RightButton)
        {
            otcepsModel.qmlCurentIndex=index;
            subMenu.popup();

        }

        if (mouse.button === Qt.LeftButton)
        {
            otcepsModel.qmlCurentIndex=index;
        }
    }
    onPressAndHold: {
        if (mouse.source === Qt.MouseEventNotSynthesized)
            subMenu.popup()
    }
    SubMenuOtcepView{id:subMenu}
}
