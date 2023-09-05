//
// Created by satellite on 2023-09-05.
//

#ifndef CHAT_GROUPUSER_H
#define CHAT_GROUPUSER_H

#include "user.h"

class GroupUser : public User {
public:
    void setRole(std::string role) { this->role = role; }
    std::string getRole() { return this->role; }
private:
    std::string role;
};

#endif //CHAT_GROUPUSER_H
