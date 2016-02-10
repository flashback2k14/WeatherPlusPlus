#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <string>


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
