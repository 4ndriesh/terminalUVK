#include "json.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFileDialog>
#include <QFile>

Json::Json(const QString & path)
{
    QFile jsonFile(path);
    if (!jsonFile.open(QIODevice::ReadOnly))
    {
        qWarning("Couldn't open save file.");
        return;
    }

    // Считываем весь файл
    QByteArray saveData = jsonFile.readAll();
    jsonFile.close();
    // Создаём QJsonDocument
    QJsonDocument jsonDocument(QJsonDocument::fromJson(saveData));
    // Из которого выделяем объект в текущий рабочий QJsonObject
    m_currentJsonObject = jsonDocument.object();
}

QString Json::getMXml(const QString &get,const QString &select)
{
    QJsonValue itemValue = m_currentJsonObject.value(get);
    QJsonObject itemObject = itemValue.toObject();
    return itemObject.value(select).toString();
    //    QJsonValue item=m_currentJsonObject[get];
    //    return item.toString();
}
QString Json::getSettings(const QString &get)
{
    QJsonValue item=m_currentJsonObject[get];
    return item.toString();
}
