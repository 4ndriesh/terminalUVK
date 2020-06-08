import QtQuick 2.10
import QtQuick.Controls 2.3


Page {
    //    width: 600
    //    height: 400
    //    anchors.fill: parent
    header: Label {
        text: qsTr("Роспуск")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    OtcepsView {
        anchors.fill: parent
    }


    //    GridLayoutOtcepsView {anchors.fill: parent}

    //    footer: Label {
    //        text: qsTr("Вы находитесь в нужном месте ;) Main TUVK.")
    //    }
}
