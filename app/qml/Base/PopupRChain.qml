import QtQuick 2.3
import QtQuick.Controls 2.14

Popup {
    id:_rchaindialog
    parent: Overlay.overlay
    x: Math.round((parent.width-width)/2)
    y: Math.round((parent.height-height)/2)
    height: 400
    width: 600
     ListView{
        id:listRChainView
        anchors.fill: parent
        currentIndex: manageModel.qmlCurentIndex
//        highlightFollowsCurrentItem: true
        model:manageModel.qmlRChain
        delegate: DelegateRChain{}
        highlight: Highlight{
            id:highliteBarChain;
            z:2
            height: listRChainView.currentItem.height
            y: listRChainView.currentItem.y;}
    }
     onClosed: console.log("close")
//    Component.onCompleted: {
////                _rchaindialog.close();
//        //        manageModel.addRChain();
//    }
}
