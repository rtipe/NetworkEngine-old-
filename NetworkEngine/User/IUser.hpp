//
// Created by youba on 01/10/2023.
//

#pragma once

#include <json/value.h>
#include <boost/asio/ip/udp.hpp>
#include <list>
#include "Event/sendEventManager.hpp"

namespace UnitiNetEngine {
    class ObjectManager;
    class IUser {
        public:
            virtual ~IUser() = default;
            virtual const Json::Value &getUserInfo() const = 0;
            virtual void update() = 0;
            virtual void updateObjectManager() = 0;
            virtual void start() = 0;
            virtual void end() = 0;
            virtual bool isThisUser(const Json::Value &user) const = 0;
            virtual sendEventManager &getSendEvent() = 0;
            virtual ObjectManager &getObjectManager() = 0;
            virtual boost::asio::ip::udp::endpoint &getEndPoint() = 0;
            virtual int getWaitedIdPacket() const = 0;
            // TODO : Ajouter le packet seulement si il n'est pas dans la liste des packets à traiter et qu'il n'est pas dans la liste
            // des packets traité
            virtual void addPacket(const Json::Value &packet) = 0;
            // TODO : executer chaque event disponible dans la liste des packets a traité et incrementer le waitedId, si l'event qui doit être executé
            // ne suit pas le waitedId, attendre jusqu'à qu'on le reçoit
            virtual void updateEvent() = 0;
            virtual void checkSentPacket(const Json::Value &sended) = 0;// TODO : si il s'est pas envoyé l'envoyer à partir de cette fonction
            virtual std::vector<Json::Value> getPacketToSend() = 0;
    };
}
