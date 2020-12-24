#include "Print_Basic.h"
#include "Print_Manager.h"
#include "Print_User_Login.h"
#include "Print_User_Registered.h"
#include "head.h"
using namespace std;
using namespace rapidjson;

void client_print_manager::chating() {
    while (true) {
        char buffer[10000];
        char tmpbuffer[10000];
        buffer[0] = '?';
        while (buffer == tmpbuffer || buffer[0] != '{')
            read(sock, buffer, sizeof(buffer));
        for (int i = 0; i < 10000; i++)
            tmpbuffer[i] = buffer[i];
        Document tmp;
        tmp.Parse(buffer);
        if (strcmp(tmp["command"].GetString(), "end") == 0) {
            cout << "退出聊天室\n";
            return;
        }
        cout << tmp["message"].GetString() << "\n";
    }
}