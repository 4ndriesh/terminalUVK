import QtQuick 2.14
import QtQuick.Layouts 1.14
import SettingsModule 1.0
import Base 1.0

Rectangle {
    id: textField
    height: Settings.listView.height;
    Layout.preferredWidth: _otceps.prefWidthState
    Layout.fillHeight: true
    Layout.fillWidth: true
    color: delegate.color
    border.width: Settings.listView.borderWidth
}
