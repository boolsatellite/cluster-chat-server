# cluster-chat-server
## json for modern c++的使用

### json的序列化

```c++
std::string func1() {
    json js;
    js["meg_type"] = 2;
    js["from"] = "zhang san";
    js["to"] = "li si";
    js["msg"] = "hello ,what are you doing now ?";
    std::cout << js << std::endl;       //json对象中重载了 << 用于输出序列化的字符串
    //{"from":"zhang san","meg_type":2,"msg":"hello ,what are you doing now ?","to":"li si"}

    std::string sendBuf = js.dump();  //将json中的数据序列化后返回对应的字符串对象
    std::cout << sendBuf.c_str() << std::endl;
    //{"from":"zhang san","meg_type":2,"msg":"hello ,what are you doing now ?","to":"li si"}
    return sendBuf;
}

std::string func2() {
    json js;
    js["id"] = {1, 2, 3, 4, 5};
    js["name"] = "zhangsan";
    js["msg"]["zhangsan"] = "helloworld";
    js["msg"]["liu shuo"] = "hello china";
    js["msg"] = {{"zhansan", "hello world"},
                 {"liushuo", "hello china"}};
    std::cout << js << std::endl;
    //{"id":[1,2,3,4,5],"msg":{"liushuo":"hello china","zhansan":"hello world"},"name":"zhangsan"}
    return js.dump();
}

std::string func3() {
    json js;
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    js["list"] = vec;

    std::map<int, std::string> m;
    m.insert({1, "黄山"});
    m.insert({2, "华山"});
    m.insert({3, "泰山"});
    js["path"] = m;
    std::cout << js << std::endl;
    //{"list":[1,2,3],"path":[[1,"黄山"],[2,"华山"],[3,"泰山"]]}
    return  js.dump();
}
```

### json的反序列化

```c++
int main() {
    std::string recvBuf = func1();
    json js = json::parse(recvBuf);
    std::cout << js["from"] << std::endl << js["to"] << std::endl << js["msg"] << std::endl;
    //"zhang san"
    //"li si"
    //"hello ,what are you doing now ?"
}

int main() {
    std::string recvBuf = func2();
    json jsbuf = json::parse(recvBuf);
    std::cout <<jsbuf["id"] << std::endl;    // [1,2,3,4,5]
    auto arr = jsbuf["id"];
    std::cout <<arr[2] << std::endl;         // 3

    std::cout <<jsbuf["msg"] << std::endl;        //{"liushuo":"hello china","zhansan":"hello world"}
    auto  msgjs = jsbuf["msg"];
    std::cout << msgjs["zhansan"] << std::endl;   // "hello world"
    std::cout <<msgjs["liushuo"] <<std::endl;     // "hello china"
}

int main() {
    std::string recvBuf = func3();
    json jsbuf = json::parse(recvBuf);

    std::vector<int> vec = jsbuf["list"];
    for ( auto & i : vec)
        std::cout << i <<" ";    //1 2 3 
    std::cout <<std::endl;

    std::map<int ,std::string> map = jsbuf["path"];
    for ( auto & i : map)
        std::cout << i.first <<":" << i.second <<"  ";  //1:黄山  2:华山  3:泰山  
    std::cout <<std::endl;

}
```

## 数据库建表

User表
```sql
CREATE TABLE User (
    id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(50) NOT NULL UNIQUE,
    password VARCHAR(50) NOT NULL,
    state ENUM('online', 'offline') DEFAULT 'offline'
);
```

Friend表

```sql
CREATE TABLE Friend (
    userid INT NOT NULL,
    friendid INT NOT NULL,
    PRIMARY KEY (userid, friendid)
);
```

AllGroup表

```sql
CREATE TABLE AllGroup (
    id INT PRIMARY KEY AUTO_INCREMENT,
    groupname VARCHAR(50) NOT NULL UNIQUE,
    groupdesc VARCHAR(200) DEFAULT ''
);
```

GroupUser表

```sql
CREATE TABLE GroupUser (
    groupid INT NOT NULL,
    userid INT NOT NULL,
    grouprole ENUM('creator', 'normal') DEFAULT 'normal',
    PRIMARY KEY (groupid, userid)
);
```

OfflineMessage表

````sql
CREATE TABLE offline_messages (
    userid INT NOT NULL,
    message VARCHAR(500) NOT NULL
);
````

