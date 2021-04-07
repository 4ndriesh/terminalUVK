import QtQuick 2.14
import QtQuick.Layouts 1.14
import SettingsModule 1.0

Rectangle   {
    id: delegate
    width: _vagons.width;
    height: Settings.listView.height/3;
    property variant st_num: STATE_NUMV===0 ? STATE_N_IN_OTCEP:STATE_NUMV
    property bool visibleVagAll: STATE_ENABLED
    property bool visibleVagOne: STATE_ENABLED && STATE_NUM_OTCEP===manageModel.qmlCurrentIndex+1? true:false

    visible: Settings.isVisibleAllVag ? visibleVagAll:visibleVagOne
    //        visible: STATE_ENABLED ? true:false
    property variant items_color: ["red", "yellow","white","silver","lightcyan","orange"]


    states: [
        State {
            name: "focus"
            when: STATE_IS_CURRENT===1
            StateChangeScript {
                name: "insertIndex"
                script: {
                    vagonsModel.qmlCurrentIndex=index;
//                    manageModel.setPositionVagons();
                }
            }
            PropertyChanges {
                target: delegate
                height:Settings.listView.heightScale
            }
        }
    ]

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
                        color:"yellow"
                    }
                },
                State {
                    name: "white"
                    when: STATE_LOCATION === 1
                    PropertyChanges {
                        target: delegate
                        color: "white"
                    }
                },
                State {
                    name: "silver"
                    when: STATE_LOCATION !== 1
                    PropertyChanges {
                        target: delegate
                        color: "silver"
                    }
                }
            ]
        }
    }
}







