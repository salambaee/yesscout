#ifndef YESSCOUT_H
#define YESSCOUT_H

void dns_lookup(const char* hostname);
bool is_port_open(const char* ip, int port);
void reverse_ip_lookup(const char* ip);
bool is_ip_up(const char* ip);

#endif