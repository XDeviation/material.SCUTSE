#include "Print_Basic.h"
#include "Print_User_Login.h"
#include "Print_User_Registered.h"
#include "head.h"
using namespace rapidjson;
using namespace std;
#ifndef CLIENT_PRINT_Manager_H
#define CLIENT_PRINT_Manager_H

class client_print_manager : public login, public registered {

  public:
    void init();
    void change_cli_doc(char *, char *);
    void change_srv_doc(char *, char *);
    void set_cli_json();
    void set_srv_json();
    bool Link_Start();
    void Link_Make();
    void work();
    void welcome(bool);
    void welcome2(bool);
    int change_password(bool);
    void chating();
};

#endif