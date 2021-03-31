/*цвет в зависимости от STATE_LOCATION
ЖИР и фокус при роспуске ((STATE_LOCATION == 1) && (STATE_GAC_ACTIVE==1)) ||
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

import QtQuick 2.14
import QtQuick.Layouts 1.14
import SettingsModule 1.0
import Base 1.0

Rectangle {
    id: delegate    
    width: _otceps.width;
    height: Settings.listView.height;
    visible: STATE_ENABLED ? true:false
    color: Settings.listView.background;

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
                    height:Settings.listView.heightScale
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

    ListArea {id: mouseArea}

    RowLayout   {
        id: layout
        anchors.fill: parent
        spacing: 0

        ST_Num{}

        DualSP {}

        DualVag{}

        Number {TextOut{text: STATE_BAZA ? "ДБ":"";}}

        Number {TextOut{text: STATE_SL_VES ? STATE_SL_VES.toFixed(2):"";}}

        ST_Ur{}

        ST_Stra{}

        ST_Strb{}
    }
}







