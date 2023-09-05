//
// Created by satellite on 2023-09-05.
//

#ifndef CHAT_GROUP_H
#define CHAT_GROUP_H
#include "vector"
#include "string"
#include "groupuser.h"

class Group {
public:
    Group(int id=-1 , std::string name="" , std::string desc="") {
        this->id = id;
        this->name = name;
        this->desc = desc;
    }

    void setId(int id) { this->id = id; }
    void setName(std::string name) { this->name = name; }
    void setDesc(std::string desc) { this->desc = desc; }

    int getId() { return id; }
    std::string getName() { return name; }
    std::string getDesc() { return desc; }
    std::vector<GroupUser>& getusers() { return this->users; }


private:
    int id;
    std::string name;
    std::string desc;
    std::vector<GroupUser> users;
};

#endif //CHAT_GROUP_H
