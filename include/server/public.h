//
// Created by satellite on 2023-08-23.
//

#ifndef CHAT_PUBLIC_H
#define CHAT_PUBLIC_H

//server和client的公共文件

enum EnMsgType {
    LOGIN_MSG = 1,     //登录消息
    LOG_MAG_ACK  ,
    REG_MSG      ,       //注册消息
    REG_MSG_ACK        //注册响应消息
};


#endif //CHAT_PUBLIC_H
