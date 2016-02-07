#ifndef WEATHERPARSER_H
#define WEATHERPARSER_H

#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

#include "WeatherData.h"
#include "WeatherUi.h"

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

    QJsonObject getObjectForKey(QString keyName, QJsonObject root) {
        return getGenericValueForKey(keyName, root).toObject();
    }

    QJsonArray getArrayForKey(QString keyName, QJsonObject root) {
        return getGenericValueForKey(keyName, root).toArray();
    }

    std::vector<WeatherDescription> getGenericWeatherDescription(QJsonObject root) {
        std::vector<WeatherDescription> descriptions;
        QJsonArray weatherArray= getArrayForKey(QString("weather"), root);
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

    std::vector<WeatherDescription> getWeatherDescription(){
        return getGenericWeatherDescription(jsonRoot);
    }

    WeatherInfo getWeatheInfo() {
        WeatherInfo info;
        QJsonObject parentObject = getObjectForKey(QString("main"), jsonRoot);
        info.temp = calvinToCelsius(getGenericValueForKey("temp", parentObject).toDouble());
        info.temp_max = calvinToCelsius(getGenericValueForKey("temp_max", parentObject).toDouble());
        info.temp_min = calvinToCelsius(getGenericValueForKey("temp_min", parentObject).toDouble());
        info.humidity = getGenericValueForKey("humidity", parentObject).toInt();
        info.pressure = getGenericValueForKey("pressure", parentObject).toDouble();
        return info;
    }

    std::vector<WeatherDescription> getForecastDescriptions() {
        std::vector<WeatherDescription> descriptions;
        QJsonArray list = getArrayForKey(QString("list"), jsonRoot);
        for(QJsonValue const &listValue : list){
            QJsonArray weathers = getArrayForKey(QString("weather"), listValue.toObject());
            cout << "List value" << endl;
            for(QJsonValue const &weather : weathers){
                cout << "Weather value" << endl;
                WeatherDescription description;
                QJsonObject parentObject = weather.toObject();
                description.icon = valueToStdString(getGenericValueForKey("icon", parentObject));
                description.main = valueToStdString(getGenericValueForKey("main", parentObject));
                description.description = valueToStdString(getGenericValueForKey("description", parentObject));
                descriptions.push_back(description);
            }
        }
        cout << "Size: " << descriptions.size() << endl;
        return descriptions;
    }

    std::vector<WeatherInfo> getForecastInfos() {
        std::vector<WeatherInfo> infos;
        QJsonArray list = getArrayForKey(QString("list"), jsonRoot);
        for(QJsonValue const &listValue : list){
            WeatherInfo info;
            QJsonObject parentObject = getObjectForKey(QString("main"),listValue.toObject());//listValue.toObject();
            info.temp = calvinToCelsius(getGenericValueForKey("temp", parentObject).toDouble());
            cout << "temp: " << info.temp << endl;
            info.temp_max = calvinToCelsius(getGenericValueForKey("temp_max", parentObject).toDouble());
            info.temp_min = calvinToCelsius(getGenericValueForKey("temp_min", parentObject).toDouble());
            info.humidity = getGenericValueForKey("humidity", parentObject).toInt();
            info.pressure = getGenericValueForKey("pressure", parentObject).toDouble();
            infos.push_back(info);
        }
        cout << "Size: " << infos.size() << endl;
        return infos;
    }
};

#endif
