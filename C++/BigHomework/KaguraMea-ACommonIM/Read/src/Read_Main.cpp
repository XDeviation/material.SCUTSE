/*
 *   Mea V1.0.0 developing
 *   Client_Read
 *   Au:Lost_Deviation
 */

#include "Read_Basic.h"
#include "Read_Manager.h"
#include "Read_User_Login.h"
#include "Read_User_Registered.h"
#include "head.h"
#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)
using namespace std;
using namespace rapidjson;

int set_disp_mode(int,
                  int); // option:0=password 1=common
                        // it make the password become unview

int main() {
    client_read_manager clnread;
    clnread.init();
    clnread.work();
}

int set_disp_mode(int fd, int option) {
    int err;
    struct termios term;
    if (tcgetattr(fd, &term) == -1) {
        perror("Cannot get the attribution of the terminal");
        return 1;
    }
    if (option)
        term.c_lflag |= ECHOFLAGS;
    else
        term.c_lflag &= ~ECHOFLAGS;
    err = tcsetattr(fd, TCSAFLUSH, &term);
    if (err == -1 && err == EINTR) {
        perror("Cannot set the attribution of the terminal");
        return 1;
    }
    return 0;
}
