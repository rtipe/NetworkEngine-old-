//
// Created by youba on 04/10/2023.
//

#include <iostream>
#include "AUser.hpp"
#include "Uniti.hpp"

namespace UnitiNetEngine {
    AUser::AUser(const Json::Value &value, const boost::asio::ip::udp::endpoint &endpoint):
    _objectManager(Uniti::getInstance().getProjectInfo().privateScene) {
        this->_data = value;
        this->_endpoint = endpoint;
    }

    void AUser::updateObjectManager() {
        this->_objectManager.update();
    }

    sendEventManager &AUser::getSendEvent() {
        return this->_sendEventManager;
    }

    ObjectManager &AUser::getObjectManager() {
        return this->_objectManager;
    }

    boost::asio::ip::udp::endpoint &AUser::getEndPoint() {
        return this->_endpoint;
    }

    int AUser::getWaitedIdPacket() const {
        return this->_waitedId;
    }

    void AUser::addPacket(const Json::Value &packet) {
        int id = packet.get("id", -1).asInt();

        if (id == -1) return;
        auto itToHandle = std::find_if(this->_packetToHandle.begin(), this->_packetToHandle.end(),
        [&](const auto &value) {
            int otherId = value.get("id", -1).asInt();
            return id == otherId;
        });
        if (itToHandle != this->_packetToHandle.end()) return;
        auto itHandled = std::find(this->_packetHandled.begin(), this->_packetHandled.end(), id);
        if (itHandled != this->_packetHandled.end()) return;
        const std::lock_guard<std::mutex> lock(this->_mutex);
        this->_packetToHandle.push_back(packet);
    }

    void AUser::updateEvent() {
        std::unique_lock<std::mutex> lock(this->_mutex);
        int nextId = (this->_waitedId + 1 >= 100) ? 0 : this->_waitedId + 1;

        auto itToHandle = std::find_if(this->_packetToHandle.begin(), this->_packetToHandle.end(),
        [&](const auto &value) {
            int id = value.get("id", -1).asInt();
            return nextId == id;
        });
        if (itToHandle == this->_packetToHandle.end()) return;
        Json::Value events = itToHandle.operator*()["events"];

        if (!events.isNull()) {
            for (const auto &event : events) {
                const std::string &name = event.get("name", "undefined").asString();
                lock.unlock();
                Uniti::getInstance().getEventManager().emitEvent(name, *this, event);
                lock.lock();
            }
        }
        if (this->_packetHandled.size() > 16)
            this->_packetHandled.pop_front();
        this->_packetHandled.push_back(nextId);
        this->_packetToHandle.erase(itToHandle);
        this->_waitedId = nextId;
        lock.unlock();
        this->updateEvent();
    }

    void AUser::checkSentPacket(const Json::Value &sent) {
        const std::lock_guard<std::mutex> lock(this->_mutex);
        std::erase_if(this->_sentPacket,
        [&] (auto &packet) {
            Json::Value info = std::get<0>(packet);
            int id = info.get("id", -1).asInt();
            return std::any_of(sent.begin(), sent.end(), [&] (const auto &sentId) { return sentId.asInt() == id; });
        });
        for (auto &packet : this->_sentPacket) {
            if (std::get<1>(packet) > 0)
                std::get<1>(packet) = std::get<1>(packet) - 1;
            else
                this->_packetToSend.push_back(std::get<0>(packet));
        }
        std::erase_if(this->_sentPacket,
        [&] (auto &packet) {
            return std::get<1>(packet) <= 0;
        });
    }

    std::vector<Json::Value> AUser::getPacketToSend() {
        std::vector<Json::Value> packets;

        packets.insert(packets.end(), this->_packetToSend.begin(), this->_packetToSend.end());
        packets.push_back(createPacket());
        this->_packetToSend.clear();
        return packets;
    }

    Json::Value AUser::createPacket() {
        const std::lock_guard<std::mutex> lock(this->_mutex);
        Json::Value packet;
        Json::Value events;
        Json::Value received;
        Json::Value id = this->_sendId;
        int i = 0;

        this->_sendId = (this->_sendId + 1 < 100) ? this->_sendId + 1 : 0;
        for (const auto &eventRow : this->_sendEventManager.getEvents()) {
            Json::Value event;
            event["name"] = eventRow.first;
            event["data"] = eventRow.second;
            events.insert(i, event);
            i++;
        }
        for (const auto &eventRow : Uniti::getInstance().getObjectManager().getSendEvent().getEvents()) {
            Json::Value event;
            event["name"] = eventRow.first;
            event["data"] = eventRow.second;
            events.insert(i, event);
            i++;
        }
        i = 0;
        for (const auto &idPacket : this->_receivedPacket) {
            received.insert(i, idPacket);
            i++;
        }
        this->_receivedPacket.clear();
        this->_sendEventManager.clear();
        packet["events"] = events;
        packet["received"] = received;
        packet["id"] = id;
        return packet;
    }

    std::mutex &AUser::getMutex() {
        return this->_mutex;
    }
}