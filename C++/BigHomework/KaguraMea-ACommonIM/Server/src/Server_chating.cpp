#include "Server_Basic.h"
#include "head.h"
using namespace std;
using namespace rapidjson;
mutex mtx;

void *User_Send_Chat(void *sock) {
    server_basic *tmp = (server_basic *) sock;
    fstream userout;

    int dep = 0;
    string exitmessage = "User ";
    exitmessage += tmp->Client_Document["username"].GetString();
    exitmessage += " is exit";

    string s;
    vector<string> sendmessage;

    mtx.lock();
    userout.open("usermessage", ios::in);
    while (getline(userout, s)) {
        sendmessage.push_back(s);
        dep++;
    }
    userout.close();
    mtx.unlock();

    for (auto it : sendmessage) {
        char *tmpsend = (char *) it.data();
        tmp->change_cli_doc("message", tmpsend);
        tmp->set_cli_json();
        write(tmp->sock, tmp->Client_Buffer, sizeof(tmp->Client_Buffer));
    }

    bool p = true;
    while (p) {
        vector<string> newsendmessage;
        mtx.lock();
        userout.open("usermessage", ios::in);
        int tmpdep = 0;
        while (tmpdep < dep) {
            getline(userout, s);
            tmpdep++;
        }
        while (getline(userout, s)) {
            newsendmessage.push_back(s);
            dep++;
        }
        userout.close();
        mtx.unlock();

        for (auto it : newsendmessage) {
            if (it == exitmessage) {
                tmp->change_cli_doc("message", "exit");
                tmp->set_cli_json();
                write(tmp->sock, tmp->Client_Buffer,
                      sizeof(tmp->Client_Buffer));
                p = false;
            } else if (p) {
                char *tmpsend = (char *) it.data();
                tmp->change_cli_doc("message", tmpsend);
                tmp->set_cli_json();
                write(tmp->sock, tmp->Client_Buffer,
                      sizeof(tmp->Client_Buffer));
            }
        }

        // sleep(1);
    }
}

void *User_Receive_Chat(void *sock) {
    server_basic *tmp = (server_basic *) sock;
    fstream userout;
    string exitmessage = "User ";
    exitmessage += tmp->Client_Document["username"].GetString();
    exitmessage += " is exit";
    char buffer[10000];
    bool p = true;
    while (p) {
        buffer[0] = '?';
        while (buffer[0] != '{')
            read(tmp->sock, buffer, sizeof(buffer));
        Document tmpbuffer;
        tmpbuffer.Parse(buffer);
        if (tmpbuffer["message"].GetString()[0] == 27) {
            mtx.lock();
            userout.open("usermessage", ios::app | ios::out);
            userout << exitmessage << endl;
            userout.close();
            mtx.unlock();
            p = false;
        } else {
            time_t now = time(0);
            tm *nowtm = localtime(&now);
            mtx.lock();
            userout.open("usermessage", ios::app | ios::out);
            userout << tmp->Client_Document["username"].GetString() << ' '
                    << setw(4) << setfill('0') << nowtm->tm_year + 1900 << '-'
                    << setw(2) << setfill('0') << nowtm->tm_mon + 1 << '-'
                    << setw(2) << setfill('0') << nowtm->tm_mday << ' '
                    << setw(2) << setfill('0') << nowtm->tm_hour << ":"
                    << setw(2) << setfill('0') << nowtm->tm_min << ":"
                    << setw(2) << setfill('0') << nowtm->tm_sec << ' '
                    << tmpbuffer["message"].GetString() << "\n";
            userout.close();
            mtx.unlock();
        }
    }
}