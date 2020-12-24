#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
using namespace std;
class User {
  private:
    int UserID;
    string SHA_256; // password
    string Username;
    string Userpath; // message path

  public:
    User(int UID, string UNAME, string UPW, string PATH)
        : UserID(UID)
        , Username(UNAME)
        , SHA_256(UPW)
        , Userpath(PATH) {
    }

    ~User() = default;

    int getUserID() {
        return UserID;
    }

    string getUsername() {
        return Username;
    }

    string getSHA_256() {
        return SHA_256;
    }

    string getPath() {
        return Userpath;
    }

    void changeSHA_256(string tmp) {
        SHA_256 = tmp;
    }
};

#endif