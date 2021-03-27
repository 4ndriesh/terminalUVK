import QtQuick 2.0
import SettingsModule 1.0

Text {
    id: _textPut
    anchors.fill: parent
    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignHCenter
    font.family: Settings.listView.fontFamily;
    font.pointSize: parent.height/2
    fontSizeMode: Text.Fit
}
