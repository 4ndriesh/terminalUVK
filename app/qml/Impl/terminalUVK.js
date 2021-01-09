
function getColore(qmlRegim, qmlPUT_NADVIG)
{
    var Colore=Style.themeHeaderColor;
    if((qmlRegim===1 && qmlPUT_NADVIG===1 && putnadviga.buttonText==="РОСПУСК: 1") ||
       (qmlRegim===1 && qmlPUT_NADVIG===2 && putnadviga.buttonText==="РОСПУСК: 2")){
        Colore=Style.themeRegimColor
    }
    else{
        Colore=Style.themeHeaderColor

    }
    return Colore
}
