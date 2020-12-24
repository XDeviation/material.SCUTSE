/*
 *   Mea V1.0.0 developing
 *   Server
 *   Au:Lost_Deviation
 */
#include "Server_Basic.h"
#include "head.h"
using namespace std;
using namespace rapidjson;

// local val
fstream userout;
int serv_sock;
int clnt_sock;
char host[100];
// char command[100];
struct sockaddr_in serv_addr;
struct sockaddr_in clnt_addr;
vector<User> userdata;

// server poerate
// these void are used to write the log
void Server_Start();
void Server_End();
void New_User_Login(string);
void New_User_Registered(string);
void New_User_Change_Password(string);
void New_IP_Connect(string, int);
void New_IP_Disconnect(string, int);

// user operate
void User_init(); // read user message from file
vector<string> split(string str, const string &delimiters); // split

int User_Name_Check(int, int, string, vector<User> &,
                    server_basic &); // check if username is used
int User_Registered(int, int, vector<User> &, server_basic &, string,
                    string); // registered, return 0,1,2 to show the result
int User_LogIn(int, int, vector<User> &, server_basic &, string &,
               string &); // login, return 0,1 to show the result
int User_Change_Password(
    int, int, vector<User> &, server_basic &, string &,
    string &); // changepassword, return 0,1  to show the result

// multithreading void
void *Clnt_Receive(void *socketListen); // connect to the client and into main
void *Clnt_Main(void *sock);            // true main
void *User_Send_Chat(void *sock);
void *User_Receive_Chat(void *sock);

// 0 alive 1 killed
int checkThrIsKill(pthread_t thr);

typedef struct MySocketInfo {
    int socketCon;
    char *ipaddr;
    uint16_t port;
} _MySocketInfo;

// clientsocks
struct MySocketInfo arrConSocket[20];
int conClientCount = 0;

// client connect process
pthread_t arrThrReceiveClient[20];
int thrReceiveClientCount = 0;

int main() {
    // init
    userout.open("userdata", ios::in);
    User_init();
    userout.close();
    Server_Start();

    // make socket
    cout << "Let's start\ncreate socket...";
    int socketListen = socket(AF_INET, SOCK_STREAM, 0);
    if (socketListen < 0) {
        cout << "failed\n";
        exit(-1);
    } else {
        cout << "success\n";
    }

    // link with IP and port
    cout << "Link start...";
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;                // IPv4
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // IP address
    server_addr.sin_port = htons(19198);             // port
    if (bind(socketListen, (struct sockaddr *) &server_addr,
             sizeof(struct sockaddr)) != 0) {
        perror("falied\n");
        exit(-1);
    } else {
        printf("success\n");
    }

    // into listening
    cout << "Into listening...";
    if (listen(socketListen, 10) != 0) {
        cout << "failed" << endl;
        exit(-1);
    } else {
        cout << "success" << endl;
    }

    // receive sock
    pthread_t thrAccept;
    pthread_create(&thrAccept, NULL, Clnt_Receive, &socketListen);

    // log
    while (1) {
        // receive number
        int i;
        for (i = 0; i < thrReceiveClientCount; i++) {
            if (checkThrIsKill(arrThrReceiveClient[i]) == 1) {
                cout << "IP "
                     << "is disconnect" << endl;
                thrReceiveClientCount--;
            }
        }
        cout << "Alive connect: " << thrReceiveClientCount << endl;

        // close server
        char userStr[30] = {'0'};
        scanf("%s", userStr);
        if (strcmp(userStr, "exit") == 0) {
            printf("exit!\n");
            break;
        }

        // // 发送消息
        // if (conClientCount <= 0) {
        //     printf("没有客户端连接\n");
        // } else {
        //     int i;
        //     for (i = 0; i < conClientCount; i++) {
        //         // int sendMsg_len = send(arrConSocket[i].socketCon, userStr,
        //         // 30, 0);
        //         int sendMsg_len = write(arrConSocket[i].socketCon, userStr,
        //         30); if (sendMsg_len > 0) {
        //             printf("向%s:%d发送成功\n", arrConSocket[i].ipaddr,
        //                    arrConSocket[i].port);
        //         } else {
        //             printf("向%s:%d发送失败\n", arrConSocket[i].ipaddr,
        //                    arrConSocket[i].port);
        //         }
        //     }
        // }

        sleep(0.5);
    }

    // ~
    close(serv_sock);
    close(clnt_sock);
    Server_End();
    userout.close();
    return 0;
}

