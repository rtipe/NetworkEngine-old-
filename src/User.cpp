//
// Created by youba on 08/10/2023.
//

#include <iostream>
#include "User.hpp"
#include "Uniti.hpp"

User::User(const Json::Value &value, const boost::asio::ip::udp::endpoint &endpoint):
AUser(value, endpoint),
_user(value) {
    std::cout << "je commence" << std::endl;
    std::unique_ptr<UnitiNetEngine::Object> object = std::make_unique<UnitiNetEngine::Object>(this->_user.asString(), UnitiNetEngine::Uniti::getInstance().getObjectManager().getSendEvent());
    object->getScriptManager().addScript("movementVessel", UnitiNetEngine::Uniti::getInstance().getScriptFactory().createScript("movementVessel", *object));
    object->getScriptManager().getScript("movementVessel").awake(this->_data);
    object->getScriptManager().start();
    UnitiNetEngine::Uniti::getInstance().getObjectManager().addObject(std::move(object));
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
