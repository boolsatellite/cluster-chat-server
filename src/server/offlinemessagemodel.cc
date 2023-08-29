//
// Created by satellite on 2023-08-29.
//
#include "offlinemessagemodel.h"
#include "db.h"


void offlineMsgModel::insert(int userid, std::string msg) {
    char sql[1024];
    sprintf(sql , "insert into OfflineMessage values(%d,'%s')",userid,msg.c_str());
    MySQL mysql;
    if(  mysql.connect() ) {
         mysql.update(sql);
    }
}

void offlineMsgModel::remove(int userid) {
    char sql[1024];
    sprintf(sql , "delete from OfflineMessage where userid=%d",userid);
    MySQL mysql;
    if(  mysql.connect() ) {
        mysql.update(sql);
    }
}

std::vector<std::string> offlineMsgModel::query(int userid) {
    char sql[1024];
    std::vector<std::string> vec;
    sprintf(sql , "select message from OfflineMessage where userid=%d",userid);
    MySQL mysql;
    if(  mysql.connect() ) {
        MYSQL_RES *res = mysql.query(sql);
        if(res != nullptr) {
            MYSQL_ROW row;
            while( (row = mysql_fetch_row(res))) {
                vec.emplace_back(row[0]);
            }
            mysql_free_result(res);
            return vec;
        }
    }
    return vec;
}
