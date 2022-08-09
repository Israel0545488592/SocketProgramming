#include "urlib.h"
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

/* more documentation in header file, urlib */

int main(int argc, char* argv[]){

  // SET UP

  int client, bytes_count = 0, bytes_read = 1;          // socket-fd and counters
  struct sockaddr_in cli_name;                          // socket address
  char URI[300] = {0}, hostname[100] = {0}, *IP_addr;
  char buffer[1000] = {0};                              // memory for recived data

  if (argc < 2){

    printf("u need to supply: URL\n");
    return -1;
  }
  if (URLparser(argv[1], hostname, URI) == -1){

    printf("problomes with parsing URL, maybe wrong format\n");
  }
  printf("\nhostname: %s\nURI: %s\n", hostname, URI);

  IP_addr = lookup(hostname);


  // http get message and a buffer for the response
  char message[500] = "";
  sprintf(message, "GET /%s HTTP/1.1\r\nHost: %s\r\nContent-Type: text/plain\r\n\r\n", URI, hostname);
  printf("\nthe http request: %s\n", message);
  fflush(stdout);


  // opening output file to write results
  FILE *file = fopen("out.html", "w");
  if (file == NULL) {
    
    printf("Error! Could not open file\n"); 
    return -1;
  }


  printf("Client is alive and establishing socket connection.\n");
  

  client = socket(AF_INET, SOCK_STREAM, 0);           // conection oriented socket for TCP comunication
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

  if (send(client, message, sizeof(message) +1, 0) == -1){  // send the HTTP GET message

    printf("transmission went wrong");
    return -1;
  }

  while (bytes_read > 0){   // read response

    bzero((char*) buffer, sizeof(buffer));
    bytes_read = recv(client, &buffer, sizeof(buffer), 0);
    
    // write to file
    fwrite(&buffer, sizeof(char), sizeof(buffer) / sizeof(char), file);
    bytes_count += bytes_read;
  }

  printf("%d bytes have been writen to an output text file\n", bytes_count);


  printf("Exiting now.\n");
  close(client);
  fclose(file);
  exit(0);
}