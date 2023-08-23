//
// Created by satellite on 2023-08-22.
//
#include "chatserver.h"
#include "iostream"


int main() {
     muduo::net::EventLoop loop;
     muduo::net::InetAddress addr("127,0.0.1",8000);
     ChatServer server(&loop , addr , "Chatserver");

     server.start();
     loop.loop();
}