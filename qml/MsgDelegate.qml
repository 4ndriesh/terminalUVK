import QtQuick 2.0
Component {
    id: listDelegate

    //! [0]
    Rectangle {
        //! [0]
        id: delegateItem
        color: "#FFFFE0"
        width: listMsgView.width; height: 50
        clip: true
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            text: modelData
            font.pixelSize: 18
            color: "black"
        }
    }

}
