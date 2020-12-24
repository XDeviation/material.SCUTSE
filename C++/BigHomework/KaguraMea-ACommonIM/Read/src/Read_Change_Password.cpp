#include "Read_Basic.h"
#include "Read_Manager.h"
#include "Read_User_Login.h"
#include "Read_User_Registered.h"
#include "head.h"
#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)
using namespace std;
using namespace rapidjson;
int set_disp_mode(int, int);
int client_read_manager::change_password(int dep) {
    char User_name[101] = "", password[100] = "", repassword[100] = "",
         answer[1000] = "";
    string s;
    getchar();
    cout << "working input password" << endl;

    set_disp_mode(STDIN_FILENO, 0);
    char c;
    int passwordn = 0, repasswordn = 0;
    do {
        c = getchar();
        if (c != '\n' && c != '\r') {
            password[passwordn++] = c;
        }
        if (c == 27) {
            while (c != '\n' && c != '\r')
                c = getchar();
            write(clnt_sock, "5", 1);
            return 0;
            set_disp_mode(STDIN_FILENO, 1);
        }
    } while (c != '\n' && c != '\r' && passwordn <= 20);
    password[passwordn] = '\0';
    if (passwordn > 20) {
        while (c != '\n' && c != '\r')
            c = getchar();
        write(clnt_sock, "2", 1);
        return change_password(2);
    }
    if (passwordn < 6) {
        write(clnt_sock, "3", 1);
        return change_password(2);
    } else {
        // Upsend
        string src_str = password; // plantext
        string hash_hex_str;       // ciphertext
        vector<unsigned char> hash(picosha2::k_digest_size);
        picosha2::hash256(src_str.begin(), src_str.end(), hash.begin(),
                          hash.end());
        hash_hex_str = picosha2::bytes_to_hex_string(hash.begin(),
                                                     hash.end()); // change
        char ciphertext[65];
        for (int i = 0; i < 64; i++)
            ciphertext[i] = hash_hex_str[i];
        ciphertext[64] = '\0';
        change_srv_doc("command", "3");
        change_srv_doc("password", ciphertext);
        change_srv_doc("username", user_name_char);
        set_srv_json();

        write(serv_sock, Server_Buffer, sizeof(Server_Buffer));

        // success:
        // 0:success;
        // 1:wrong;

        cout << "ending!" << endl;
        write(clnt_sock, "0", 1);
    }
    set_disp_mode(STDIN_FILENO, 1);
    return 1;
}