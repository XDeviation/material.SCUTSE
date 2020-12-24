#include "Read_Basic.h"
#include "Read_User_Login.h"
#include "Read_User_Registered.h"
#include "head.h"
using namespace rapidjson;
using namespace std;
#ifndef CLIENT_READ_Manager_H
#define CLIENT_READ_Manager_H

class client_read_manager : public login, public registered {

  public:
    void init();

    bool Link_Start(); // link to server
    void Link_Make();  // link to print
    void work();
    int change_password(int);
    friend void *showchat(void *prarm);
    friend void *sendchat(void *prarm);
};

#endif