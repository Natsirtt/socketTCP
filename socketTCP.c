#include "socketTCP.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

#include "socketTCP_utils.h"

SocketTCP *creerSocketTCP() {
  SocketTCP *s = allocSocketTCP();
  s->socket = socket(AF_INET, SOCK_STREAM, 0);
  if (s->socket == -1) {
    return NULL;
  }
  return s;
}

char *getLocalName(SocketTCP *socket) {
    return socket->local.name;
}

char *getLocalIP(SocketTCP *socket) {
  return socket->local.ip;
}

int getLocalPort(SocketTCP *socket) {
  return socket->local.port;
}

char *getDistantName(SocketTCP *socket) {
  if (isConnected(socket)) {
    return socket->distant.name;
  }
  return NULL;
}

char *getDistantIP(SocketTCP *socket) {
  if (isConnected(socket)) {
    return socket->distant.ip;
  }
  return NULL;
}

int getDistantPort(SocketTCP *socket) {
  if (isConnected(socket)) {
    return socket->distant.port;
  }
  return -1;
}

int isConnected(SocketTCP *socket) {
  return socket != NULL && socket->distant.port != -1;
}

int connectSocketTCP(SocketTCP *socket, const char *address, int port) {
  struct sockaddr_in in;
  
  if (initSockAddr(address, port, &in) == -1) {
    return -1;
  }
  
  if (socket->distant.name != NULL) {
    free(socket->distant.name);
  }
  
  if ((socket->distant.ip) != NULL) {
    free(socket->distant.ip);
  }
  
  socket->distant = getIdBySockAddr(&in);
  if ((socket->distant.port) == -1) {
    return -1;
  }
  
  return connect(socket->socket, (struct sockaddr *) &in,
                 sizeof(struct sockaddr_in));
}

SocketTCP *creerSocketEcouteTCP(const char *address, int port) {
  struct sockaddr_in in;
  SocketTCP *socket;
  
  if ((socket = creerSocketTCP()) == NULL) {
    return NULL;
  }
  
  //On initialise la socket
  if (initSockAddr(address, port, &in) == -1) {
    return NULL;
  }
  
  //On lie la socket
  if (bind(socket->socket, (struct sockaddr *) &in,
           sizeof(struct sockaddr_in)) == -1) {
  
    return NULL;
  }
  
  //On la déclare en écoute
  if (listen(socket->socket, SIZE_QUEUE) == -1) {
    return NULL;
  }
  
  socket->local = getIdBySockAddr(&in);
  
  return socket;
}

SocketTCP *acceptSocketTCP(SocketTCP *socket) {
  SocketTCP *res = allocSocketTCP(); //On alloue seulement, on ne créé pas, car accept s'en occupe
  struct sockaddr_in in; //Permet de récupérer les infos sur la socket de service
  socklen_t size = sizeof(struct sockaddr_in);
  int service; //La socket de service
  
  if ((service = accept(socket->socket, (struct sockaddr *) &in, &size)) == -1) {
    return NULL;
  }
  
  res->socket = service; //La socket liant les deux machines est la socket de service
  res->local = socket->local; //La machine locale est évidemment la même que celle écoutant
  res->distant = getIdBySockAddr(&in); //On récupère les infos de la machine distante
  return res;
}

int writeSocketTCP(SocketTCP *socket, const void *buff, int length) {
  if (!isConnected(socket)) {
    return -1;
  }
  
  int res;
  if ((res = write(socket->socket, (char *) buff, length)) == -1) {
    return -1;
  }
  
  if (res != length) {
    return -1;
  }
  
  return res;
}

int readSocketTCP(SocketTCP *socket, void *buff, int length) {
  if (!isConnected(socket)) {
    return -1;
  }
  
  return read(socket->socket, (char *) buff, length);
}

int closeSocketTCP(SocketTCP *socket) {
  freeSocketTCP(socket);
  
  return close(socket->socket);
}
