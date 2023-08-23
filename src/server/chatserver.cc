//
// Created by satellite on 2023-08-21.
//

#include "chatserver.h"
#include "string"
#include "functional"
#include "json.hpp"
#include "chatservice.h"
using namespace nlohmann;

ChatServer::ChatServer(EventLoop *loop, const InetAddress addr, const string &nameArg)
    : server_(loop , addr , nameArg)
    , loop_(loop)
{
    server_.setConnectionCallback(std::bind(&ChatServer::onConnection,this,std::placeholders::_1));

    server_.setMessageCallback((std::bind(&ChatServer::onMessage,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3)));

    server_.setThreadNum(4);


}

void ChatServer::start() {
    server_.start();
}

void ChatServer::onConnection(const TcpConnectionPtr &conn) {
    if(!conn->connected()) {              //用户断开连接
        conn->shutdown();
    }
}

void ChatServer::onMessage(const TcpConnectionPtr &conn, Buffer *buffer, Timestamp time) {
    std::string buf = buffer->retrieveAllAsString();
    json js = json::parse(buf);
    //通过js["msgid"]获取对应业务注册的回调函数
    auto msgHandler = ChatService::instance()->getHandler(js["msgid"].get<int>());
    msgHandler(conn , js , time);
}

