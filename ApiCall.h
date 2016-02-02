#ifndef APICALL_H
#define APICALL_H

#include <boost/network/protocol/http/client.hpp>
using namespace boost::network;

class ApiCall{

private:
    http::client m_client;
    http::client::request m_request;

public:
    ApiCall(std::string uri);
    std::string request();
};

#endif
