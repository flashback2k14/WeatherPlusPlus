#ifndef WEATHERMAPPER_H
#define WEATHERMAPPER_H

#include <iostream>
#include <map>


class WeatherMapper {

private:
    std::map<std::string, std::string> weathersByDesc;
    std::map<std::string, std::string> weathersByIcon;

public:
    WeatherMapper() {
        // day icons
        weathersByIcon["01d"] = "sun";
        weathersByIcon["02d"] = "sun-with-1cloud";
        weathersByIcon["03d"] = "clouds";
        weathersByIcon["04d"] = "clouds";
        weathersByIcon["09d"] = "clouds-with-rain";
        weathersByIcon["10d"] = "sun-with-2cloud-rain";
        weathersByIcon["11d"] = "sun-with-2cloud-littlerain";
        weathersByIcon["13d"] = "sun-with-clouds-show";
        weathersByIcon["50d"] = "sun-haze-01";
        // night icons
        weathersByIcon["01n"] = "moon";
        weathersByIcon["02n"] = "moon-with-clouds";
        weathersByIcon["03n"] = "clouds";
        weathersByIcon["04n"] = "clouds";
        weathersByIcon["09n"] = "clouds-with-rain";
        weathersByIcon["10n"] = "moon-drizzle-01";
        weathersByIcon["11n"] = "moon-clouds-thunder-01";
        weathersByIcon["13n"] = "moon-with-clouds-show";
        weathersByIcon["50n"] = "moon-haze-01";


        weathersByDesc["thunderstorm with light rain"] = "clouds-with-lighting-littlerain";
        weathersByDesc["thunderstorm with rain"] = "clouds-with-lighting-rain";
        weathersByDesc["thunderstorm with heavy rain"] = "clouds-with-lighting-rain";
        weathersByDesc["light thunderstorm"] = "clouds-with-lighting";

        weathersByDesc["thunderstorm"] = "clouds-with-lighting";
        weathersByDesc["heavy thunderstorm"] = "clouds-with-2lighting";
        weathersByDesc["ragged thunderstorm"] = "clouds-with-2lighting";
        weathersByDesc["thunderstorm with light drizzle"] = "clouds-with-lighting-littlerain";

        weathersByDesc["thunderstorm with drizzle"] = "clouds-with-lighting-rain";
        weathersByDesc["thunderstorm with heavy drizzle"] = "clouds-with-lighting-rain";
        weathersByDesc["light intensity drizzle"] = "clouds-with-littlerain";
        weathersByDesc["drizzle"] = "clouds-with-rain";

        weathersByDesc["heavy intensity drizzle"] = "clouds-with-rain";
        weathersByDesc["drizzle rain"] = "clouds-with-rain";
        weathersByDesc["heavy intensity drizzle rain"] = "clouds-with-rain";
        weathersByDesc["shower rain and drizzle"] = "clouds-with-rain";

        weathersByDesc["heavy shower rain and drizzle"] = "clouds-with-rain";
        weathersByDesc["shower drizzle"] = "clouds-with-rain";
        weathersByDesc["light rain"] = "clouds-with-littlerain";
        weathersByDesc["moderate rain"] = "clouds-with-rain";

        weathersByDesc["heavy intensity rain"] = "clouds-with-rain";
        weathersByDesc["very heavy rain"] = "clouds-with-rain";
        weathersByDesc["extreme rain"] = "clouds-with-rain";
        weathersByDesc["freezing rain"] = "clouds-with-rain";

        weathersByDesc["light intensity shower rain"] = "clouds-with-rain";
        weathersByDesc["shower rain"] = "clouds-with-rain";
        weathersByDesc["heavy intensity shower rain"] = "clouds-with-rain";
        weathersByDesc["ragged shower rain"] = "clouds-with-rain";

        weathersByDesc["light snow"] = "clouds-with-littlesnow";
        weathersByDesc["snow"] = "clouds-with-snow";
        weathersByDesc["heavy snow"] = "clouds-with-snow";
        weathersByDesc["sleet"] = "clouds-with-snow";

        weathersByDesc["shower sleet"] = "clouds-with-snow";
        weathersByDesc["light rain and snow"] = "sun-rain-and-snow-01";
        weathersByDesc["rain and snow"] = "sun-rain-and-snow-01";
        weathersByDesc["light shower snow"] = "clouds-with-snow";

        weathersByDesc["shower snow"] = "clouds-with-snow";
        weathersByDesc["heavy shower snow"] = "clouds-with-snow";
        weathersByDesc["mist"] = "sun-haze-01";
        weathersByDesc["smoke"] = "sun-haze-01";

        weathersByDesc["haze"] = "sun-haze-01";
        weathersByDesc["sand, dust whirls"] = "sun-haze-01";
        weathersByDesc["fog"] = "sun-haze-01";
        weathersByDesc["sand"] = "sun-haze-01";

        weathersByDesc["dust"] = "sun-haze-01";
        weathersByDesc["volcanic ash"] = "sun-haze-01";
        weathersByDesc["squalls"] = "sun-windy-01";
        weathersByDesc["tornado"] = "sun-windy-01";

        weathersByDesc["sky is clear"] = "sun";
        weathersByDesc["few clouds"] = "sun-with-1cloud";
        weathersByDesc["scattered clouds"] = "sun-with-3clouds";
        weathersByDesc["broken clouds"] = "sun-with-3clouds";

        //tornado exists twice in the gist
        weathersByDesc["overcast clouds"] = "sun-with-3clouds";
        weathersByDesc["tropical storm"] = "sun-windy-01";
        weathersByDesc["hurricane"] = "sun-windy-01";
        weathersByDesc["cold"] = "sun-with-clouds-littlesnow";

        weathersByDesc["hot"] = "sun";
        weathersByDesc["windy"] = "sun-windy-01";
        weathersByDesc["hail"] = "sun";
        weathersByDesc["calm"] = "sun";

        weathersByDesc["gentle breeze"] = "sun-windy-01";
        weathersByDesc["light breeze"] = "sun-windy-01";
        weathersByDesc["moderate breeze"] = "sun-windy-01";
        weathersByDesc["fresh breeze"] = "sun-windy-01";

        weathersByDesc["strong breeze"] = "sun-windy-01";
        weathersByDesc["high wind, near gale"] = "sun-windy-01";
        weathersByDesc["gale"] = "sun-windy-01";
        weathersByDesc["severe gale"] = "sun-windy-01";

        weathersByDesc["storm"] = "sun-windy-01";
        weathersByDesc["violent storm"] = "sun-windy-01";
        // hurricane exists twice
    }

    std::string getWeatherIconByDesc(std::string name) {
        try {
            return weathersByDesc.at(name);
        } catch (exception err) {
            return "";
        }
    }

    std::string getWeatherIconByIcon(std::string icon) {
        try {
            return weathersByIcon.at(icon);
        } catch (exception err) {
            return "";
        }
    }
};

#endif
