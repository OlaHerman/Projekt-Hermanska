#ifndef _polecenia_h
#define _polecenia_h
#include "mapa.h"

char * make_request(char *url);
int info(char *token);
int move(char *token);
int explore(char *token);
int right(char *token);
int left(char *token);


#endif