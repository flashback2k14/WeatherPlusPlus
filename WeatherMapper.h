#ifndef WEATHERMAPPER_H
#define WEATHERMAPPER_H

#include <iostream>
#include <map>


class WeatherMapper {

private:
    std::map<std::string, std::string> weathers;

public:
    WeatherMapper() {
        weathers["thunderstorm with light rain"] = "clouds-with-lighting-littlerain";
        weathers["thunderstorm with rain"] = "clouds-with-lighting-rain";
        weathers["thunderstorm with heavy rain"] = "clouds-with-lighting-rain";
        weathers["light thunderstorm"] = "clouds-with-lighting";

        weathers["thunderstorm"] = "clouds-with-lighting";
        weathers["heavy thunderstorm"] = "clouds-with-2lighting";
        weathers["ragged thunderstorm"] = "clouds-with-2lighting";
        weathers["thunderstorm with light drizzle"] = "clouds-with-lighting-littlerain";

        weathers["thunderstorm with drizzle"] = "clouds-with-lighting-rain";
        weathers["thunderstorm with heavy drizzle"] = "clouds-with-lighting-rain";
        weathers["light intensity drizzle"] = "clouds-with-littlerain";
        weathers["drizzle"] = "clouds-with-rain";

        weathers["heavy intensity drizzle"] = "clouds-with-rain";
        weathers["drizzle rain"] = "clouds-with-rain";
        weathers["heavy intensity drizzle rain"] = "clouds-with-rain";
        weathers["shower rain and drizzle"] = "clouds-with-rain";

        weathers["heavy shower rain and drizzle"] = "clouds-with-rain";
        weathers["shower drizzle"] = "clouds-with-rain";
        weathers["light rain"] = "clouds-with-littlerain";
        weathers["moderate rain"] = "clouds-with-rain";

        weathers["heavy intensity rain"] = "clouds-with-rain";
        weathers["very heavy rain"] = "clouds-with-rain";
        weathers["extreme rain"] = "clouds-with-rain";
        weathers["freezing rain"] = "clouds-with-rain";

        weathers["light intensity shower rain"] = "clouds-with-rain";
        weathers["shower rain"] = "clouds-with-rain";
        weathers["heavy intensity shower rain"] = "clouds-with-rain";
        weathers["ragged shower rain"] = "clouds-with-rain";

        weathers["light snow"] = "clouds-with-littlesnow";
        weathers["snow"] = "clouds-with-snow";
        weathers["heavy snow"] = "clouds-with-snow";
        weathers["sleet"] = "clouds-with-snow";

        weathers["shower sleet"] = "clouds-with-snow";
        weathers["light rain and snow"] = "sun-rain-and-snow-01";
        weathers["rain and snow"] = "sun-rain-and-snow-01";
        weathers["light shower snow"] = "clouds-with-snow";

        weathers["shower snow"] = "clouds-with-snow";
        weathers["heavy shower snow"] = "clouds-with-snow";
        weathers["mist"] = "sun-haze-01";
        weathers["smoke"] = "sun-haze-01";

        weathers["haze"] = "sun-haze-01";
        weathers["sand, dust whirls"] = "sun-haze-01";
        weathers["fog"] = "sun-haze-01";
        weathers["sand"] = "sun-haze-01";

        weathers["dust"] = "sun-haze-01";
        weathers["volcanic ash"] = "sun-haze-01";
        weathers["squalls"] = "sun-windy-01";
        weathers["tornado"] = "sun-windy-01";

        weathers["sky is clear"] = "sun";
        weathers["few clouds"] = "sun-with-1cloud";
        weathers["scattered clouds"] = "sun-with-3clouds";
        weathers["broken clouds"] = "sun-with-3clouds";

        //tornado exists twice in the gist
        weathers["overcast clouds"] = "sun-with-3clouds";
        weathers["tropical storm"] = "sun-windy-01";
        weathers["hurricane"] = "sun-windy-01";
        weathers["cold"] = "sun-with-clouds-littlesnow";

        weathers["hot"] = "sun";
        weathers["windy"] = "sun-windy-01";
        weathers["hail"] = "sun";
        weathers["calm"] = "sun";

        weathers["gentle breeze"] = "sun-windy-01";
        weathers["light breeze"] = "sun-windy-01";
        weathers["moderate breeze"] = "sun-windy-01";
        weathers["fresh breeze"] = "sun-windy-01";

        weathers["strong breeze"] = "sun-windy-01";
        weathers["high wind, near gale"] = "sun-windy-01";
        weathers["gale"] = "sun-windy-01";
        weathers["severe gale"] = "sun-windy-01";

        weathers["storm"] = "sun-windy-01";
        weathers["violent storm"] = "sun-windy-01";
        // hurricane exists twice
    }

    std::string getWeatherIcon(std::string name){
        return weathers.at(name);
    }
};

#endif
