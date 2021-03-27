import QtQuick 2.14
import QtQuick.Layouts 1.14
import SettingsModule 1.0

Rectangle {
    id: delegate
    //цвет в зависимости от STATE_LOCATION
    /*ЖИР и фокус при роспуске ((STATE_LOCATION == 1) && (STATE_GAC_ACTIVE==1)) ||
                             ((STATE_LOCATION == 2) && (STATE_GAC_ACTIVE==1)&&(STATE_ZKR_S_IN==1))

    цвет фона строки
    Белый STATE_LOCATION = 2
    желтый   STATE_ZKR_S_IN==1
    светло серый (STATE_LOCATION == 2) && (STATE_GAC_ACTIVE==1)
    ост - серый

    цвет фона ячейки маршрута
    Красный -STATE_ERROR
    остальн - обычн фон
stat
    EDIT когда ЖИР всегда или (STATE_LOCATION == 2)*/


    property variant items_color: ["red", "yellow","white","silver","lightcyan","orange"]

    width: _otceps.width;
    height: Settings.listView.height;
    visible: STATE_ENABLED ? true:false

    Item {
        id: _focusOtcepstates
        states: [
            State {
                name: "focus"
                when: STATE_IS_CURRENT===1
                StateChangeScript {
                    name: "insertIndex"
                    script: {
                        manageModel.qmlCurrentIndex=STATE_NUM-1;
                    }
                }

                PropertyChanges {
                    target: delegate
                    height:Settings.listView.heightScale;
                }
            },
            State {
                name: "notfocus"
                when: STATE_IS_CURRENT!==1
                PropertyChanges {
                    target: delegate
                    height:Settings.listView.height;
                }
            }
        ]
    }

    Item {
        id: _locationColor
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

    ListArea {id: mouseArea}

    RowLayout   {
        id: layout
        anchors.fill: parent
        spacing: 0

        ST_Num{}

        DualSP {}

        DualVag{}

        Number { txt: STATE_BAZA ? "ДБ":"";}

        Number { txt: STATE_SL_VES ? STATE_SL_VES.toFixed(2):"";}

        ST_Ur{}

        ST_Stra{}

        ST_Strb{}
    }
}







