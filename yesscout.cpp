#include "yesscout.h"
#include <iostream>
#include <cstring>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

bool is_ip_up(const char* ip) {
    string command = "ping -c 1 -W 1 ";
    command += ip;
    command += " > /dev/null 2>&1";
    int result = system(command.c_str());
    return (result == 0);
}

void reverse_ip_lookup(const char* ip) {
    struct sockaddr_in sa;
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &sa.sin_addr);
    int status = getnameinfo((struct sockaddr*)&sa, sizeof(sa), host, sizeof(host), service, sizeof(service), 0);
    if (status == 0) {
        cout << "Hostname : " << host << endl;
    } else {
        cerr << "Error : " << gai_strerror(status) << endl;
    }
}

void dns_lookup(const char* hostname) {
    struct addrinfo hints, *res;
    int status;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    status = getaddrinfo(hostname, NULL, &hints, &res);
    if (status != 0) {
        cerr << "Get address info error: " << gai_strerror(status) << endl;
        return;
    }

    void* addr;
    char ipstr[INET6_ADDRSTRLEN];

    if (res->ai_family == AF_INET) {
        struct sockaddr_in* ipv4 = (struct sockaddr_in*)res->ai_addr;
        addr = &(ipv4->sin_addr);
    } else {
        struct sockaddr_in6* ipv6 = (struct sockaddr_in6*)res->ai_addr;
        addr = &(ipv6->sin6_addr);
    }

    inet_ntop(res->ai_family, addr, ipstr, sizeof(ipstr));
    cout << "Domain name : " << hostname << endl;
    cout << "IP Address: " << ipstr << endl;
    freeaddrinfo(res);
}

bool is_port_open(const char* ip, int port) {
    int sock;
    struct sockaddr_in server_addr;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Socket creation failed");
        return false;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

    int result = connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    close(sock);
    return result == 0;
}
