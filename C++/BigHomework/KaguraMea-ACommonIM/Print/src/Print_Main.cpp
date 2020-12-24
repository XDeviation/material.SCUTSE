/*
 *   Mea V1.0.0 developing
 *   Client_Print
 *   Au:Lost_Deviation
 */
const char version[100] = "V1.0.0";
#include "Print_Basic.h"
#include "Print_Manager.h"
#include "Print_User_Login.h"
#include "Print_User_Registered.h"
#include "head.h"
#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)
using namespace std;

int main() {
    std::setlocale(LC_ALL, "UTF-8");
    client_print_manager cln;
    cln.work();
    return 0;
}
