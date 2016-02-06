#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <QLabel>
#include <QImage>
#include <string>


struct ImageData {
    QLabel *mImageLabel;
    QImage *mImage;
    QLabel *mImageDesc;
};

struct WeatherInformation {
    QLabel *mInfoTemp;
    QLabel *mInfoTempMin;
    QLabel *mInfoTempMax;
    QLabel *mInfoHumidity;
    QLabel *mInfoPressure;
};

struct WeatherDescription {
    std::string icon = "unknown";
    std::string main = "unknown";
    std::string description = "unknown";
};

struct WeatherInfo {
    time_t dt = 0;
    double temp = 99999.0;
    double pressure = 99999.0;
    int humidity = 99999;
    double temp_min = 99999.0;
    double temp_max = 99999.0;
};

#endif
