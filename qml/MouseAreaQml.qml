import QtQuick 2.0
//Item {
//    id: itemMouseArea
//    property alias enabledList: mouseArea.enabled
MouseArea {
    id: mouseArea
    anchors.fill: parent
    enabled: visibleIcon
    //onClicked: delegate.ListView.view.currentIndex = model.index // if only selection is wanted
    onClicked: {
        //console.debug("click");
        if (delegate.ListView.isCurrentItem)
        {
            delegate.ListView.view.currentIndex = -1;

        }
        else
        {
            delegate.ListView.view.currentIndex = model.index;
        }
    }
    Connections {
        target: otcepsModel
        onSetEnabledEdit: {
            visibleIcon=qmlVisible
            if(qmlVisible==true){
                listView.currentIndex=0;
                mouseArea.enabled=qmlVisible
            }
            else{
                listView.currentIndex=-1;
                mouseArea.enabled=qmlVisible;
            }
        }
    }
}
