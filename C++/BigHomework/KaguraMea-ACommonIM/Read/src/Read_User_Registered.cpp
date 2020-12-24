#include "Read_User_Registered.h"
#include "Read_Basic.h"
#include "head.h"
#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)
using namespace std;
using namespace rapidjson;
int set_disp_mode(int, int);
int change_command(Document &);

int registered::User_Registered(int dep) {
    char User_name[10000] = "", password[10000] = "", repassword[10000] = "",
         answer[10000] = "";
    string s;
    if (dep <= 1) {
        cin >> s;

        if (s[0] == 27) {
            write(clnt_sock, "4", 1);
            return 0;
        }
        // write to print:
        // 0:success;
        // 1:be used;
        // 2:too long;
        // 3:too short;
        // 4:wrong;

        if (s.length() > 100) {
            write(clnt_sock, "2", 1);
            return User_Registered(1);
        }
        if (s.length() < 6) {
            write(clnt_sock, "3", 1);
            return User_Registered(1);
        } else {
            for (int i = 0; i < s.length(); i++)
                User_name[i] = s[i];
            User_name[s.length()] = '\0';

            change_srv_doc("command", "0");
            change_srv_doc("username", User_name);
            set_srv_json();

            write(serv_sock, Server_Buffer, sizeof(Server_Buffer));
            while (answer[0] != '{')
                read(serv_sock, answer, sizeof(answer));

            // Upsend;
            // answer:
            // 0:unused;
            // 1:be used;

            Document tmp;
            tmp.Parse(answer);

            if (strcmp(tmp["message"].GetString(), "1") == 0) {
                write(clnt_sock, "1", 1);
                return User_Registered(1);
            } else {
                write(clnt_sock, "0", 1);
                user_name_str = s;
                // for (int i = 0; i < s.length(); i++)
                //     User_name[i] = s[i];
                // User_name[s.length()] = '\0';
            }
        }
        cin.ignore();
    }

    cout << "working input password" << endl;

    // input password
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
            set_disp_mode(STDIN_FILENO, 1);
            return 0;
        }
    } while (c != '\n' && c != '\r' && passwordn <= 20);
    password[passwordn] = '\0';
    if (passwordn > 20) {
        while (c != '\n' && c != '\r')
            c = getchar();
        write(clnt_sock, "2", 1);
        return User_Registered(2);
    }
    if (passwordn < 6) {
        write(clnt_sock, "3", 1);
        return User_Registered(2);
    } else {
        write(clnt_sock, "0", 1);
    }

    do {
        c = getchar();
        if (c != '\n' && c != '\r') {
            repassword[repasswordn++] = c;
        }
        if (c == 27) {
            while (c != '\n' && c != '\r')
                c = getchar();
            write(clnt_sock, "5", 1);
            set_disp_mode(STDIN_FILENO, 1);
            return 0;
        }
    } while (c != '\n' && c != '\r' && repasswordn <= 20);
    if (passwordn > 20)
        while (c != '\n' && c != '\r')
            c = getchar();
    repassword[repasswordn] = '\0';

    // check password
    if (strcmp(repassword, password) || passwordn > 20) {
        write(clnt_sock, "4", 1);
        return User_Registered(2);
    } else {
        // Upsend
        string src_str = password; // plantext
        string hash_hex_str;       // ciphertext
        vector<unsigned char> hash(picosha2::k_digest_size);
        picosha2::hash256(src_str.begin(), src_str.end(), hash.begin(),
                          hash.end());
        hash_hex_str =
            picosha2::bytes_to_hex_string(hash.begin(), hash.end()); // change
        char ciphertext[65];
        for (int i = 0; i < 64; i++)
            ciphertext[i] = hash_hex_str[i];
        ciphertext[64] = '\0';
        change_srv_doc("command", "1");
        change_srv_doc("password", ciphertext);
        set_srv_json();

        write(serv_sock, Server_Buffer, sizeof(Server_Buffer));
        write(clnt_sock, "0", 1);
    }
    set_disp_mode(STDIN_FILENO, 1);
}