void User_init() {
    string s;
    vector<string> input_user_data[4];
    while (userout.peek() != EOF) {
        for (int i = 0; i < 3; i++) {
            getline(userout, s);
            input_user_data[i] = split(s, ":");
        }
        string userpath = input_user_data[2][1];
        ifstream pwinput;                        // password input
        string upwpath = userpath + "/password"; // password path
        pwinput.open(upwpath.c_str(), ios::in);
        string password;
        pwinput >> password;
        pwinput.close();
        User new_user(stoi(input_user_data[0][1]), input_user_data[1][1],
                      password, userpath);
        userdata.push_back(new_user);
    }
}

vector<string> split(string str, const string &delimiters) {
    regex del(delimiters);
    vector<string> v(sregex_token_iterator(str.begin(), str.end(), del, -1),
                     sregex_token_iterator());
    return v;
}

void *Clnt_Receive(void *socketListen) {
    while (1) {
        int sockaddr_in_size = sizeof(struct sockaddr_in);
        struct sockaddr_in client_addr;
        int _socketListen = *((int *) socketListen);
        int socketCon =
            accept(_socketListen, (struct sockaddr *) (&client_addr),
                   (socklen_t *) (&sockaddr_in_size));
        if (socketCon < 0) {
            printf("连接失败\n");
        } else {
            printf("ip: %s:%d is connected\r\n",
                   inet_ntoa(client_addr.sin_addr), client_addr.sin_port);
            New_IP_Connect(inet_ntoa(client_addr.sin_addr),
                           client_addr.sin_port);
        }
        printf("socket: %d\n", socketCon);
        write(socketCon, "T", 1);

        // create a new process
        _MySocketInfo socketInfo;
        socketInfo.socketCon = socketCon;
        socketInfo.ipaddr = inet_ntoa(client_addr.sin_addr);
        socketInfo.port = client_addr.sin_port;
        arrConSocket[conClientCount] = socketInfo;
        conClientCount++;
        printf("Total connect: %d\n", conClientCount);

        // into main
        pthread_t thrReceive = 0;
        pthread_create(&thrReceive, NULL, Clnt_Main, &socketCon);

        // sleep
        sleep(0.5);
    }

    char *s = "安全退出接受进程";
    pthread_exit(s);
}

int checkThrIsKill(pthread_t thr) {
    int res = 1;
    int res_kill = pthread_kill(thr, 0);
    if (res_kill == 0) {
        res = 0;
    }
    return res;
}

void *Clnt_Main(void *sock) {
    server_basic sendback;
    sendback.Client_Document.Parse(sendback.Client_Json);
    int clnt_sock = *((int *) sock);
    sendback.sock = clnt_sock;
    bool if_close = false;
    while (!if_close) {
        char command[10000] = "";
        while (command[0] != '{')
            read(clnt_sock, command, sizeof(command));
        Document tmp;
        tmp.Parse(command);

        if (strcmp(tmp["command"].GetString(), "0") == 0) {
            // used:1 unused:0
            User_Name_Check(1, clnt_sock, tmp["username"].GetString(), userdata,
                            sendback);
        } else if (strcmp(tmp["command"].GetString(), "1") == 0) {
            string username = tmp["username"].GetString();
            string password = tmp["password"].GetString();
            if (User_Registered(1, clnt_sock, userdata, sendback, username,
                                password) == 0) {
                New_User_Registered(username);
            }
        } else if (strcmp(tmp["command"].GetString(), "2") == 0) {
            string username = tmp["username"].GetString();
            string password = tmp["password"].GetString();
            if (User_LogIn(1, clnt_sock, userdata, sendback, username,
                           password) == 0) {
                New_User_Login(username);
                char *tmpusername = (char *) username.data();
                sendback.change_cli_doc("username", tmpusername);
            }
        } else if (strcmp(tmp["command"].GetString(), "3") == 0) {
            string username = tmp["username"].GetString();
            string password = tmp["password"].GetString();
            if (User_Change_Password(1, clnt_sock, userdata, sendback, username,
                                     password) == 0) {
            }
        } else if (strcmp(tmp["command"].GetString(), "4") == 0) {
            pthread_t sendchat;
            pthread_t showchat;
            pthread_create(&sendchat, NULL, User_Receive_Chat,
                           (void *) &sendback);
            pthread_create(&showchat, NULL, User_Send_Chat, (void *) &sendback);
        } else if (strcmp(tmp["command"].GetString(), "exit") == 0) {
            break;
        }
    }
}