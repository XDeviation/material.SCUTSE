#include "Print_User_Registered.h"
#include "Print_Basic.h"
#include "head.h"
#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)
using namespace std;

int registered::User_Registered(bool p, int dep) {
    if (p) printf("\033[2J\n");
    cout << "请输入用户名(6-100个字符):" << flush;
    char success[10000] = "";
    if (dep <= 1) {
        read(sock, success, 1);

        // success
        // 0:success;
        // 1:be used;
        // 2:too long;
        // 3:too short;
        // 4:wrong;
        // 5:exit

        if (strcmp(success, "1") == 0) {
            printf("\033[2J\n");
            cout << "用户名已被使用!\n";
            return User_Registered(false, 1);
        } else if (strcmp(success, "2") == 0) {
            printf("\033[2J\n");
            cout << "用户名过长!\n";
            return User_Registered(false, 1);
        } else if (strcmp(success, "3") == 0) {
            printf("\033[2J\n");
            cout << "用户名过短!\n";
            return User_Registered(false, 1);
        } else if (strcmp(success, "4") == 0) {
            return 1;
        }
    }
    for (int i = 0; i < sizeof(success); i++)
        success[i] = '\0';
    cout << "\n请输入密码(6-20个字符):" << flush;
    read(sock, success, 1);
    if (strcmp(success, "2") == 0) {
        printf("\033[2J\n");
        cout << "密码过长!\n";
        return User_Registered(false, 2);
    } else if (strcmp(success, "3") == 0) {
        printf("\033[2J\n");
        cout << "密码过短!\n";
        return User_Registered(false, 2);
    } else if (strcmp(success, "5") == 0) {
        return 1;
    }

    for (int i = 0; i < sizeof(success); i++)
        success[i] = '\0';
    cout << "\n请确认密码(6-20个字符):" << flush;
    read(sock, success, 1);
    if (strcmp(success, "0") == 0) {
        printf("\033[2J\n");
        return 0;
    } else if (strcmp(success, "4") == 0) {
        printf("\033[2J\n");
        cout << "两次密码输入不一样!\n";
        return User_Registered(false, 2);
    } else if (strcmp(success, "5") == 0) {
        return 1;
    }
}
