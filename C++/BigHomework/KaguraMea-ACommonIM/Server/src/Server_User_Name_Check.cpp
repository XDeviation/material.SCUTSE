#include "Server_Basic.h"
#include "head.h"
using namespace std;
using namespace rapidjson;

int User_Name_Check(int dep, int clnt_sock, string username,
                    vector<User> &userdata, server_basic &sendback) {
    bool if_used = false;
    for (auto it : userdata) {
        if (username == it.getUsername()) if_used = true;
    }

    // write to client;
    // 0:unused;
    // 1:be used;

    if (if_used) {
        sendback.change_cli_doc("command", "0");
        sendback.change_cli_doc("message", "1");
    } else {
        sendback.change_cli_doc("command", "0");
        sendback.change_cli_doc("message", "0");
    }

    sendback.set_cli_json();

    write(clnt_sock, sendback.Client_Buffer, sizeof(sendback.Client_Buffer));
}