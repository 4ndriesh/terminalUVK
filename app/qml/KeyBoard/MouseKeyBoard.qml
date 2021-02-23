import QtQuick 2.14

MouseArea {
    id: eventmouse
    anchors.fill: parent
    hoverEnabled: true
    onEntered: { parent.state='Hovering';}
    onExited: { parent.state='';}
}
