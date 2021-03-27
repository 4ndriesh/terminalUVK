import QtQuick 2.14
import QtQuick.Layouts 1.14
import SettingsModule 1.0
import Base 1.0

Rectangle {
    id: textField
    property alias txt: _textPut.text
    Layout.fillHeight: true
    Layout.fillWidth: true
    Layout.preferredWidth: delegate.width/Settings.header.column
    height: Settings.listView.height;
    color: delegate.color
    border.width: Settings.listView.borderWidth
    TextOut{id:_textPut}
}
