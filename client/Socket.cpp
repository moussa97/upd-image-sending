#include"Socket.h"
#include<iostream>

using namespace std;

Socket::Socket(int port)
{
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) //socket creation
	{
        perror("cannot create socket");
        return;
    }

	struct sockaddr_in myaddr;

    
    memset((char *)&myaddr, 0, sizeof(myaddr)); //resisting the struct
    myaddr.sin_family = AF_INET; //Describes the protocol type
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    myaddr.sin_port = htons(port); //setting a port number

    
    if (bind(s, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) //binding the socket to the port number
	{
        perror("bind failed");
        return;
    }

}

void Socket::Send(char* message, sockaddr_in& peer_address)
{
		if (sendto(s, message, strlen(message), 0, (struct sockaddr *)&peer_address, sizeof(peer_address)) < 0) {
        	perror("sendto failed");
        }
}

void Socket::Recieve(char*& message, sockaddr_in& peer_address)
{     
    
    socklen_t addrlen = sizeof(peer_address);
    int recvlen = recvfrom(s, buf, SIZE, 0, (struct sockaddr *)&peer_address, &addrlen);//lenght of recieved message
    printf("received %d bytes\n", recvlen);

    if (recvlen > 0) {
        buf[recvlen] = 0;
        printf("received message: \"%s\"\n", buf);
    }

	message = strdup(buf);


}



