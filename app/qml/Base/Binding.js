function borderGreen(index,state) {
    var color=Settings.backgroundListView;
    borderBlack();
    switch(manageModel.stateBt.editing){
    case 0:

        if(state===1){
            manageModel.qmlCurentIndex=index;
            color=delegate.items_color[4];
        }
        break;

    case 1:
        if(delegate.ListView.isCurrentItem){
            state_sp.enabled=true;
            state_sp.border.color= "green";
            state_sp.border.width= 5;
            state_sp.textPutfocus=true;
            state_sp.visibleCursor=true;
            color="lightsteelblue"
        }
        break;
    default:
        break;
    }
    return color;
}
function borderBlack() {
    state_sp.enabled=false;
    state_sp.border.color= "black";
    state_sp.border.width= 1;
    state_sp.textPutfocus=false;
    state_sp.visibleCursor=false;
}
function state_spWidth() {
    state_sp.Layout.preferredWidth=(mainwindow.width/12)*2;
    return false
}
function state_spWidthmin() {
    state_sp.Layout.preferredWidth=(mainwindow.width/12);
    return true
}
