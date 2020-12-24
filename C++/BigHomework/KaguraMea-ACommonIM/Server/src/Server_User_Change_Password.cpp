#include "Server_Basic.h"
#include "head.h"
using namespace std;
using namespace rapidjson;

int User_Change_Password(int dep, int clnt_sock, vector<User> &userdata,
                         server_basic &sendback, string &username,
                         string &password) {

    sendback.change_cli_doc("command", "3");

    User Now_Log_User(1, "", "", "");
    bool if_used = false;
    for (auto it : userdata) {
        if (username == it.getUsername()) {
            if_used = true;
            Now_Log_User = it;
        }
    }

    // write to client;
    // 0:success;
    // 1:unused;
    // 2:password wrong

    // check password
    fstream userout;
    string pw = Now_Log_User.getPath() + "/password";
    userout.open(pw.c_str(), ios::out | ios::trunc);
    userout << password << endl;
    userout.close();
    for (auto &it : userdata) {
        if (username == it.getUsername()) {
            if_used = true;
            it.changeSHA_256(password);
        }
    }

    return 0;
}