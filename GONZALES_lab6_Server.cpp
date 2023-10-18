#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main() {
    int serverFD, s1, s2, vr;
    struct sockaddr_in addr;
    int opt = 1;
    int addrlen = sizeof(addr);
    char buffer[1024] = {0};
    string msg;

    // Creating socket file descriptor
    if ((serverFD = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(serverFD, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(9001);
    cout << "Waiting for the client connections" << endl;

    // Forcefully attaching socket to the port 8080
    if (bind(serverFD, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(serverFD, 2) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((s1 = accept(serverFD, (struct sockaddr *)&addr, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    cout << "[C++ SERVER] Connection with CLIENT 1 established." << endl;
    cout << "[C++ SERVER] waiting for the input..." << endl;
    vr = read(s1, buffer, 1024);
    int n1 = stoi(buffer);
    cout << "a = "  << n1 << endl;
    bzero(buffer, 1024);

    vr = read(s1, buffer, 1024);
    int n3 = stoi(buffer);
    cout << "b = "  << n3 << endl;
    bzero(buffer, 1024);

    if ((s2 = accept(serverFD, (struct sockaddr *)&addr, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    cout << "[C++ SERVER] Connection with CLIENT 2 established." << endl;
    cout << "[C++ SERVER] waiting for the input..." << endl;
    vr = read(s2, buffer, 1024);
    int n2 = stoi(buffer);
    cout << "c = "  << n2 << endl;
    bzero(buffer, 1024);

    vr = read(s2, buffer, 1024);
    int n4 = stoi(buffer);
    cout << "d = "  << n4 << endl;
    bzero(buffer, 1024);

    int sum = n1 + n2 +n3 + n4;
    cout << "[C++ SERVER] The sum has been computed... "  << sum << endl;
    msg = to_string(sum);
    send(s1, msg.c_str(), msg.length(), 0);
    send(s2, msg.c_str(), msg.length(), 0);
    
    close(s1);
    close(s2);
    close(serverFD);
    return 0;
}