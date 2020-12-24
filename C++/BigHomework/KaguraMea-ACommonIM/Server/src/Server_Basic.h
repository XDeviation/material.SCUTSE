#include "head.h"
using namespace rapidjson;
using namespace std;
#ifndef SERVER_BASIC_H
#define SERVER_BASIC_H

class server_basic {
  public:
    Document Client_Document;
    char *Client_Json = "{\"command\":\"none\","
                        "\"username\":\"none\","
                        "\"message\":\"none\","
                        "\"online\":\"none\","
                        "\"time\":\"none\"}"; // Client_Json
    char Client_Buffer[10000] = "";
    int sock;

    // first tag second message
    void change_cli_doc(char *, char *); // change client document

    void set_cli_json(); // set client json
};

#endif