//
// Created by youba on 08/10/2023.
//

#pragma once

#include "AUser.hpp"

class User: public UnitiNetEngine::AUser {
public:
    User(const Json::Value &value, const boost::asio::ip::udp::endpoint &endpoint);
    const Json::Value &getUserInfo() const override;
    void update() override;
    void start() override;
    void end() override;
    bool isThisUser(const Json::Value &user) const override;
private:
    Json::Value _user;
};
