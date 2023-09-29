# cluster-chat-server

## 编码中的记录

### 业务和网络的分离

```c++
chatserver.cc
void ChatServer::onMessage(const TcpConnectionPtr &conn, Buffer *buffer, Timestamp time) {
    std::string buf = buffer->retrieveAllAsString();
    json js = json::parse(buf);
}
```

这里将从网络中接收的json字符串发序列化存放在```json```对象中，之后要处理json中的东西，也就是业务层面的代码，我们当然不希望网络层和业务层的代码杂糅在一起，便想办法进行分离，实现解耦合的方法一般有两种，**1. 利用抽象类 2. 利用回调函数**

这里采用回调函数来解决，引入处理业务类```ChatService```，类中存储了key消息类型(消息id号int)value对应回调函数(functional对象)，```ChatService```在构造函数中完成各类消息的注册，并对外提供接口```ChatService::MsgHandler ChatService::getHandler(int msgid)```查询消息id对应的回调函数，从而实现业务代码与网络代码分离

### 数库操作和业务的分离，及数据库之间的分离

```c++
void ChatService::reg(const muduo::net::TcpConnectionPtr &conn, json &js, muduo::Timestamp) {
    std::string name = js["name"]; 
    std::string pwd = js["password"];
    User user;
    user.setname(name);
    user.setpassword(pwd);
    bool state = userModel.insert(user);
```

这里将数据库的每个表单独作为一个类，只提供相应的成员和```get set```方法，而将用于数据库操作的类为```UserModel```提供了以User为形参的数据库操作函数```bool insert(User user);```，这样可以在更换数据库时只修改```UserModel```类，```ChatService```类中存在私有成员```UserModel userModel;  //用于执行user表的操作```，这样就可以通过```userModel```对象提供的方法操作数据库，达到了业务与数据库操作分离

### json的操作

```c++
            std::vector<User> userVec = friendModel_.query(user.getid());
            if(!userVec.empty()) {
                std::vector<std::string> vec2;
                for(auto & i : userVec) {
                    json json1;
                    json1["id"] = user.getid();
                    json1["name"] = user.getname();
                    json1["state"] = user.getstate();
                    vec2.push_back(json1.dump());
                }
                response["friend"] = vec2;
            }
```

通过数据库查询将User对象存放到vector容器中，用于User是自定义类型故无法执行```response["friend"] = userVec```，退而求其次将每个```User```对象转化成对应```json```以数组的方式存储，那么是不是可以为每个对象提供到对呀json的转化这样就实现了通过字符串进行对象之间的传递，在网络环境中格外好用



 









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
CREATE TABLE OfflineMessage (
    userid INT NOT NULL,
    message VARCHAR(500) NOT NULL
);
````

折腾了3天mysql：https://blog.csdn.net/weixin_45086957/article/details/124805201 感谢这篇博客
