import QtQuick 2.0
import QtQuick.Layouts 1.1
import Base 1.0
import SettingsModule 1.0
import ResourceProvider 1.0
import QtGraphicalEffects 1.0

Item {
    property int qmlnewList: manageModel.newList
    property int qmluvkLive: manageModel.uvkLive
    RowLayout {
        spacing: 5
        anchors.right: parent.right
        width: 220
        MultiButton {
            id: newSortList
            Layout.alignment: Qt.AlignRight
            //            buttonText: "Новый Лист"
            color: qmlnewList ? Settings.themeBtSignalColorAct:Settings.themeBtSignalColorDAct
            wink: false
            ImageSVG {
                    source: Resources.contacts.defaulticonList
                    size: newSortList.height/1.5
//                    color: "#228b22"
                }
        }

        MultiButton {
            id: _uvkLive
            Layout.alignment: Qt.AlignRight
            Layout.rightMargin:10
            //            buttonText: "УВК"
            color: qmluvkLive ?  Settings.themeBtSignalColorAct:Settings.themeBtSignalColorDAct
            wink: false
            ImageSVG {
                    source: Resources.contacts.defaulticonConnect
                    size: _uvkLive.height/1.5
//                    color: "#dc143c"
                }
        }
    }
}
