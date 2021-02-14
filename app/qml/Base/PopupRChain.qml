import QtQuick 2.3
import QtQuick.Controls 2.14

Popup {
    id:_rchaindialog
    parent: Overlay.overlay
    x: Math.round((parent.width-width)/2)
    y: Math.round((parent.height-height)/2)
    height: 400
    width: 600
    focus: true
     ListView{
        id:listRChainView
        anchors.fill: parent
        highlightFollowsCurrentItem: false
        currentIndex: rChain.qmlChainItem
        model:rChain.qmlRChain
        delegate: DelegateRChain{}
        highlight: Highlight{
            id:highliteBarChain;
            z:2
            height: listRChainView.currentItem.height
            y: listRChainView.currentItem.y;}
    }
     onClosed: {
         rChain.qmlChainItem=0;
         manageModel.selectHook=0;
     }
     onOpened: {
         rChain.addRChain();
         manageModel.selectHook=1;
     }
     Connections{
         target: rChain
         function onQmlChainItemChanged(){listRChainView.currentIndex=rChain.qmlChainItem}
         function onCloseRChainChanged(){_rchaindialog.close();}
     }
     Connections{
         target: manageModel
         function onOpenRChainChanged(){_rchaindialog.open();}
     }
}
