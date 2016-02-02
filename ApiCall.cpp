#include "ApiCall.h"

ApiCall::ApiCall(std::string uri): m_client(), m_request(uri) {
    m_request << header("Connection", "close");
};

std::string ApiCall::request(){
    return body(m_client.get(m_request));
}