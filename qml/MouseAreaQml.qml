import QtQuick 2.0
import QtQuick.Controls 2.0
//Item {
//    id: itemMouseArea
//    property alias enabledList: mouseArea.enabled

MouseArea {
    id: mouseArea
    function selectCurentIndex()
    {

        if (delegate.ListView.isCurrentItem)
//            delegate.ListView.view.currentIndex = -1;
            delegate.ListView.view.currentIndex = model.index;
        else
            delegate.ListView.view.currentIndex = model.index;

    otcepsModel.setGlobalCurentIndex(listView.currentIndex);
    }
    anchors.fill: parent
    enabled: visibleIcon
    acceptedButtons: Qt.LeftButton | Qt.RightButton
    //onClicked: delegate.ListView.view.currentIndex = model.index // if only selection is wanted
    onClicked: {
        //console.debug("click");
        if (mouse.button === Qt.RightButton)
        {
            selectCurentIndex();
            subMenu.popup();

        }

        if (mouse.button === Qt.LeftButton)
        {
            selectCurentIndex();
        }
    }
    onPressAndHold: {
        if (mouse.source === Qt.MouseEventNotSynthesized)
            subMenu.popup()
    }
    SubMenuOtcepView{id:subMenu}
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
    Connections{
        target: otcepsModel
        onSetQmlCurrentItem: {
//            console.log(listView.currentIndex)
            delegate.ListView.view.currentIndex = inc_dec;
        }
    }
}
