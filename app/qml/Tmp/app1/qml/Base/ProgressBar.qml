import QtQuick 2.14
import QtQuick.Controls 1.4

Rectangle {
    ProgressBar {
        id: pb1
        anchors.fill: parent
        minimumValue: 0
        maximumValue: otcepsModel.qmlStatusPB.set_maximumValue
        value: otcepsModel.qmlStatusPB.set_value
        visible: otcepsModel.qmlStatusPB.set_visible
    }
}
