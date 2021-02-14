#include "json.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFileDialog>
#include <QFile>

Json::Json()
{
onLoadSettings();
}
void Json::onLoadSettings()
{
    QFile jsonFile(":/settings.json");
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
    return;
}
QString Json::getMXml(const QString &get)
{
    QJsonValue item=m_currentJsonObject[get];
    return item.toString();
}
