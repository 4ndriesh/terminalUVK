import QtQuick 2.14
import QtQuick.Controls 1.4

Rectangle {
    ProgressBar {
        id: pb1
        anchors.fill: parent
        minimumValue: 0
        maximumValue: manageModel.qmlStatusPB.set_maximumValue
        value: manageModel.qmlStatusPB.set_value
        visible: manageModel.qmlStatusPB.set_visible
    }
}
