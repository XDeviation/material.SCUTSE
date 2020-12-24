#include "Server_Basic.h"
#include "head.h"
using namespace std;
using namespace rapidjson;

void Server_Start() {
    time_t now = time(0);
    tm *nowtm = localtime(&now);
    fstream logout;
    logout.open("Server_Log", ios::app | ios::out);
    logout << "---------------------\n";
    logout << nowtm->tm_year + 1900 << '-' << setw(2) << setfill('0')
           << nowtm->tm_mon << '-' << setw(2) << setfill('0') << nowtm->tm_mday
           << ' ' << setw(2) << setfill('0') << nowtm->tm_hour << ":" << setw(2)
           << setfill('0') << nowtm->tm_min << ":" << setw(2) << setfill('0')
           << nowtm->tm_sec << " Server start\n";
    logout.close();
}

void Server_End() {
    time_t now = time(0);
    tm *nowtm = localtime(&now);
    fstream logout;
    logout.open("Server_Log", ios::app | ios::out);
    logout << nowtm->tm_year + 1900 << '-' << setw(2) << setfill('0')
           << nowtm->tm_mon << '-' << setw(2) << setfill('0') << nowtm->tm_mday
           << ' ' << setw(2) << setfill('0') << nowtm->tm_hour << ":" << setw(2)
           << setfill('0') << nowtm->tm_min << ":" << setw(2) << setfill('0')
           << nowtm->tm_sec << " Server close\n\n";
    logout.close();
}

void New_User_Login(string username) {
    time_t now = time(0);
    tm *nowtm = localtime(&now);
    fstream logout;
    logout.open("Server_Log", ios::app | ios::out);
    logout << nowtm->tm_year + 1900 << '-' << setw(2) << setfill('0')
           << nowtm->tm_mon << '-' << setw(2) << setfill('0') << nowtm->tm_mday
           << ' ' << setw(2) << setfill('0') << nowtm->tm_hour << ":" << setw(2)
           << setfill('0') << nowtm->tm_min << ":" << setw(2) << setfill('0')
           << nowtm->tm_sec << " User: " << username << " is logined\n";
    logout.close();
}

void New_User_Registered(string username) {
    time_t now = time(0);
    tm *nowtm = localtime(&now);
    fstream logout;
    logout.open("Server_Log", ios::app | ios::out);
    logout << nowtm->tm_year + 1900 << '-' << setw(2) << setfill('0')
           << nowtm->tm_mon << '-' << setw(2) << setfill('0') << nowtm->tm_mday
           << ' ' << setw(2) << setfill('0') << nowtm->tm_hour << ":" << setw(2)
           << setfill('0') << nowtm->tm_min << ":" << setw(2) << setfill('0')
           << nowtm->tm_sec << " User: " << username << " is registered\n";
    logout.close();
}

void New_IP_Connect(string IPaddress, int port) {
    time_t now = time(0);
    tm *nowtm = localtime(&now);
    fstream logout;
    logout.open("Server_Log", ios::app | ios::out);
    logout << nowtm->tm_year + 1900 << '-' << setw(2) << setfill('0')
           << nowtm->tm_mon << '-' << setw(2) << setfill('0') << nowtm->tm_mday
           << ' ' << setw(2) << setfill('0') << nowtm->tm_hour << ":" << setw(2)
           << setfill('0') << nowtm->tm_min << ":" << setw(2) << setfill('0')
           << nowtm->tm_sec << " IP: " << IPaddress << ":" << port
           << " is connected\n";
    logout.close();
}

void New_IP_Disconnect(string IPaddress, int port) {
    time_t now = time(0);
    tm *nowtm = localtime(&now);
    fstream logout;
    logout.open("Server_Log", ios::app | ios::out);
    logout << nowtm->tm_year + 1900 << '-' << nowtm->tm_mon << '-'
           << nowtm->tm_mday << ' ' << nowtm->tm_hour << ":" << nowtm->tm_min
           << ":" << nowtm->tm_sec << " IP: " << IPaddress << ":" << port
           << " is disconnected\n";
    logout.close();
}