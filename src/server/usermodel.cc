//
// Created by satellite on 2023-08-25.
//

#include "iostream"
#include "usermodel.h"
#include "db.h"

bool UserModel::insert(User user) {
    char sql[1024];
    std::sprintf(sql , "insert into User (name , password , state) values('%s','%s','%s')" ,
                    user.getname().c_str() , user.getpassword().c_str() , user.getstate().c_str() );
    MySQL mysql;
    if( mysql.connect() ) {
        if ( mysql.update(sql) ) {
            user.setid(mysql_insert_id(mysql.getConn()));
            return true;
        }
    }
    return false;
}

User UserModel::query(int id) {
     char sql[1024];
     std::sprintf(sql , "select * from User where id = %d",id);
     MySQL mysql;
     if( mysql.connect() ) {
         MYSQL_RES* res = mysql.query(sql);
         if (res != nullptr) {  //查询成功
             MYSQL_ROW row = mysql_fetch_row(res);
             if( row != nullptr ) {
                 User user;
                 user.setid(atoi(row[0]));
                 user.setname(row[1]);
                 user.setpassword(row[2]);
                 user.setstate(row[3]);
                 mysql_free_result(res);       //释放MYSQL_RES的资源
                 return user;
             }
         }
     }
    return {};
}

bool UserModel::updateState(User user) {
    char sql[1024];
    std::sprintf(sql , "update User set state='%s' where id=%d",user.getstate().c_str(),user.getid() );
    MySQL mysql;
    if( mysql.connect() ) {
        if ( mysql.update(sql) ) {
            return true;
        }
    }
    return false;
}

