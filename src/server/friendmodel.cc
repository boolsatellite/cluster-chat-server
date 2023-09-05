//
// Created by satellite on 2023-09-03.
//
#include "friendmodel.h"
#include "db.h"

void FriendModel::insert(int userid, int friendid) {
    char sql[1024];
    sprintf(sql , "insert into Friend values(%d,%d)",userid,friendid);
    MySQL mysql;
    if( mysql.connect() ) {
        mysql.update(sql);
    }

}

std::vector<User> FriendModel::query(int userid) {
    char sql[1024];
    sprintf(sql , "select a.id , a.name , a.state from User a inner join Friend b on b.friendid = a.id where b.userid=%d ",userid);
    MySQL mysql;
    if( mysql.connect() ) {
        MYSQL_RES* res = mysql.query(sql);
        if( res != nullptr) {
            MYSQL_ROW row;
            std::vector<User> vec;
            while( (row = mysql_fetch_row(res))) {
                User user;
                user.setid(atoi(row[0]));
                user.setname(row[1]);
                user.setstate(row[2]);
                vec.emplace_back(user);
            }
            return vec;
        }
    }
    return {};
}

