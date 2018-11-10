#include "client.h"
#include"Message.h"
#include <cstdlib>

Client::Client(int my_port,int p)
{
port = my_port;
 so = new Socket(port);

 memset((char*)&servaddr, 0, sizeof(servaddr));//resetting the struct

 servaddr.sin_family = AF_INET; //Describes the protocol type
 servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
 servaddr.sin_port = htons(p);//setting a port number

}


Client::Client(int port,char * server_ip, int server_port)
{


 struct hostent *hp;     /* host information */
 hp = gethostbyname(server_ip);
 if (!hp) {
	fprintf(stderr, "could not obtain address of %s\n", server_ip);
	return;
  }


 so = new Socket(port);

 memset((char*)&servaddr, 0, sizeof(servaddr));

 servaddr.sin_family = AF_INET;
 servaddr.sin_port = htons(server_port);

 memcpy((void *)&servaddr.sin_addr, hp->h_addr_list[0], hp->h_length);

}


void Client::DoOperation(vector<string> v)
{

  // char* fmessage;
//
// char *y = new char[x.length() + 1]; // or
// char y[100];
//
// std::strcpy(y, x.c_str());
  struct sockaddr_in peer_address;

  for (int i = 0; i<v.size();i++)
  {
    char* fmessage = new char[v[i].length()+1];
    strcpy(fmessage,v[i].c_str());
    // fmessage = v[i].c_str();
	sleep(1.0);
    so->Send(fmessage, servaddr);
    //so->Recieve(fmessage,peer_address);
  }


	// int n;
  //       ss.fd = so->s;
  //       ss.events = POLLIN;
  //       n = poll(&ss, 1, 1);
  //       if(n == 0 || n == -1)
  //       {
  //           printf("Timeout!!\n");
  //           //exit(-1);
  //        }
  //  	else
	// {
  // 	 so->Recieve(message, peer_address);
  // 	}


}
string Client::read_pic(string img) // reads the pic and base64 encodes it and it takes the name of the pic to be sent
{
	//cout<<"IN READ_PIC"<<endl;
  Message m;
  string message;
  string name = img + ".jpg";
  string marshalled;
  ifstream is (name.c_str(), ifstream::binary);
	// get length of file:
	is.seekg (0, is.end);
	int length = is.tellg();
	is.seekg (0, is.beg);
	char * buffer = new char [length];
	//cout << "Reading " << length << " characters...  \n";
	// read data as a block:
  if (is)
	{
    is.read (buffer,length);
/*
    if (is)
      std::cout << "all characters read successfully \n";
    else
      std::cout << "error: only " << is.gcount() << " could be read";
*/
    is.close();
  }
  marshalled=m.base64_encode(reinterpret_cast<const unsigned char *> (buffer),length);
	//cout<<"END OF READ"<<endl;
return marshalled;
}
vector<string> Client::fragment(string encoded)
{
	//cout<<"Start of Frag"<<endl;
  string temp="";
  int counter = 0;
  int id=0;
  int total_size=0;
  vector<string> vect_temp, frag_message;
  cout<<"Size of array "<<encoded.size()<<"\n";
  total_size = ceil(encoded.size()/18000);
  cout<<" total size " << total_size <<"\n";
  for (int i =0 ; i<encoded.size();i++)
  {
    temp += encoded[i];
    counter++;
    if (counter == 18000)
    {
      id++;
      temp = decToHexa(id) + decToHexa(total_size) + temp;
      vect_temp.push_back(temp);
	  //cout<<" ID : "<<decToHexa(id)<<"\n";
	  //cout<<" TS : "<<decToHexa(total_size)<<"\n";
      //cout<<"Size of the fragment is "<<temp.size()<<"\n";
      temp="";
      counter = 0;
    }
    if(i == encoded.size()-1)
    {
      id++;
      temp = decToHexa(id) + decToHexa(total_size) + temp;
      vect_temp.push_back(temp);
  //    cout<<"Size of the rest of the pic is "<< temp.size()<<"\n";
      temp="";
    }

  }

frag_message = vect_temp;
//cout<<"end of frag"<<endl;
cout << frag_message.size() << endl;

return frag_message;

}


string Client::decToHexa(int n)
{
    string temp="";
    // char array to store hexadecimal number
    string hexaDeciNum;
    // counter for hexadecimal number array
    int i = 0;
    while(n!=0)
    {    // temporary variable to store remainder
        int temp  = 0;
        // storing remainder in temp variable.
        temp = n % 16;
        // check if temp < 10
        if(temp < 10)
        {
          hexaDeciNum[i] = temp + 48;
          i++;
        }
        else
        {
            hexaDeciNum[i] = temp + 55;
            i++;
        }

        n = n/16;
    }
    // printing hexadecimal number array in reverse order
    for(int j=i-1; j>=0; j--)
        temp +=hexaDeciNum[j];

    // cout<<temp;
    // cout<<"\n";
    // cout<<temp.length()<<"\n";
    int z = temp.length();
    for (int i = 0; i< (8-z);i++)
    {
      temp = "x"+temp;
    }
    return temp;
}
void Client::send(string name)
{

	string msg;
	vector<string> docs;
	msg = read_pic(name);
	docs = fragment(msg);
/*	for(int i=0;i<docs.size();i++)
{
	cout<<docs[i].length()<<endl;
}
*/
	DoOperation(docs);

}
