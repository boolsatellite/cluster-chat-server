//
// Created by satellite on 2023-08-29.
//

#ifndef CHAT_OFFLINEMESSAGEMODEL_H
#define CHAT_OFFLINEMESSAGEMODEL_H

#include "string"
#include "vector"

class offlineMsgModel {
public:
    void insert(int userid , std::string msg);      //存储用户离线消息

    void remove(int userid);                        //删除用户离线消息

    std::vector<std::string> query(int userid);     //查询用户离线消息

private:
};



#endif //CHAT_OFFLINEMESSAGEMODEL_H
