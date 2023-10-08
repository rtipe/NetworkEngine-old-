//
// Created by youba on 04/10/2023.
//

#pragma once

#include "IUser.hpp"
#include "ObjectManager.hpp"

namespace UnitiNetEngine {
    class AUser : public IUser {
        public:
            void updateObjectManager() override;
            sendEventManager &getSendEvent() override;
            ObjectManager &getObjectManager() override;
            boost::asio::ip::udp::endpoint &getEndPoint() override;
            int getWaitedIdPacket() const override;
            void addPacket(const Json::Value &packet) override;
            void updateEvent() override;
            void checkSentPacket(const Json::Value &sent) override;
            std::vector<Json::Value> getPacketToSend() override;
        protected:
            AUser(const Json::Value &value, const boost::asio::ip::udp::endpoint &endpoint);
            Json::Value createPacket();
            Json::Value _data;
            ObjectManager _objectManager;
            sendEventManager _sendEventManager;
            boost::asio::ip::udp::endpoint _endpoint;
            std::vector<Json::Value> _packetToHandle;
            std::list<int> _packetHandled;
            std::vector<std::tuple<Json::Value, int>> _sentPacket;
            std::vector<Json::Value> _packetToSend;
            std::list<int> _receivedPacket;
            int _waitedId = 0;
            int _sendId = 0;
            std::mutex _mutex;
    };
}
