#include <qbytearray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <QDebug>
#include <iostream>
#include <boost/lexical_cast.hpp>

#ifndef WEATHERPARSER_H
#define WEATHERPARSER_H

using namespace std;

class WeatherParser {
private:
    QJsonObject jsonRoot;
public:
    WeatherParser(std::string json){
        QByteArray ba(json.data());
        QJsonDocument sourceJsonDoc;
        QJsonDocument destJsonDoc = sourceJsonDoc.fromJson(ba);
        jsonRoot = destJsonDoc.object();
    }

    QJsonValue getValueForKey(QString keyName){
        return jsonRoot.value(keyName);
    }

    QJsonObject getObjectForKey(QString keyName){
        return jsonRoot.value(keyName).toObject();
    }

    QJsonArray getArrayForKey(QString keyName){
        return jsonRoot.value(keyName).toArray();
    }

    std::string getTemp(QJsonObject parent){
        QJsonValue jsonValue = parent.value(QString("temp"));
        return boost::lexical_cast<std::string>(jsonValue.toDouble() - 273.15);
    }
};

#endif
