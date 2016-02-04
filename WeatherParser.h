#ifndef WEATHERPARSER_H
#define WEATHERPARSER_H

#include <qbytearray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <QDebug>
#include <iostream>
#include <boost/lexical_cast.hpp>

#include "WeatherData.h"

using namespace std;

const static double gCALVIN = 273.15;

class WeatherParser {
private:
    QJsonObject jsonRoot;

    QJsonValue getGenericValueForKey (QString keyName, QJsonObject jsonObject){
        return jsonObject.value(keyName);
    }

    std::string valueToStdString (QJsonValue value){
        return value.toString().toStdString();
    }

    double calvinToCelsius(double value){
        return value - gCALVIN;
    }

public:
    WeatherParser(std::string json) {
        QByteArray ba(json.data());
        QJsonDocument sourceJsonDoc;
        QJsonDocument destJsonDoc = sourceJsonDoc.fromJson(ba);
        jsonRoot = destJsonDoc.object();
    }

    QJsonValue getValueForKey(QString keyName) {
        return getGenericValueForKey(keyName, jsonRoot);
        //return jsonRoot.value(keyName);
    }

    QJsonObject getObjectForKey(QString keyName) {
        return getGenericValueForKey(keyName, jsonRoot).toObject();
        //return jsonRoot.value(keyName).toObject();
    }

    QJsonArray getArrayForKey(QString keyName) {
        return getGenericValueForKey(keyName, jsonRoot).toArray();
        //return jsonRoot.value(keyName).toArray();
    }

    std::string getTemp(QJsonObject parent) {
        QJsonValue jsonValue = getGenericValueForKey("temp", parent);
        //QJsonValue jsonValue = parent.value(QString("temp"));
        return boost::lexical_cast<std::string>(calvinToCelsius(jsonValue.toDouble()));
    }

    std::vector<WeatherDescription> getWeatherDescription(){
        std::vector<WeatherDescription> descriptions;
        QJsonArray weatherArray= getArrayForKey(QString("weather"));
        for(QJsonValue const &value : weatherArray){
            WeatherDescription description;
            QJsonObject parentObject = value.toObject();
            description.main = valueToStdString(getGenericValueForKey("main", parentObject));
            description.description = valueToStdString(getGenericValueForKey("description", parentObject));
            descriptions.push_back(description);
        }
        return descriptions;
    }

    WeatherInfo getWeatheInfo(){
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
