#include "Print_Basic.h"
#include "head.h"
using namespace rapidjson;
using namespace std;
#ifndef CLIENT_PRINT_LOGIN_H
#define CLIENT_PRINT_LOGIN_H

class login : virtual public client_print {

  public:
    int User_LogIn(bool, int);
};

#endif