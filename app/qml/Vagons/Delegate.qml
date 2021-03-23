import QtQuick 2.14
import QtQuick.Layouts 1.14
import SettingsModule 1.0

Rectangle   {
    id: delegate
    width: _vagons.width;
    height: Settings.listView.height/3;
//    visible: STATE_NUM_OTCEP===manageModel.qmlCurrentIndex+1? true:false
    visible: STATE_ENABLED ? true:false
    property variant items_color: ["red", "yellow","white","silver","lightcyan","orange"]
    Item {
        id: _scale
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
    }
    Item {
        id: _visible
        states:[
            State {
                name: "visible"
                when: STATE_NUM_OTCEP!==manageModel.qmlCurrentIndex+1
                PropertyChanges {
                    target: delegate
                    visible:false;
                }
            }
        ]
    }
    Item {
        id: _locationColor
        states: [
            State {
                name: "white"
                when: STATE_LOCATION === 1
                PropertyChanges {
                    target: delegate
                    color: delegate.items_color[2]
                }
            },
            State {
                name: "grey"
                when: STATE_LOCATION !== 1
                PropertyChanges {
                    target: delegate
                    color: delegate.items_color[3]
                }
            }
        ]
    }
    RowLayout   {
        id: layout
        anchors.fill:parent
        spacing: 0
        Number {id: sl_vagon_cnt;txt: STATE_NUMV}
    }

}







