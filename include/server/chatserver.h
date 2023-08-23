//
// Created by satellite on 2023-08-21.
//

#ifndef CLUSTER_CHAT_SERVER_CHATSERVER_H
#define CLUSTER_CHAT_SERVER_CHATSERVER_H

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>

using namespace muduo;
using namespace muduo::net;

//网络模块代码
class ChatServer {
public:
    ChatServer(EventLoop* loop ,        //初始化聊天服务器对象
               const InetAddress addr,
               const std::string& nameArg);

    void start();                       //启动服务


private:

    void onConnection(const TcpConnectionPtr&);    //有新连接的回调函数


    void onMessage(const TcpConnectionPtr&,        //读写事件的回调函数
                   Buffer*,
                   Timestamp);

    muduo::net::TcpServer server_;                  //服务器对象
    muduo::net::EventLoop* loop_;                   //事件循环
};


#endif //CLUSTER_CHAT_SERVER_CHATSERVER_H
