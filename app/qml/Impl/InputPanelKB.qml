import QtQuick 2.0
import QtQuick.Controls 2.14
import QtQuick.VirtualKeyboard 2.14
import SettingsModule 1.0

InputPanel {
    id: inputPanel
    y: Qt.inputMethod.visible ? parent.height - inputPanel.height : parent.height
    visible: Settings.visibleInputPanel
    anchors.left: parent.left
    anchors.right: parent.right
    z: 5
    parent: Overlay.overlay
    focus: true
}

//InputPanel {
//    id: inputPanel
////    parent: mainwindow // <-- This will do the trick
//    anchors.bottom:parent.bottom
//    anchors.left: parent.left
//    anchors.right: parent.right
//    visible: Settings.visibleInputPanel
////    visible: Qt.inputMethod.visible
//}

