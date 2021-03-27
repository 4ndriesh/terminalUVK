import QtQuick 2.14
import QtQuick.Layouts 1.14
import SettingsModule 1.0
import Base 1.0

Rectangle {
    id: _st_num
    property variant st_num: STATE_EXTNUMPART ? STATE_EXTNUM+"."+STATE_EXTNUMPART:STATE_EXTNUM
    Layout.fillHeight: true
    Layout.fillWidth: true
    Layout.preferredWidth: _otceps.prefWidthState
    height: Settings.listView.height;
    color: delegate.color
    border.width: Settings.listView.borderWidth
    TextOut
    {
        text:STATE_EXTNUM ? st_num:STATE_NUM;
    }
    TextOut
    {
        anchors.margins: 5
        verticalAlignment: Text.AlignBottom
        horizontalAlignment: Text.AlignRight
        font.pointSize: parent.height/4
        text: STATE_EXTNUM ? STATE_NUM:"";
    }
}
