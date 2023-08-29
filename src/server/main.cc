//
// Created by satellite on 2023-08-22.
//
#include "chatserver.h"
#include "chatservice.h"
#include "iostream"
#include "signal.h"

void handler(int ) {
    ChatService::instance()->reset();
}

int main() {
    signal(SIGINT , handler);


     muduo::net::EventLoop loop;
     muduo::net::InetAddress addr("127,0.0.1",8000);
     ChatServer server(&loop , addr , "Chatserver");

     server.start();
     loop.loop();
}