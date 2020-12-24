#include "Print_Manager.h"
#include "Print_Basic.h"
#include "Print_User_Login.h"
#include "Print_User_Registered.h"
#include "head.h"
using namespace std;
using namespace rapidjson;

bool client_print_manager::Link_Start() {
    // make socket
    char host[100] = {0};
    sock = socket(AF_INET, SOCK_STREAM, 0);
    // send request
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;                     // IPv4
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP address
    serv_addr.sin_port = htons(10086);                  // port

    connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    read(sock, buffer, sizeof(buffer));
    if (buffer[0] == 'T') return true;
    return false;
}

void client_print_manager::welcome(bool p) {
    if (p) printf("\033[2J\n");
    cout << "欢迎使用即时通讯软件 KaguraMea\n";
    cout << "当前版本" << version << endl;
    cout << "1、新用户注册\n";
    cout << "2、用户登录\n";
}

void client_print_manager::welcome2(bool p) {
    if (p) printf("\033[2J\n");
    cout << "欢迎使用即时通讯软件 KaguraMea\n";
    cout << "当前版本" << version << endl;
    cout << "用户" << username << "已登录" << endl;
    cout << "2、加入聊天\n";
    cout << "5、修改密码\n";
    cout << "请输入功能对应的数字进行功能选择，如需退出，请输入exit\n";
}

void client_print_manager::work() {
    while (!Link_Start()) {
        printf("\033[2J\n");
        cout << "连接本地输入客户端中" << flush;
        for (int j = 1; j <= 100000000; j++)
            j == j;
        for (int i = 1; i <= 10; i++) {
            cout << '.' << flush;
            for (int j = 1; j <= 20000000; j++)
                i = i;
        }
        cout << endl;
        cout << "连接本地输入客户端失败\n请确认已打开Mea_Read_"
                "001\n输入exit退出，或输入其他任意字符重新连接\n";
        string s;
        cin >> s;
        if (s == "exit") return;
    }
    printf("\033[2J\n");
    cout << "连接本地输入客户端中" << flush;
    for (int j = 1; j <= 10000000; j++)
        j == j;
    for (int i = 1; i <= 10; i++) {
        cout << '.' << flush;
        for (int j = 1; j <= 20000000; j++)
            ;
    }
    cout << "连接成功！\n" << flush;
    welcome(false);

    // read
    while (true) {
        read(sock, buffer, sizeof(buffer));
        if (strcmp(buffer, Exit) == 0) break;
        if (strcmp(buffer, "1") == 0) {
            int success = User_Registered(true, 0);
            printf("\033[2J\n");
            if (success == 0) {
                cout << "注册成功\n";
                welcome(false);
            } else if (success == 1) {
                cout << "注册失败\n";
                welcome(false);
            }
        } else if (strcmp(buffer, "2") == 0) {
            if (User_LogIn(true, 0) == 0) {
                welcome2(true);
                break;
            } else
                welcome(true);
        } else {
            printf("\033[2J\n");
            cout << "命令不存在，请重新输入\n";
            welcome(false);
        }
    }

    while (true) {
        read(sock, buffer, sizeof(buffer));
        if (strcmp(buffer, Exit) == 0) break;
        if (strcmp(buffer, "2") == 0) {
            chating();
            welcome2(true);
        } else if (strcmp(buffer, "5") == 0) {
            if (change_password(true) == 0) {
                printf("\033[2J\n");
                cout << "修改成功\n";
                welcome2(false);
            } else {
                printf("\033[2J\n");
                cout << "修改失败\n";
                welcome2(false);
            }
        } else {
            printf("\033[2J\n");
            cout << "命令不存在，请重新输入\n";
            welcome2(false);
        }
    }

    // close socket
    close(sock);
    return;
}