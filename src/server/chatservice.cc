//
// Created by satellite on 2023-08-23.
//

#include "chatservice.h"
#include "public.h"
#include "muduo/base/Logging.h"


ChatService *ChatService::instance() {
    static ChatService service;
    return &service;
}

void ChatService::login(const muduo::net::TcpConnectionPtr &conn, json &js, muduo::Timestamp) {
    LOG_INFO << "do login service";

}

void ChatService::reg(const muduo::net::TcpConnectionPtr &conn, json &js, muduo::Timestamp) {
    LOG_INFO << "do reg service";
}

ChatService::ChatService() {
    msgHandlerMap.insert({LOGIN_MSG, std::bind(&ChatService::login, this, std::placeholders::_1, std::placeholders::_2,
                                               std::placeholders::_3)});
    msgHandlerMap.insert({REG_MSG, std::bind(&ChatService::reg, this, std::placeholders::_1, std::placeholders::_2,
                                             std::placeholders::_3)});
}

ChatService::MsgHandler ChatService::getHandler(int msgid) {
    auto it = msgHandlerMap.find(msgid);
    if (it == msgHandlerMap.end()) {
        return [&](const muduo::net::TcpConnectionPtr &conn, json &js, muduo::Timestamp) {
            LOG_ERROR << "msgid:" << msgid << "can not find handler";
        };
    } else {
        return msgHandlerMap[msgid];
    }
}

