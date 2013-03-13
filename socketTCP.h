#ifndef SOCKET_TCP
#define SOCKET_TCP

#define SIZE_QUEUE 10

typedef struct {
  char *name;
  char *ip;
  int port;
} id;

typedef struct {
  int socket;
  id local;
  id distant;
} SocketTCP;

/**
 * Créé une SocketTCP (Socket BSD) pour une communication TCP et retourne
 * le pointeur sur cette SocketTCP.
 * Retourne NULL si la création de la socket à échoué.
 */
SocketTCP *creerSocketTCP();

/**
 * Retourne le nom local de la SocketTCP si elle est connectée.
 * Retourne NULL si elle n'est pas connectée.
 */
char *getLocalName(SocketTCP *socket);

/**
 * Retourne l'IP locale de la SocketTCP si elle est connectée.
 * Retourne NULL si elle n'est pas connectée.
 */
char *getLocalIP(SocketTCP *socket);

/**
 * Retourne le port local sur lequel la SocketTCP est connectée.
 * Retourne -1 si la socket n'est pas connectée.
 */
int getLocalPort(SocketTCP *socket);

/**
 * Retourne le nom de la machine distante sur laquelle la SocketTCP est
 * connectée.
 * Retourne -1 si la socket n'est pas connectée.
 */
char *getDistantName(SocketTCP *socket);

/**
 * Retourne l'adresse IP distante sur laquelle la SocketTCP est connectée.
 * Retourne NULL si elle n'est pas connectée.
 */
char *getDistantIP(SocketTCP *socket);

/**
 * retourne le port distant sur laquelle la SocketTCP est connectée.
 * Retourne -1 si la socket n'est pas connectée.
 */
int getDistantPort(SocketTCP *socket);

/**
 * Renvoi 1 si la socket est connectée, 0 sinon.
 */
int isConnected(SocketTCP *socket);

/**
 * Se connecte sur une machine distante dont l'adresse et le port sont donnés
 * en paramètre. L'adresse peut être donnée sous forme de nom ou sous
 * forme décimale pointée.
 * Retourne 0 si la connection est étable, -1 sinon.
 * La structure SocketTCP passée en paramètre est mise à jour. 
 */
int connectSocketTCP(SocketTCP *socket, const char *address, int port);

/**
 * Créé une socket d'écoute et l'attache à l'addresse et au port donnés
 * en paramètre.
 */
SocketTCP *creerSocketEcouteTCP(const char *adress, int port);

/**
 * Attend une connexion sur la socket d'écoute passée en paramètre.
 * Alloue puis retourne un pointeur sur SocketTCP correspondant à la
 * socket de service de cette connexion.
 * La fonction est bloquante jusqu'à ce qu'une connexion soit établie.
 * S'il y a eu une erreur, la fonction renvoie NULL
 */
SocketTCP *acceptSocketTCP(SocketTCP *socket);

/**
 * Ecrit sur socket un bloc d'octets buffer de taille length et retourne
 * la taille des données écrites.
 * Si une erreur à eu lieu, -1 est renvoyé.
 */
int writeSocketTCP(SocketTCP *socket, const void *buff, int length);

/**
 * Lit sur socket un bloc d'octet de taille au plus length dans buffer.
 * Retourne la taille des données réellements lues.
 * Si une erreur à eu lieu, -1 est renvoyé.
 */
int readSocketTCP(SocketTCP *socket, void *buff, int length);

/**
 * Ferme la connexion dans les deux sens et libère la SocketTCP.
 * Retourne -1 en cas d'erreur.
 */
int closeSocketTCP(SocketTCP *socket);

#endif
