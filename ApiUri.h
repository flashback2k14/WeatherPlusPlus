#ifndef APIURI_H
#define APIURI_H

#include <QString>


const static QString appId = "ba424016b92f34904aacdef3c4b65e1e";


class ApiUri {

public:
    static QString buildCurrentWeatherUri(QString cityName) {
        return QString("http://api.openweathermap.org/data/2.5/weather?q=") + cityName + QString("&APPID=") + ::appId;
    }

    static QString buildForecastWeatherUri(QString cityName) {
        return QString("http://api.openweathermap.org/data/2.5/forecast?q=") + cityName + QString("&APPID=") + ::appId;
    }
};

#endif
