# include <stdio.h>
# include <time.h>
# include "e101.h"

extern "C" int init(int d_lev);
extern "C" int connect_to_server( char server_addr[15],int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);

int main (){
   init(1);
   //connects to server with the ip address 192.168.1.2
   char serv[24] = {'1','9','2','.','1','6','8','.','1','.','2'};
   connect_to_server(serv, 1024);
   //sends a message to the connected server
   char message[24] = {'p','l','e','a','s','e'};
   send_to_server(message);
   //receives message from the connected server
   //message[24];
   receive_from_server(message);
   send_to_server(message);

return 0;}
