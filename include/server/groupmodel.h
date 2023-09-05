//
// Created by satellite on 2023-09-05.
//

#ifndef CHAT_GROUPMODEL_H
#define CHAT_GROUPMODEL_H

#include "group.h"

class GroupModel {
public:
    bool createGroup(Group& group);                             //创建群组
    void addGroup(int userid , int groupid , std::string role);   //加入群组
    std::vector<Group> queryGroup(int userid);                  //查询用户所在群组信息
    std::vector<int> queryGroupUser(int userid , int groupid);  //根据groupid查询群组id列表除userid自己
};

#endif //CHAT_GROUPMODEL_H
