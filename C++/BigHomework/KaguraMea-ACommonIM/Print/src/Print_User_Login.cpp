#include "Print_User_Login.h"
#include "Print_Basic.h"
#include "head.h"
#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)
using namespace std;

int login::User_LogIn(bool p, int dep) {
    if (p) printf("\033[2J\n");
    char success[10000] = "";

    // success
    // 0:success;
    // 1:no user;
    // 2:too long;
    // 3:too short;
    // 4:wrong;
    // 5:exit;

    if (dep <= 1) {
        cout << "请输入用户名(6-100个字符):" << flush;
        read(sock, success, 1);
        if (strcmp(success, "1") == 0) {
            printf("\033[2J\n");
            cout << "用户不存在!\n";
            return User_LogIn(false, 1);
        } else if (strcmp(success, "2") == 0) {
            printf("\033[2J\n");
            cout << "用户名过长!\n";
            return User_LogIn(false, 1);
        } else if (strcmp(success, "3") == 0) {
            printf("\033[2J\n");
            cout << "用户名过短!\n";
            return User_LogIn(false, 1);
        } else if (strcmp(success, "4") == 0) {
            return 1;
        }
    }

    if (dep <= 1) printf("\033[2J\n");
    for (int i = 0; i < sizeof(success); i++)
        success[i] = '\0';
    cout << "\n请输入密码(6-20个字符):" << flush;
    read(sock, success, 1);
    if (strcmp(success, "2") == 0) {
        printf("\033[2J\n");
        cout << "密码过长!\n";
        return User_LogIn(false, 2);
    } else if (strcmp(success, "3") == 0) {
        printf("\033[2J\n");
        cout << "密码过短!\n";
        return User_LogIn(false, 2);
    } else if (strcmp(success, "4") == 0) {
        printf("\033[2J\n");
        cout << "密码错误!\n";
        return User_LogIn(false, 2);
    } else if (strcmp(success, "5") == 0) {
        return 1;
    }
    char tmpusername[101] = "";
    read(sock, tmpusername, sizeof(tmpusername));
    username = tmpusername;
    return 0;
}
