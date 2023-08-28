//
// Created by satellite on 2023-08-25.
//

#ifndef CHAT_USERMODEL_H
#define CHAT_USERMODEL_H

#include "user.h"

//User表的数据操作类
class UserModel {
public:
    bool insert(User user);
    User query(int id);
    bool updateState(User user);


};


#endif //CHAT_USERMODEL_H
