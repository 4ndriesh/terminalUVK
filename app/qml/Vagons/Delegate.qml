import QtQuick 2.14
import QtQuick.Layouts 1.14
import SettingsModule 1.0

Rectangle   {
    id: delegate
    width: _vagons.width;
    height: Settings.listView.height/3;
//visible: STATE_ENABLED ? true:false
    states:[
        State {
            name: "scale"
            when: delegate.ListView.isCurrentItem
            PropertyChanges {
                target: delegate
                height:Settings.listView.heightScale;
            }
        }
    ]

    RowLayout   {
        id: layout
        anchors.fill:parent
        spacing: 0
        Number {id: sl_vagon_cnt;txt: STATE_NUMV.toString()}
    }
}







