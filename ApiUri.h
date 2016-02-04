#ifndef APIURI_H
#define APIURI_H

#include <iostream>
using namespace std;
const static std::string appId = "ba424016b92f34904aacdef3c4b65e1e";

class ApiUri {

public:
    static std::string buildCurrentWeatherUri(std::string cityName) {
        return "http://api.openweathermap.org/data/2.5/weather?q=" + cityName + "&APPID=" + ::appId;
    };

};

#endif
