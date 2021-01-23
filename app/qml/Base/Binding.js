function borderGreen() {
    state_sp.enabled=true;
    state_sp.border.color= "green";
    state_sp.border.width= 5;
    state_sp.Layout.preferredWidth=mainwindow.width/12;
    return true
}
function borderBlack() {
    state_sp.enabled=false;
    state_sp.border.color= "black";
    state_sp.border.width= 1;
    return false
}
function state_spWidth() {
    state_sp.Layout.preferredWidth=(mainwindow.width/12)*2;
    return false
}
