#ifndef WEATHERPARSER_H
#define WEATHERPARSER_H

#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

#include "WeatherData.h"

#include <iostream>
using namespace std;


const static double gCALVIN = 273.15;

class WeatherParser {

private:
    QJsonObject jsonRoot;

    QJsonValue getGenericValueForKey (QString keyName, QJsonObject jsonObject) {
        return jsonObject.value(keyName);
    }

    std::string valueToStdString (QJsonValue value) {
        return value.toString().toStdString();
    }

    double calvinToCelsius(double value) {
        return value - gCALVIN;
    }

public:
    WeatherParser(QByteArray jsonData) {
        QJsonDocument sourceJsonDoc;
        QJsonDocument destJsonDoc = sourceJsonDoc.fromJson(jsonData);
        jsonRoot = destJsonDoc.object();
    }

    QJsonObject getObjectForKey(QString keyName) {
        return getGenericValueForKey(keyName, jsonRoot).toObject();
    }

    QJsonArray getArrayForKey(QString keyName) {
        return getGenericValueForKey(keyName, jsonRoot).toArray();
    }

    std::vector<WeatherDescription> getWeatherDescription() {
        std::vector<WeatherDescription> descriptions;
        QJsonArray weatherArray= getArrayForKey(QString("weather"));
        for(QJsonValue const &value : weatherArray){
            WeatherDescription description;
            QJsonObject parentObject = value.toObject();
            description.icon = valueToStdString(getGenericValueForKey("icon", parentObject));
            description.main = valueToStdString(getGenericValueForKey("main", parentObject));
            description.description = valueToStdString(getGenericValueForKey("description", parentObject));
            descriptions.push_back(description);
        }
        return descriptions;
    }

    WeatherInfo getWeatheInfo() {
        WeatherInfo info;
        QJsonObject parentObject = getObjectForKey(QString("main"));
        info.temp = calvinToCelsius(getGenericValueForKey("temp", parentObject).toDouble());
        info.temp_max = calvinToCelsius(getGenericValueForKey("temp_max", parentObject).toDouble());
        info.temp_min = calvinToCelsius(getGenericValueForKey("temp_min", parentObject).toDouble());
        info.humidity = getGenericValueForKey("humidity", parentObject).toInt();
        info.pressure = getGenericValueForKey("pressure", parentObject).toDouble();
        return info;
    }
};

#endif
