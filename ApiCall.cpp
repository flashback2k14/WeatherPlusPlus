#include "ApiCall.h"

ApiCall::ApiCall(std::string uri): m_client(), m_request(uri) {};

std::string ApiCall::request(){
    http::client client;
    http::client::request request(m_request);
    request << header("Connection", "close");
    http::client::response response = client.get(request);
    return body(response);
}