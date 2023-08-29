//
// Created by satellite on 2023-08-23.
//

#ifndef CHAT_CHATSERVICE_H
#define CHAT_CHATSERVICE_H

#include "muduo/net/TcpConnection.h"
#include "json.hpp"
#include "unordered_map"
#include "functional"
#include "usermodel.h"
#include "offlinemessagemodel.h"
#include "thread"
#include "mutex"

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
    //异常退出处理
    void clientCloseException(const muduo::net::TcpConnectionPtr& conn);
    //一对一聊天业务
    void oneChat(const muduo::net::TcpConnectionPtr& conn , json& js , muduo::Timestamp);

    //获取消息对应的处理器
    MsgHandler getHandler(int msgid);
private:


    ChatService();   //单例模式

    //存放消息id和对应的业务处理方法
    std::unordered_map<int , MsgHandler> msgHandlerMap_;

    // 聊天服务器当有消息时要向用户推送消息，故必须保存在线用户的连接信息
    std::unordered_map<int , muduo::net::TcpConnectionPtr> userConnMap_;

    //用于执行user表的操作
    UserModel userModel_;

    //用于处理离线消息
    offlineMsgModel offlineMsgModel_;

    //互斥锁保证userConMap_的线程安全，msgHandlerMap_在构造时就已经初始化且不在改变故不需要线程安全处理
    std::mutex mtx_;
};



#endif //CHAT_CHATSERVICE_H
