#include "Server_Basic.h"
#include "head.h"
using namespace std;
using namespace rapidjson;

void server_basic::change_cli_doc(char *tag, char *message) {
    Value &tmp = Client_Document[tag];
    tmp = StringRef(message);
}

void server_basic::set_cli_json() {
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    Client_Document.Accept(writer);
    string tmp = buffer.GetString();
    for (int i = 0; i < 10000; i++)
        Client_Buffer[i] = '\0';
    for (int i = 0; i < tmp.length(); i++)
        Client_Buffer[i] = tmp[i];
}
