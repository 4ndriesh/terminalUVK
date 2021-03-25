import QtQuick 2.14
import QtQuick.Layouts 1.14
import SettingsModule 1.0

Rectangle {
    id: textField
    property alias txt: _textPut.text
    Layout.fillWidth: true
    Layout.fillHeight: true
    Layout.preferredWidth: _vagons.width/Settings.header.column
    height: Settings.listView.height;
    border.width: Settings.listView.borderWidth
    color: delegate.color

    Text {
        id: _textPut
        anchors.fill: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.family: Settings.listView.fontFamily;
        font.pointSize: parent.height/2
        fontSizeMode: Text.Fit
    }
}
