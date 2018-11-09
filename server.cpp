#include "server.h"
#include "Message.h"


Server::Server(int p)
{

 port = p;
 s = new Socket(port);

}

void Server::GetRequest()
{

    printf("Listening on port %d.\n",port);
    char * message;
    struct sockaddr_in peer_address; //client address

     while(FL)
     {
        s->Recieve(message, peer_address);
        write(message);
        //SendReply(message, peer_address);
    		if (strcmp(message,"q")==0)
    		{
    			printf("Server closed \n");
    			FL=false;
    			exit(0);

    		}
			  /*sort(x.begin(),x.end());
			  for(int i=1;i<=x.size();i++)
			  {
			  	if(x[i].first == i)
			  		{
			  			continue;
			  		}
			  		else
			  		reply.push_back(i);
			  }
			  for(int i=0;i<reply.size();i++)
			  {
			  	cout<<reply[i]<<endl;
			  }*/
    }
	  output();
}

int Server::hex2dec(string hex)
{
    unsigned long result = 0;
    for (int i=0; i<hex.length(); i++) {
        if (hex[i]>=48 && hex[i]<=57)
        {
            result += (hex[i]-48)*pow(16,hex.length()-i-1);
        } else if (hex[i]>=65 && hex[i]<=70) {
            result += (hex[i]-55)*pow(16,hex.length( )-i-1);
        } else if (hex[i]>=97 && hex[i]<=102) {
            result += (hex[i]-87)*pow(16,hex.length()-i-1);
        }
    }
    return result;
}

void Server::SendReply(char * message, struct sockaddr_in peer_address)
{
     s->Send(message, peer_address);
}

void Server::write(char* message)
{

  string decoded_message = message;
  string s_id="";
  string s_total_size="";
	int total;
  s_id  = decoded_message.substr(0,8); //
	int remove =0;
	for(int i=0;i<s_id.length();i++)
	{
		if(s_id[i]=='x')
			remove++;
	}	
  int id ;
	s_id = s_id.erase(0,remove);
	id = hex2dec(s_id);
	remove=0;
 
	
  s_total_size = decoded_message.substr(8,8); // 
		for(int i=0;i<s_total_size.length();i++)
	{
		if(s_total_size[i]=='x')
			remove++;
	}	
	s_total_size = s_total_size.erase(0,remove);
	total = hex2dec(s_total_size);
	
	cout<<"total "<<total<<endl;
	cout<<"id "<<id<<endl;	
	//total = atoi(s_total_size.c_str());
	/*cout<<" "<<total<<endl;
	cout<<"id "<<id<<endl;*/
  decoded_message = decoded_message.erase(0,16);
  Message m;
  string norm = m.base64_decode(decoded_message); //
  x.push_back(make_pair(id,norm));
	int temp;
	temp = fsize;
  fsize++;
	cout<<"fsize "<<fsize<<endl;
	//cout<<"Le"<<decoded_message.length()<<"\n";
	if (fsize == total)
	{
		FL = false;
	}
		
}

void Server::output()
{	
	
	  sort(x.begin(),x.end());	
	for(int i=0;i<x.size();i++)
{
	cout<<"ana hena"<<endl;
	cout<<x[i].first<<endl;
}
	string out;
  for(int i=0; i<fsize; i++)
	{
		out = out+ x[i].second;
	}
  ofstream myfile ("hatem.jpg",ofstream::binary);
  if (myfile.is_open())
  {
    myfile << out;
    myfile.close();
  }
  else cout << "Unable to open file";
} 


