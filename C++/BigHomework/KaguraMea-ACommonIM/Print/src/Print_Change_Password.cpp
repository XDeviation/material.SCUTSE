#include "Print_Basic.h"
#include "Print_Manager.h"
#include "Print_User_Login.h"
#include "Print_User_Registered.h"
#include "head.h"
#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)
using namespace std;
using namespace rapidjson;

int client_print_manager::change_password(bool p) {
    if (p) printf("\033[2J\n");
    char success[101] = "";
    for (int i = 0; i < sizeof(success); i++)
        success[i] = '\0';
    cout << "请输入密码(6-20个字符):" << flush;
    read(sock, success, 1);
    if (strcmp(success, "2") == 0) {
        printf("\033[2J\n");
        cout << "密码过长!\n";
        return change_password(false);
    } else if (strcmp(success, "3") == 0) {
        printf("\033[2J\n");
        cout << "密码过短!\n";
        return change_password(false);
    } else if (strcmp(success, "5") == 0) {
        return 1;
    } else
        return 0;
}
