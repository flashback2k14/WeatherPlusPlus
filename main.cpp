#include <iostream>
#include <boost/network/protocol/http/client.hpp>

#include "ApiCall.h"

using namespace boost::network;

int main() {
    std::string uri = "http://api.openweathermap.org/data/2.5/forecast/city?id=524901&APPID=ba424016b92f34904aacdef3c4b65e1e";
    ApiCall forecastByCity(uri);
    std::string resp = forecastByCity.request();
    std::cout << resp << std::endl;
    return 0;
}