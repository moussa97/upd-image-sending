
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

#include "server.h"
using namespace std;



int main(){

	
    Server s(5656);

    s.GetRequest();

    return 0;
}
