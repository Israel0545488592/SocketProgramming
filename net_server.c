#include <sys/types.h>
#include <unistd.h>          
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>     
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SIM_LENGTH 1000

#define PORT 1337

int main(void){

  //set up

  int server; 
  int connect_sock; 
  struct sockaddr_in serv_name; 
  socklen_t len = sizeof(serv_name);
  int count;
  
  server = socket(AF_INET, SOCK_STREAM, 0);  
    
  bzero(&serv_name, sizeof(serv_name));   // zero out address variable to prevent miss-haps
  serv_name.sin_family = AF_INET;         // setting up the IP
  serv_name.sin_port = htons(PORT);       // network byte order (PORT)          

  bind(server, (struct sockaddr *)&serv_name, sizeof(serv_name));        
  listen(server, 1); 

  len = sizeof(serv_name);
  
  connect_sock = accept(server, (struct sockaddr *)&serv_name, &len);

  for (count = 1; count <= SIM_LENGTH; count++){
    
    write(connect_sock, &count, 4);
    printf("Server has written %d to socket.\n", count);
  }

  close(connect_sock); 
  close(server);
}
