#include "Read_Manager.h"
#include "Read_Basic.h"
#include "Read_User_Login.h"
#include "Read_User_Registered.h"
#include "head.h"
#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)
using namespace std;
using namespace rapidjson;

void *showchat(void *param);
void *sendchat(void *param);

void client_read_manager::init() {
    Server_Document.Parse(Server_Json);
    Client_Document.Parse(Client_Json);
}

void client_read_manager::work() {
    Server_Document.Parse(Server_Json);
    while (!Link_Start()) {
        printf("\033[2J\n");
        cout << "连接服务器中" << flush;
        for (int j = 1; j <= 100000000; j++)
            j == j;
        for (int i = 1; i <= 10; i++) {
            for (int j = 1; j <= 20000000; j++)
                ;
            cout << '.' << flush;
        }
        cout << endl;
        cout << "连接服务器失败\n请确认设备已联网\n输入exit退出，或输入其他任意"
                "字符重新连接\n";
        string s;
        cin >> s;
        if (s == "exit") return;
    }
    printf("\033[2J\n");
    cout << "连接服务器中" << flush;
    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 20000000; j++)
            ;
        cout << '.' << flush;
    }
    cout << endl;
    cout << "连接成功！\n" << flush;
    Link_Make();

    while (cin >> command) {
        if (strcmp(command, "1") == 0) {
            // write(serv_sock, "1", 1);
            write(clnt_sock, command, sizeof(command));
            User_Registered(0);
        } else if (strcmp(command, "2") == 0) {
            // write(serv_sock, "2", 1);
            write(clnt_sock, command, sizeof(command));
            if (User_LogIn(0) == 1) break;
        } else if (strcmp(command, "exit") == 0) {

            // tell the server
            change_srv_doc("command", "exit");
            set_srv_json();
            write(serv_sock, Server_Buffer, sizeof(Server_Buffer));

            // tell the client
            write(clnt_sock, command, sizeof(command));
            break;

        } else {
            write(clnt_sock, command, sizeof(command));
        }
    }

    while (cin >> command) {
        if (strcmp(command, "1") == 0) {
            // write(serv_sock, "1", 1);
            // write(clnt_sock, command, sizeof(command));
            // User_Registered(0);
        } else if (strcmp(command, "2") == 0) {
            // write(serv_sock, "2", 1);
            write(clnt_sock, command, sizeof(command));
            change_srv_doc("command", "4");
            set_srv_json();
            write(serv_sock, Server_Buffer, sizeof(Server_Buffer));
            pthread_t sdchat;
            pthread_t shchat;
            int ret;
            ret = pthread_create(&sdchat, NULL, sendchat, this);
            ret = pthread_create(&shchat, NULL, showchat, this);
            pthread_join(sdchat, NULL);
            pthread_join(shchat, NULL);
        } else if (strcmp(command, "3") == 0) {
            // bool success = User_ShowFriend();
        } else if (strcmp(command, "4") == 0) {
            // bool success = User_AddFriend();
        } else if (strcmp(command, "5") == 0) {
            write(clnt_sock, command, sizeof(command));
            bool success = change_password(0);
        } else if (strcmp(command, "exit") == 0) {

            // tell the server
            change_srv_doc("command", "exit");
            set_srv_json();
            write(serv_sock, Server_Buffer, sizeof(Server_Buffer));

            // tell the client
            write(clnt_sock, command, sizeof(command));
            break;
        } else {
            write(clnt_sock, command, sizeof(command));
        }
    }

    // close sock
    close(clnt_sock);
    close(serv_sock);
}

bool client_read_manager::Link_Start() {
    // make socket
    char host[10000] = {0};
    char buffer[10000] = {0};
    serv_sock = socket(AF_INET, SOCK_STREAM, 0);

    // send request
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;                     // IPv4
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP address
    serv_addr.sin_port = htons(19198);                  // port

    connect(serv_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    read(serv_sock, buffer, sizeof(buffer));
    if (buffer[0] == 'T') return true;
    return false;
}

void client_read_manager::Link_Make() {
    // make socket
    my_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // link with IP and port
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;         // IPv4
    my_addr.sin_addr.s_addr = INADDR_ANY; // IP address
    my_addr.sin_port = htons(10086);      // port
    bind(my_sock, (struct sockaddr *) &my_addr, sizeof(my_addr));

    // into listening
    listen(my_sock, 20);

    // receive request
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    clnt_sock =
        accept(my_sock, (struct sockaddr *) &clnt_addr, &clnt_addr_size);

    // send message
    char str[100] = "T";
    write(clnt_sock, str, sizeof(str));
}

void client_read::change_cli_doc(char *tag, char *message) {
    mu.lock();
    Value &tmp = Client_Document[tag];
    tmp = StringRef(message);
    mu.unlock();
}

void client_read::change_srv_doc(char *tag, char *message) {
    mu.lock();
    Value &tmp = Server_Document[tag];
    tmp = StringRef(message);
    mu.unlock();
}

void client_read::set_cli_json() {
    mu.lock();
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    Client_Document.Accept(writer);
    string tmp = buffer.GetString();
    for (int i = 0; i < 10000; i++)
        Client_Buffer[i] = '\0';
    for (int i = 0; i < tmp.length(); i++)
        Client_Buffer[i] = tmp[i];
    mu.unlock();
}

void client_read::set_srv_json() {
    mu.lock();
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    Server_Document.Accept(writer);
    string tmp = buffer.GetString();
    for (int i = 0; i < 10000; i++)
        Server_Buffer[i] = '\0';
    for (int i = 0; i < tmp.length(); i++) {
        Server_Buffer[i] = tmp[i];
        mu.unlock();
    }
}