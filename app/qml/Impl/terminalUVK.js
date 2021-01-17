
function getColore(qmlRegim, qmlPUT_NADVIG)
{
    var Colore=Settings.themeHeaderColor;
    if((qmlRegim===1 && qmlPUT_NADVIG===1) ||
       (qmlRegim===1 && qmlPUT_NADVIG===2)){
        Colore=Settings.themeRegimColor
    }
    else{
        Colore=Settings.themeHeaderColor

    }
    return Colore
}
