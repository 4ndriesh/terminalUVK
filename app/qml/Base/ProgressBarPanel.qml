import QtQuick 2.14
import QtQuick.Controls 1.4
import QtQuick.Controls 2.14
import SettingsModule 1.0

Rectangle {
    property int maximumValue: manageModel.qmlStatusPB.set_maximumValue
    property int set_value: manageModel.qmlStatusPB.set_value
    property int set_visible: manageModel.qmlStatusPB.set_visible

    ProgressBar {
        id: pb1
        anchors.fill: parent
        from: 0
        to: maximumValue
        value: set_value
        visible: set_visible

        background: Rectangle {
            implicitWidth: 200
            implicitHeight: 6
            color: Settings.backgroundColorPB
            radius: 3
        }

        contentItem: Item {
            implicitWidth: 200
            implicitHeight: 4

            Rectangle {
                width: pb1.visualPosition * parent.width
                height: parent.height
                radius: 2
                color: Settings.themeColorPB
            }
        }
    }
}
