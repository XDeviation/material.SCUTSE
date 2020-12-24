#include "Read_Basic.h"
#include "Read_Manager.h"
#include "Read_User_Login.h"
#include "Read_User_Registered.h"
#include "head.h"
using namespace std;
using namespace rapidjson;

void *sendchat(void *param) {
    client_read_manager *read_data = (client_read_manager *) param;
    read_data->change_srv_doc("username", read_data->user_name_char);
    string s;
    getchar();
    read_data->change_srv_doc("password", "none");
    while (s[0] != 27) {
        getline(cin, s);
        char *tmp = (char *) s.data();
        read_data->change_srv_doc("message", tmp);
        read_data->set_srv_json();
        write(read_data->serv_sock, read_data->Server_Buffer,
              sizeof(read_data->Server_Buffer));
    }
    char c[1];
    c[0] = 27;
    read_data->change_srv_doc("message", c);
    read_data->set_srv_json();
    write(read_data->serv_sock, read_data->Server_Buffer,
          sizeof(read_data->Server_Buffer));
}

void *showchat(void *param) {
    client_read_manager *read_data = (client_read_manager *) param;
    read_data->change_srv_doc("username", read_data->user_name_char);
    bool p = true;
    char tmp[10000];
    while (p) {
        // for (int i = 0; i < 10000; i++)
        //     tmp[i] = '\0';
        tmp[0] = '?';
        Document rec_message; // receive message
        while (tmp[0] != '{')
            read(read_data->serv_sock, tmp, sizeof(tmp));
        rec_message.Parse(tmp);
        // if (rec_message["message"].GetString() == "exit") {
        //     read_data->change_cli_doc("command", "end");
        //     p = false;
        // }
        char *tmp2 = (char *) rec_message["message"].GetString();
        read_data->change_cli_doc("message", tmp2);
        if (strcmp(rec_message["message"].GetString(), "exit") == 0) {
            read_data->change_cli_doc("command", "end");
            p = false;
        }
        read_data->set_cli_json();
        write(read_data->clnt_sock, read_data->Client_Buffer,
              sizeof(read_data->Client_Buffer));
    }
}
