//
// Created by satellite on 2023-08-25.
//

#ifndef CHAT_USER_H
#define CHAT_USER_H

#include <string>

//user表的ORM类
class User {
public:
    User(int id=-1, std::string name="", std::string Pwd="", std::string state="offline") {
        this->id = id;
        this->name = name;
        this->password = Pwd;
        this->state = state;
    }

    void setid(int id) { this->id = id; }

    void setname(std::string name) { this->name = name; }

    void setpassword(std::string password) { this->password = password; }

    void setstate(std::string state) { this->state = state; }

    int getid() { return id; }

    std::string getname() { return name; }

    std::string getpassword() { return password; }

    std::string getstate() { return state; }

private:
    int id;
    std::string name;
    std::string password;
    std::string state;
};


#endif //CHAT_USER_H
