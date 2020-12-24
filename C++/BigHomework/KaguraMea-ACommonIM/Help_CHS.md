# 如何使用KaguraMea 

## 使用前：

### Linux端：

#### 本地测试：
- 将所有文件clone到本地，并在Print、Read、Server文件夹下运行 `make` 命令
- 将Server文件夹下的 `userdata` 文件清空
- 依次运行 `Server`、`Read`、`Print` ，并在Read处输入所有指令

#### 联网运行：
- 将Server文件夹下所有文件clone到服务器，并在此文件夹下运行 `make` 命令
- 将Print、Read两个文件夹下所有文件clone到本地
- 将Read_Manager.cpp的127行的
`serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");`
语句中将IP地址(127.0.0.1)改为你的服务器的地址，并在Print、Read文件夹下运行 `make` 命令
- 将Server文件夹下的 `userdata` 文件清空
- 依次运行 `Server`、`Read`、`Print` ，并在 `Read` 处输入所有指令

---

## 使用时
- 在本页面查看所有操作
- 或者在[这里](https://github.com/XDeviation/KaguraMea-ACommonIM/wiki)查询所有支持的操作

## 帮助文档

### 登陆前 
- 输入 `1` 以注册新用户
- 你需要在注册新用户的界面依次输入用户名和密码，用户名要求长度在6-100内，密码要求长度在6-20内，服务器会自动判断该用户名是否被注册并及时返回，注册成功后你将获得一个与现有用户名相同的好友密钥，你可以通过搜索他人的好友密钥达到添加好友的目的。
- 输入 `2` 以登录现有账号
- 你需要在登录界面依次输入用户名和密码，服务器会自动判断用户是否存在以及密码是否正确。

### 登陆后
- 加入聊天会将历史的消息拉取至本地。
- 输入 `5` 以修改密码
- 修改密码没有二次验证的功能，若修改出错请到 `./Server/usrdata` 中对应的文件夹里进行重置。

### 疑难解答

#### 端口冲突
- 将Read_Main.cpp的第103行语句
`serv_addr.sin_port = htons(19198);`
中的端口(19198)改为闲置端口

- 或者将Read_Main.cpp的第121行语句
`my_addr.sin_port = htons(10086);`和Print_Main.cpp的第116行语句
`serv_addr.sin_port = htons(10086);`
中的端口(10086)改为闲置的端口