//
// Created by satellite on 2023-08-23.
//

#ifndef CHAT_CHATSERVICE_H
#define CHAT_CHATSERVICE_H

#include "muduo/net/TcpConnection.h"
#include "json.hpp"
#include "unordered_map"
#include "functional"

using namespace nlohmann;


//聊天服务器业务类
class ChatService {
public:
    using MsgHandler = std::function<void(const muduo::net::TcpConnectionPtr& conn , json& js , muduo::Timestamp)>;
    //获取单例接口
    static ChatService* instance();
    ///处理登录业务
    void login(const muduo::net::TcpConnectionPtr& conn , json& js , muduo::Timestamp);
    //处理注册业务
    void reg(const muduo::net::TcpConnectionPtr& conn , json& js , muduo::Timestamp);
    //获取消息对应的处理器
    MsgHandler getHandler(int msgid);
private:


    ChatService();   //单例模式

    //存放消息id和对应的业务处理方法
    std::unordered_map<int , MsgHandler> msgHandlerMap;

};



#endif //CHAT_CHATSERVICE_H
