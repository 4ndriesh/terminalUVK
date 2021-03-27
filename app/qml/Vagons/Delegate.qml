import QtQuick 2.14
import QtQuick.Layouts 1.14
import SettingsModule 1.0

Rectangle   {
    id: delegate
    width: _vagons.width;
    height: Settings.listView.height/3;
    property variant st_num: STATE_NUMV===0 ? STATE_N_IN_OTCEP:STATE_NUMV
    visible: STATE_ENABLED && STATE_NUM_OTCEP===manageModel.qmlCurrentIndex+1? true:false
    //        visible: STATE_ENABLED ? true:false
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
        id: _zkr_progress
        states:[
            State{
                when: STATE_ZKR_PROGRESS===1
                StateChangeScript {
                    name: "currentIndex"
                    script: {
                        vagonsModel.qmlCurrentIndex=index;                        
                    }
                }
            }
        ]
    }

    RowLayout   {
        id: layout
        anchors.fill:parent
        spacing: 0
//        Number{txt:STATE_NUM_OTCEP}
        Number
        {
            id: sl_vagon_cnt;
            txt: st_num
            states: [
                State {
                    name: "yellow"
                    when: STATE_ZKR_PROGRESS===1
                    PropertyChanges {
                        target: delegate
                        color:delegate.items_color[1]
                    }
                },
                State {
                    name: "white"
                    when: STATE_LOCATION === 1
                    PropertyChanges {
                        target: delegate
                        color: items_color[2]
                    }
                },
                State {
                    name: "grey"
                    when: STATE_LOCATION !== 1
                    PropertyChanges {
                        target: delegate
                        color: items_color[3]
                    }
                }
            ]
        }
    }

}







