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
    LOG_INFO << "CherService::log" <<__FILE__ << ":" << __LINE__;
    int id = js["id"].get<int>();
    std::string pwd = js["password"];

    User user = userModel_.query(id);
    if(user.getpassword() == pwd && user.getid() != -1) {       //密码正确且用户存在
        if( user.getstate() == "online") {                      //用户已经登录
            json response;
            response["msgid"] = LOG_MAG_ACK;
            response["errno"] = 2;
            response["errmsg"] = "该账号已经登录";
            conn->send(response.dump());
        }
        else {                                                 //用户没有登录则完成登录操作
            //登录成功刷新状态信息
            user.setstate("online");
            userModel_.updateState(user);

            //将用户连接记录
            {
                std::lock_guard<std::mutex> lock(mtx_);
                userConnMap_.insert({user.getid(), conn});
            }
            json response;
            response["msgid"] = LOG_MAG_ACK;
            response["errno"] = 0;
            response["id"] = user.getid();
            response["name"] = user.getname();
            conn->send(response.dump());
        }
    }
    else {                                                     //登录失败
        json response;
        response["msgid"] = LOG_MAG_ACK;
        response["errno"] = 1;
        response["errmsg"] = "用户名密码错误";
        conn->send(response.dump());

    }
}

void ChatService::reg(const muduo::net::TcpConnectionPtr &conn, json &js, muduo::Timestamp) {
    LOG_INFO << "ChatService::reg" << __FILE__ << ":" <<__LINE__;
    std::string name = js["name"];
    std::string pwd = js["password"];
    User user;
    user.setname(name);
    user.setpassword(pwd);
    bool state = userModel_.insert(user);
    if(state) {    //注册成功
        json response;
        response["msgid"] = REG_MSG_ACK;
        response["id"] = user.getid();
        response["errno"] = 0;
        conn->send(response.dump());   //向对端发送序列化json
    }
    else {         //注册失败
        json response;
        response["msgid"] = REG_MSG_ACK;
        response["id"] = user.getid();
        response["errno"] = 1;           //标识注册失败
        conn->send(response.dump());   //向对端发送序列化json
    }
}

ChatService::ChatService() {
    msgHandlerMap_.insert({LOGIN_MSG, std::bind(&ChatService::login, this, std::placeholders::_1, std::placeholders::_2,
                                                std::placeholders::_3)});
    msgHandlerMap_.insert({REG_MSG, std::bind(&ChatService::reg, this, std::placeholders::_1, std::placeholders::_2,
                                              std::placeholders::_3)});
}

ChatService::MsgHandler ChatService::getHandler(int msgid) {
    auto it = msgHandlerMap_.find(msgid);
    if (it == msgHandlerMap_.end()) {
        return [&](const muduo::net::TcpConnectionPtr &conn, json &js, muduo::Timestamp) {
            LOG_ERROR << "msgid:" << msgid << "can not find handler";
        };
    } else {
        return msgHandlerMap_[msgid];
    }
}

void ChatService::clientCloseException(const muduo::net::TcpConnectionPtr &conn) {
    LOG_ERROR << "ChatService::clientCloseException" << __FILE__ << ":" <<__LINE__;
    User user{};
    std::lock_guard<std::mutex> lock(mtx_); {
        for (auto it = userConnMap_.begin(); it != userConnMap_.end(); ++it) {
            if (it->second == conn) {
                user.setid(it->first);
                userConnMap_.erase(it);         //从map表中删除对应 id conn
                break;
            }
        }
    }
    if(user.getid() != -1) {                        //防止新建连接未登录就异常退出情况
        user.setstate("offline");                   //更新状态
        userModel_.updateState(user);
    }
}
