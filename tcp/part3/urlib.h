#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int URLparser(char*, char*, char*);   // URL -> hostname and URI
char* lookup(char*);                  // hostname -> IP