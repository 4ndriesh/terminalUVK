import QtQuick 2.0
import QtQuick.VirtualKeyboard 2.14
import SettingsModule 1.0

InputPanel {
    id: inputPanel
    y: Qt.inputMethod.visible ? parent.height - inputPanel.height : parent.height
    visible: Settings.visibleInputPanel
    anchors.left: parent.left
    anchors.right: parent.right
}

