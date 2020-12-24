#include "Read_Basic.h"
#include "head.h"
using namespace rapidjson;
using namespace std;
#ifndef CLIENT_READ_REGISTERED_H
#define CLIENT_READ_REGISTERED_H

class registered : virtual public client_read {

  public:
    int User_Registered(int);
};

#endif