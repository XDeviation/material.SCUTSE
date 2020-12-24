#include "Print_Basic.h"
#include "head.h"
using namespace rapidjson;
using namespace std;
#ifndef CLIENT_PRINT_REGISTERED_H
#define CLIENT_PRINT_REGISTERED_H

class registered : virtual public client_print {

  public:
    int User_Registered(bool, int);
};

#endif