#include "Read_Basic.h"
#include "head.h"
using namespace rapidjson;
using namespace std;
#ifndef CLIENT_READ_LOGIN_H
#define CLIENT_READ_LOGIN_H

class login : virtual public client_read {

  public:
    int User_LogIn(int);
};

#endif