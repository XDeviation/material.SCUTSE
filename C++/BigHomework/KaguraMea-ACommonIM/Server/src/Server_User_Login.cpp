#include "Server_Basic.h"
#include "head.h"
using namespace std;
using namespace rapidjson;

int User_LogIn(int dep, int clnt_sock, vector<User> &userdata,
               server_basic &sendback, string &username, string &password) {

    sendback.change_cli_doc("command", "2");

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

    if (!if_used) {
        sendback.change_cli_doc("message", "1");
        sendback.set_cli_json();
        sendback.change_cli_doc("online", "0");
        write(clnt_sock, sendback.Client_Buffer,
              sizeof(sendback.Client_Buffer));
        return 0;
    }

    // check password
    bool p = (password != Now_Log_User.getSHA_256());
    if (p) {
        sendback.change_cli_doc("message", "2");
        sendback.set_cli_json();
        sendback.change_cli_doc("online", "0");
    } else {
        sendback.change_cli_doc("message", "0");
        sendback.set_cli_json();
        sendback.change_cli_doc("online", "1");
    }

    write(clnt_sock, sendback.Client_Buffer, sizeof(sendback.Client_Buffer));

    if (sendback.Client_Document["online"].GetString() == "1") return 0;
    return 1;
}