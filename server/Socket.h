#ifndef SOCKET_H
#define SOCKET_H
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

class Socket
{
	private:
		int s; //socket
		const static int SIZE = 20000; //buffer size
		char buf[SIZE];
		
	public:
		Socket(int port);
		void Send(char* message, sockaddr_in& peer_address); 
		void Recieve(char*& message, sockaddr_in& peer_address);
		//~Socket();
		

};

#endif
