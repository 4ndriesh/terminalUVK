function getColoreedirSortList(qmlVisible)
{
    var Colore="lightsteelblue";
    if(qmlVisible===true){
        Colore="orange"
    }
    else{
        Colore="lightsteelblue"

    }
    return Colore
}

function getColore(qmlPUT_NADVIG)
{
    var Colore="lightsteelblue";
    if(qmlPUT_NADVIG===1 && putnadviga.buttonText==="РОСПУСК: 1" ||
            qmlPUT_NADVIG===2 && putnadviga.buttonText==="РОСПУСК: 2"){
        Colore="orange"
    }
    else{
        Colore="lightsteelblue"

    }
    return Colore
}

function getColoreStop(qmlStopPause)
{
    var Colore="lightsteelblue";
    if(qmlStopPause===1 && stop.buttonText==="СТОП"){
        Colore="orange"
    }
    else{
        Colore="lightsteelblue"

    }
    return Colore
}

function getColorePause(qmlStopPause)
{
    var Colore="lightsteelblue";
    if(qmlStopPause===2 && pause.buttonText==="ПАУЗА"){
        Colore="orange"
    }
    else{
        Colore="lightsteelblue"

    }
    return Colore
}

function zoomIn( hoveredPoint ) {
    if( hoveredPoint.x - axisX.min <= 1 ) {
        return
    }
    var scale = parseFloat( ( hoveredPoint.x - axisX.min ) / ( axisX.max - axisX.min ) )
    axisX.min++
    axisX.max = ( hoveredPoint.x - axisX.min ) / scale + axisX.min
}


function zoomOut( hoveredPoint) {
    var scale = parseFloat( ( hoveredPoint.x - axisX.min ) / ( axisX.max - axisX.min ) )
    axisX.min--
    axisX.max = ( hoveredPoint.x - axisX.min ) / scale + axisX.min
}
