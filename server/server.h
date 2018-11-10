#ifndef SERVER_H
#define SERVER_H
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
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include<vector>
#include<cstring>
#include<string>
#include<fstream>
#include <algorithm>
#include "Message.h"
#include "Socket.h"
#include"math.h"


using namespace std;

class Server
{

private:
        vector < pair <int,string> > x; 
	vector<int> reply;
	int fsize =0;
        int port;
	Socket* s;
	bool FL=true;
public:

	Server(int port);
	void GetRequest();
  	void SendReply(char * message, struct sockaddr_in peer_address);
	void output();
	void write(char* message);
	int hex2dec(string x);
	



};

#endif
