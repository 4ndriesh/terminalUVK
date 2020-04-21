import QtQuick 2.0

MouseArea {
                   anchors.fill: parent
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
               }
