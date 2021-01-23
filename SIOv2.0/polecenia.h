#ifndef _polecenia_h
#define _polecenia_h

#include "mapa.h"

static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp);
char *make_request(char *url);

int info(char *token);
int move(char *token);
int explore(char *token);
int right(char *token);
int left(char *token);

#endif