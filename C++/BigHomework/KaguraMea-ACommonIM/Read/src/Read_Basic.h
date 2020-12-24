#include "head.h"
using namespace rapidjson;
using namespace std;
#ifndef CLIENT_READ_BASIC_H
#define CLIENT_READ_BASIC_H

class client_read {
  public:
    Document Server_Document;
    char *Server_Json = "{\"command\":\"none\","
                        "\"username\":\"none\","
                        "\"password\":\"none\","
                        "\"message\":\"none\","
                        "\"time\":\"none\"}"; // Server_Json
    char Server_Buffer[10000];

    Document Client_Document;
    char *Client_Json = "{\"command\":\"none\","
                        "\"username\":\"none\","
                        "\"message\":\"none\","
                        "\"time\":\"none\"}"; // Client_Json
    char Client_Buffer[10000];

    int serv_sock, clnt_sock, my_sock;
    char host[10000];
    char command[10000];
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    struct sockaddr_in my_addr;
    string user_name_str;
    char user_name_char[100];
    mutex mu;

    // first tag second message
    void change_cli_doc(char *, char *); // change client document
    void change_srv_doc(char *, char *); // change server document

    void set_cli_json(); // set client json
    void set_srv_json(); // set server json
};

#endif