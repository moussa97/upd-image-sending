
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include<string>

#include "client.h"
using namespace std;


int main(){


    string ip;
    printf("Please enter Server IP Address: ");
    cin >> ip;
    char * ip_add = strdup(ip.c_str());
    // user port my port then the ip then the server port;
    //Client c(8080,ip_add,5656);
    cin.ignore();
    Client c(8080,ip_add,5656); 
    c.send("girl");
/*
	string img = "gjgg";//jhhjjhjhhjhjasdgahhjahjahjahahjajh
	string imgafter = c.read_pic(img.c_str());
	vector<string> v;
	v = c.fragment(imgafter);
	c.DoOperation(v);

    char * message;
    string inp;
	//bool x = true;
    while(1){

      printf("Enter Message: ");
      std::getline(std::cin,inp);
	//	message = "hi";
	// message = strdup(inp.c_str());
	  c.DoOperation(message);

    }
*/
    return 0;
}
