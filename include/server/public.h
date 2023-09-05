//
// Created by satellite on 2023-08-23.
//

#ifndef CHAT_PUBLIC_H
#define CHAT_PUBLIC_H

//server和client的公共文件

enum EnMsgType {
    LOGIN_MSG = 1,       //登录消息
    LOG_MAG_ACK  ,       //登录回响消息
    REG_MSG      ,       //注册消息
    REG_MSG_ACK  ,       //注册响应消息
    ONE_CHAT_MSG ,       //聊天消息
    ADD_FRIEND_MSG,      //添加好友
    CREAT_GROUP_MSO,     //创建群组
    ADD_GROUP_MSG,       //加入群组
    GROUP_CHAT_MSG       //群聊天
};


#endif //CHAT_PUBLIC_H


/*
 * {"msgid":3,"name":"li","password":"666"}
 *
 * {"msgid":1,"id":1,"password":"123456"}                       登录id 1
 * {"msgid":1,"id":2,"password":"666"}                          登录id 2
 *
 * {"msgid":5,"id":2,"from":"li","to":1,"msg":"hello!"}         聊天消息，2->1 hello!
 * {"msgid":5,"id":1,"from":"zhang","to":2,"msg":"hello!"}      聊天消息, 1->2 hello1
 *
 * {"msgid":6,"id":1,"friendid":2}
 *
 * {"msgid":7,"id":1,"name":"group1","desc":"id‘s group"}
 * {"msgid":8,"id":2,"groupid":1}
 * {"msgid":9,"id":2,"groupid":1,"msg":"testGroupMsg"}
 */