#include "Server_Basic.h"
#include "head.h"
using namespace std;

int User_Registered(int dep, int clnt_sock, vector<User> &userdata,
                    server_basic &sendback, string username, string password) {
    fstream userout;

    // check if main path is created
    string dir = "./usrdata";
    if (access(dir.c_str(), 0) == -1) {
        int flag = mkdir(dir.c_str(), 0777);
    }

    // mkdir
    dir += "/";
    dir += to_string(userdata.size() + 1);
    mkdir(dir.c_str(), 0777);
    string pw = dir + "/password";
    userout.open(pw.c_str(), ios::out);
    userout << password;
    userout.close();

    // new user
    User newuser(userdata.size() + 1, username, password, dir);
    userdata.push_back(newuser);

    userout.open("userdata", ios::app | ios::out);
    userout << "UserID:" << userdata[userdata.size() - 1].getUserID()
            << "\nUsername:" << userdata[userdata.size() - 1].getUsername()
            << "\nUserpath:" << userdata[userdata.size() - 1].getPath() << endl;
    userout.close();

    return 0;
}