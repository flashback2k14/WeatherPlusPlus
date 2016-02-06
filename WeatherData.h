#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <string>


struct WeatherDescription {
    std::string icon;
    std::string main;
    std::string description;
};

struct WeatherInfo {
    double temp;
    double pressure;
    int humidity;
    double temp_min;
    double temp_max;
};

#endif
