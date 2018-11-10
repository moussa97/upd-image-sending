#ifndef CLIENT_H
#define CLIENT_H
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
#include <poll.h>
#include<string>
#include<cstring>
#include <fstream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<iomanip>
#include "Socket.h"
#include "Message.h"

class Client
{

private:
  struct sockaddr_in servaddr;
  int port; // my port
	Socket* so;
	struct pollfd ss;
  string encoded;
  vector<string> frag_message;
public:
  bool check=true;
  Client(int my_port,int server_port); //Testing on Same Machine
  Client(int my_port,char * server_ip, int server_port); //Testing on different machines
  // void DoOperation(char * message);
  void DoOperation(vector <string> v);
  string read_pic(string img); // reads the pic and base64 encodes it and it takes the name of the pic to be sent
  vector<string> fragment(string marshal);
  string decToHexa(int n);
  void send(string name); 
	
};

#endif
