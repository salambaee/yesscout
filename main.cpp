#include <iostream>
#include "yesscout.h"

using namespace std;

int main() {
    char const* header_name = R"(                                            _   
                                           | |  
  _   _   ___  ___  ___   ___  ___   _   _ | |_ 
 | | | | / _ \/ __|/ __| / __|/ _ \ | | | || __|
 | |_| ||  __/\__ \\__ \| (__| (_) || |_| || |_ 
  \__, | \___||___/|___/ \___|\___/  \__,_| \__|
   __/ |                                        
  |___/                                         

yesscout0.1 written by salambae [project1337]
https://github.com/salambaee/yesscout
)";
    char hostname[256];
    char ip[256];
    int input;
    int start_port, end_port;
    while (true) {
        cout << header_name << endl;
        cout << "1. DNS Lookup" << endl;
        cout << "2. Port Scanning" << endl;
        cout << "3. Reverse IP Lookup" << endl;
        cout << "4. Ping IPv4 Address" << endl;
        cout << "5. Exit" << endl;
        cout << ">> ";
        cin >> input;
        if (cin.fail()) {
            cerr << "Invalid input. Please enter a valid number." << endl;
            return 1;
        }
        system("clear");
        switch (input) {
            case 1:
                cout << "Enter any valid URL: ";
                cin >> hostname;
                dns_lookup(hostname);
                cout << "  " << endl;
                break;
            case 2:
                cout << "Enter any valid IP address : ";
                cin >> ip;
                cout << "Start Port : ";
                cin >> start_port;
                cout << "End Port : ";
                cin >> end_port;
                cout << "Scanning ports on IP : " << ip << endl;
                reverse_ip_lookup(ip);
                for (int port = start_port; port <= end_port; ++port) {
                    if (is_port_open(ip, port)) {
                        cout << "Port " << port << " is open!" << endl;
                    }
                }
                cout << "  " << endl;
                break;
            case 3:
                cout << "Enter any valid IP address : ";
                cin >> ip;
                reverse_ip_lookup(ip);
                cout << "  " << endl;
                break;
            case 4:
                cout << "Enter an IP address : ";
                cin >> ip;
                if (is_ip_up(ip)) {
                    cout << "The IP " << ip << " is up!" << endl;
                } else {
                    cout << "The IP " << ip << " is down or unreachable." << endl;
                }
                cout << "  " << endl;
                break;
            case 5:
                return false;
                break;
            default:
                cout << "Invalid option. Please select 1 or 5 (Exit)." << endl;
                break;
        }
    }
    cout << "Thanks for using yesscout :)" << endl;
    return 0;
}
