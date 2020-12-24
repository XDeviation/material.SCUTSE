#include "head.h"
using namespace rapidjson;
using namespace std;
#ifndef CLIENT_PRINT_BASIC_H
#define CLIENT_PRINT_BASIC_H

class client_print {
  public:
    // some local val
    int sock;
    struct sockaddr_in serv_addr;
    char buffer[10000] = "";
    char Exit[10000] = "exit";
    string username;
    string version = "V1.0.0";
    // user's active
    bool User_ShowFriend(bool);     // show the user's friend
    bool User_AddFriend(bool);      // add friend
    bool User_ChangePassword(bool); // change the user's password
};

#endif