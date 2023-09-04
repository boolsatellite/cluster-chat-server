//
// Created by satellite on 2023-09-03.
//

#ifndef CLUSTER_CHAT_SERVER_FRIENDMODEL_H
#define CLUSTER_CHAT_SERVER_FRIENDMODEL_H

#include "vector"
#include "user.h"

//维护好友信息的操作接口
class FriendModel {
public:
    //添加好友
    void insert(int userid , int friendid);
    //返回用户好友列表
    std::vector<User> query(int userid);
};


#endif //CLUSTER_CHAT_SERVER_FRIENDMODEL_H
