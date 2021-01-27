#ifndef _polecenia_h
#define _polecenia_h

#include "mapa.h"


static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp);
char *make_request(char *url);

Pole * info(Dane *M);
Pole * ruch(Pole *P, Dane *M);
Pole * odkryj(Pole *P, Dane2 *ME);
Pole * prawo(Pole *P, Dane *M);
Pole * lewo(Pole *P, Dane *M);

#endif