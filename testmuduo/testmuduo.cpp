//
// Created by satellite on 2023-08-20.
//
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <functional>
#include <iostream>
#include <string>

class ChatServer {
public:

/*
        TcpServer(EventLoop* loop,
        const InetAddress& listenAddr,
        const string& nameArg,
        Option option = kNoReusePort);
*/
    ChatServer(
            muduo::net::EventLoop *loop,                      //事件循环
            const muduo::net::InetAddress &listenAddr,        //服务器ip + port
            const std::string &nameArg)                       //服务器名称
            : server_(loop, listenAddr, nameArg), loop_(loop) {
        //注册用户连接回调
        server_.setConnectionCallback(std::bind(&ChatServer::onConnection, this, std::placeholders::_1));
        //注册读写回调
        server_.setMessageCallback(std::bind(&ChatServer::onMessage, this, std::placeholders::_1, std::placeholders::_2,
                                             std::placeholders::_3));
        //设置服务器的线程数量
        server_.setThreadNum(4);
    }

    void start() {          //开启事件循环
        server_.start();
    }

private:
    muduo::net::TcpServer server_;   //
    muduo::net::EventLoop *loop_;    //

    void onConnection(const muduo::net::TcpConnectionPtr &conn) {
        if (conn->connected()) {
            std::cout << conn->peerAddress().toIpPort() << "state : online" << std::endl;
        } else {
            std::cout << "state not connect";
            conn->shutdown();
        }
    }

/*
    typedef std::function<void (const TcpConnectionPtr&,
                                Buffer*,
                                Timestamp)> MessageCallback;
*/
    void onMessage(const muduo::net::TcpConnectionPtr & conn,          //连接
                   muduo::net::Buffer * buffer,                          //缓冲区
                   muduo::Timestamp time) {                           //超时信息
        std::string buf = buffer->retrieveAllAsString();
        std::cout << "recv data" << buf << " time : " << time.toString() <<std::endl;
    }
};

int main()
{
    muduo::net::EventLoop loop;
    muduo::net::InetAddress addr("127.0.0.1" , 8000);
    ChatServer chatServer(&loop,addr,"ChatServer");
    chatServer.start();
    loop.loop();
}

