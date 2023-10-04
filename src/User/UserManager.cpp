//
// Created by youba on 01/10/2023.
//

#include "UserManager.hpp"

namespace UnitiNetEngine {

    IUser &UserManager::getUser(size_t id) {
        return *this->_users[id];
    }

    bool UserManager::isUserExist(size_t id) const {
        return this->_users.size() < id;
    }

    bool UserManager::isUserExist(const Json::Value &value) const {
        auto it = std::find_if(this->_users.begin(), this->_users.end(),
        [&] (const std::unique_ptr<IUser> &user) {
            return user->isThisUser(value);
        });
        return it != this->_users.end();
    }

    IUser &UserManager::getUser(const Json::Value &value) {
        auto it = std::find_if(this->_users.begin(), this->_users.end(),
        [&] (const std::unique_ptr<IUser> &user) {
            return user->isThisUser(value);
        });
        return it->operator*();
    }

    void UserManager::addUser(std::unique_ptr<IUser> user) {
        const std::lock_guard<std::mutex> lock(this->_mutex);
        user->start();
        this->_users.push_back(std::move(user));
    }

    std::unique_ptr<IUser> UserManager::createUser(const Json::Value &value, const boost::asio::ip::udp::endpoint &endpoint) {
        return this->_creator(value, endpoint);
    }

    const std::vector<std::unique_ptr<IUser>> &UserManager::getUsers() const {
        return this->_users;
    }

    std::vector<std::unique_ptr<IUser>> &UserManager::getUsers() {
        return this->_users;
    }

    void UserManager::removeUser(const Json::Value &value) {
        const std::lock_guard<std::mutex> lock(this->_mutex);
        std::erase_if(this->_users, [&](const std::unique_ptr<IUser> &user) {
            return user->isThisUser(value);
        });
    }

    std::mutex &UserManager::getMutex() {
        return this->_mutex;
    }

    void UserManager::update() {
        for (std::unique_ptr<IUser> &user : this->_users) {
            user->updateEvent();
            user->update();
            user->updateObjectManager();
        }
    }

    std::map<boost::asio::ip::udp::endpoint, Json::Value> UserManager::getPacketToSend() {
        std::map<boost::asio::ip::udp::endpoint, Json::Value> packets;

        for (std::unique_ptr<IUser> &user : this->_users) {
            auto userPackets = user->getPacketToSend();
            for (const auto &userPacket : userPackets) {
                packets[user->getEndPoint()] = userPacket;
            }
        }
        return packets;
    }
}