#ifndef APICALL_H
#define APICALL_H

#include <boost/network/protocol/http/client.hpp>
using namespace boost::network;

class ApiCall {

private:
    http::client m_client;
    http::client::request m_request;

public:
    /**
     * Constructor
     */
    ApiCall(std::string uri) : m_client(), m_request(uri) {
         m_request << header("Connection", "close");
    };
    /**
     * Request Data
     */
    std::string request() {
        return body(m_client.get(m_request));
    };

};

#endif
