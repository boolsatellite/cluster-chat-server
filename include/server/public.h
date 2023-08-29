//
// Created by satellite on 2023-08-23.
//

#ifndef CHAT_PUBLIC_H
#define CHAT_PUBLIC_H

//server和client的公共文件

enum EnMsgType {
    LOGIN_MSG = 1,       //登录消息
    LOG_MAG_ACK  ,
    REG_MSG      ,       //注册消息
    REG_MSG_ACK  ,       //注册响应消息
    ONE_CHAT_MSG         //聊天消息
};


#endif //CHAT_PUBLIC_H


/*
 * {"msgid":3,"name":"li","password":"666"}
 *
 * {"msgid":1,"id":1,"password":"123456"}
 * {"msgid":1,"id":2,"password":"666"}
 *
 * {"msgid":5,"id":2,"from":"li","to":1,"msg":"hello!"}
 * {"msgid":5,"id":1,"from":"zhang","to":2,"msg":"hello!"}
 */