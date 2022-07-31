#include "nslookup.h"
#include <sys/types.h>
#include <unistd.h>          
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>    
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <sys/types.h> 
#include <arpa/inet.h>

#define PORT 80 

int main(int argc, char* argv[]){

  // SET UP

  //socket variables
  int client;
  struct sockaddr_in cli_name;

  if (argc < 3){

    printf("u need to supply: URL and URI");
    return -1;
  }
  char* IP_addr = lookup(argv[1]);

  int bytes_count = 0;
  int bytes_read = 1;

  // http get message and a buffer for the response
  char message[300] = "GET /";
  strncat(message, argv[2], strlen(argv[2]));
  strncat(message, " HTTP/1.1", strlen(argv[2]));

  // memory for recived messages
  char buffer[1000] = {0};

  // opening output file to write results
  FILE *file = fopen("out.html", "w");
  if (file == NULL) {
        printf("Error! Could not open file\n"); 
        return -1;
  }


  printf("Client is alive and establishing socket connection.\n");
  

  client = socket(AF_INET, SOCK_STREAM, 0);
  if (client < 0){

    perror ("Error opening channel");
    close(client);
    exit(1);
  }
      
  // pre prosseing

  bzero(&cli_name, sizeof(cli_name));                   // zero out address variable to prevent miss-haps
  cli_name.sin_family = AF_INET;                        // setting up the IP
  cli_name.sin_addr.s_addr = inet_addr(IP_addr);        // network byte order (IP)
  cli_name.sin_port = htons(PORT);                      // network byte order (PORT)


  if (connect(client, (struct sockaddr *)&cli_name, sizeof(cli_name)) < 0){
    
    perror ("Error establishing communications");
    close(client);
    exit(1);
  }

  if (send(client, message, sizeof(message) +1, 0) == -1){  // the http get message

    printf("transmission went wrong");
    return -1;
  }

  while (bytes_read > 0){

    bzero((char*) buffer, sizeof(buffer));
    bytes_read = recv(client, &buffer, sizeof(buffer), 0);
    //read(client, &bytes_read, 4);
    fwrite(&buffer, sizeof(char), sizeof(buffer) / sizeof(char), file);
    bytes_count += bytes_read;
  }

  printf("%d bytes have been writen to an output text file\n", bytes_count);


  printf("Exiting now.\n");
  close(client);
  fclose(file);
  exit(0);
} 
