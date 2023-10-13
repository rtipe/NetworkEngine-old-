//
// Created by youba on 08/10/2023.
//

#include <iostream>
#include "User.hpp"
#include "Uniti.hpp"
#include "VesselAlly.hpp"

User::User(const Json::Value &value, const boost::asio::ip::udp::endpoint &endpoint):
AUser(value, endpoint),
_user(value) {
    std::cout << "je commence" << std::endl;
    VesselAlly::createVesselAlly(*this);
}

const Json::Value &User::getUserInfo() const {
    return this->_user;
}

void User::update() {
    //std::cout << "je update" << std::endl;
}

void User::start() {
}

void User::end() {

}

bool User::isThisUser(const Json::Value &user) const {
    return this->_user.asString() == user.asString();
}
