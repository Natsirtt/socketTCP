#include "socketTCP_utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define SHORT_BUFFER_LENGTH 10 //Suffisant pour un port
#define BUFFER_LENGTH 4096

SocketTCP *allocSocketTCP() {
  SocketTCP *s_sock;
  s_sock = (SocketTCP *) malloc(sizeof(SocketTCP));
  if (s_sock != NULL) {
    s_sock->socket = -1;
    s_sock->local.name = NULL;
    s_sock->local.ip = NULL;
    s_sock->local.port = -1;
    s_sock->distant.name = NULL;
    s_sock->distant.ip = NULL;
    s_sock->distant.port = -1;
  }
  return s_sock;
}

/**
 * Libère les ressources utilisées par un id.
 */
void _freeIdTCP(id *i) {
  if (i->name != NULL) {
    free(i->name);
  }
    
  if (i->ip != NULL) {
    free(i->ip);
  }
}

void freeSocketTCP(SocketTCP *socket) {
  _freeIdTCP(&(socket->local));
  _freeIdTCP(&(socket->distant));
  free(socket);
}

int initSockAddr(const char *adresse, int port, struct sockaddr_in *in) {
  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  memset(in, 0, sizeof(struct sockaddr_in));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_ADDRCONFIG;
  char p[SHORT_BUFFER_LENGTH];
  snprintf(p, SHORT_BUFFER_LENGTH, "%d", port);
  
  struct addrinfo *res;
  if (getaddrinfo(adresse, p, &hints, &res) != 0) {
    return -1;
  }
  
  memcpy(in, res->ai_addr, sizeof(struct sockaddr_in));
  return 0;
}

id getIdBySockAddr(const struct sockaddr_in *in) {
  id res;
  char nameHost[BUFFER_LENGTH];
  char ipHost[BUFFER_LENGTH];
  char serv[SHORT_BUFFER_LENGTH];
  int ret;
  
  ret = getnameinfo((struct sockaddr *) in, sizeof(struct sockaddr_in),
                    nameHost, BUFFER_LENGTH, serv, SHORT_BUFFER_LENGTH,
                    NI_NUMERICSERV);

  if (ret != 0) {
    res.port = -1;
    return res;
  }
  
  ret = getnameinfo((struct sockaddr *) in, sizeof(struct sockaddr_in),
                    ipHost, BUFFER_LENGTH, serv, SHORT_BUFFER_LENGTH,
                    NI_NUMERICHOST);
  
  if (ret != 0) {
    res.port = -1;
    return res;
  }
  
  //Nom
  int nameLength = strlen(nameHost);
  res.name = (char *) malloc(sizeof(char) * nameLength + 1);
  strncpy(res.name, nameHost, nameLength);
  res.name[nameLength] = 0;
  //Port
  res.port = atoi(serv);
  //IP
  int ipLength = strlen(ipHost);
  res.ip = (char *) malloc(sizeof(char) * ipLength + 1);
  strncpy(res.ip, ipHost, ipLength);
  res.ip[ipLength] = 0;
  return res;
}
