import QtQuick 2.3
import QtQuick.Controls 2.14

Popup {
    id:_rchaindialog
    parent: Overlay.overlay
    x: Math.round((parent.width-width)/2)
    y: Math.round((parent.height-height)/2)
    height: 400
    width: 800
    focus: true
     ListView{
        id:listRChainView
        anchors.fill: parent
        highlightFollowsCurrentItem: true
        currentIndex: rChain.qmlChainItem
        model:rChain.qmlRChain
        delegate: DelegateRChain{}
        highlight: Highlight{
            id:highliteBarChain;
            z:2
            heightHighlite: 30
//            height: listRChainView.currentItem.height
            yHighlite:0;
            width: _rchaindialog.width
//            y: listRChainView.currentItem.y;
        }
    }
     onClosed: {
         rChain.qmlChainItem=0;
         manageModel.selectHook=0;
         msgTimer.running=false;
     }
     onOpened: {
         rChain.addRChain();
         manageModel.selectHook=1;
         msgTimer.running=true;
     }

     Timer {
         id: msgTimer
         interval: 1000
         repeat: true
         running: false
         onTriggered: rChain.addRChain();
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
