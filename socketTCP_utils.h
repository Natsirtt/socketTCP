#ifndef SOCKET_TCP_UTILS
#define SOCKET_TCP_UTILS

/**
 * Bibliothèque de fonctions utilitaires pour la bibliothèque de fonctions
 * socketTCP.
 */

#include "socketTCP.h"
#include <sys/socket.h>
#include <netdb.h>

#define STRING_LENGTH 

/**
 * Alloue un espace memoire SocketTCP et retourne le pointeur.
 * Retourne NULL si une erreur d'allocation est apparue.
 */
SocketTCP *allocSocketTCP();

/**
 * Libère les ressources utilisées par une socket.
 */
void freeSocketTCP(SocketTCP *socket);

/**
 * Remplit le champs de la structure "in" en fonction de l'adresse et
 * du port donnés.
 * Le paramètre adresse peut contenir soit une adresse IPV4 au format
 * décimal pointé soit un nom de machine.
 * La fonction retourne 0 si tout s'est bien passé, -1 sinon (adresse non
 * valide).
 */
int initSockAddr(const char *adresse, int port, struct sockaddr_in *in);

/**
 * Retourne une structure id avec le nom, l'adresse IP et le port initialisés
 * à partir d'une structure sockaddr_in.
 * Remplit le port de l'id à -1 si une erreur est apparue.
 */
id getIdBySockAddr(const struct sockaddr_in *in);

#endif
