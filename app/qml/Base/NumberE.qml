import QtQuick 2.14
import QtQuick.Layouts 1.14
import SettingsModule 1.0

Rectangle {
    id: textField
    property alias txt: _textPut.text
    property alias textEnabled: _textPut.enabled
    property alias textPutfocus: _textPut.focus

    Layout.fillWidth: true
    Layout.fillHeight: true
    Layout.preferredWidth: listEdit.width/10
    height: 60
    border.width: Settings.listView.borderWidth
    TextInput {
        id: _textPut
        anchors.fill: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.family: Settings.listView.fontFamily;
        font.pointSize: parent.height*0.5
        inputMethodHints:Qt.ImhFormattedNumbersOnly
//        enabled: false
        onEditingFinished: {
            if(textField===state_sp)
                sp=_textPut.text;
            else if(textField===state_sp_f)
                sl_vagon_cnt=_textPut.text;
        }
    }
    //    Text {
    //        id: _textPut
    //        anchors.fill: parent
    //        verticalAlignment: Text.AlignVCenter
    //        horizontalAlignment: Text.AlignHCenter
    //        font.family: Settings.listView.fontFamily;
    //        font.pointSize: parent.height*0.5
    //        fontSizeMode: Text.Fit
    //        //        enabled: false
    //        //        inputMethodHints:Qt.ImhFormattedNumbersOnly
    //        focus: false


    //    }

}
