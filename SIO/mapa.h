#ifndef _mapa_h
#define _mapa_h

#include "polecenia.h"

#define MAX_SIZE 100

typedef struct _Memory
{
    char *response;
    size_t size;
} Memory;

typedef struct _Mapa
{
    char *status;
    char *name;
    int current_x;
    int current_y;
    char *current_session;
    char *direction;
    int step;
    char *field_type;
    char *field_bonus;
    
} Mapa;

typedef struct _Mapa_explore
{
    char *status;
    char *type[3];
    int x[3];
    int y[3];
} Mapa_explore;

typedef struct _Pole
{
    char index[MAX_SIZE][MAX_SIZE];
    int current_x;
    int current_y;
} Pole;

static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp);
Pole *stworz();
Pole * dodaj(Pole *P, Mapa *M);
void wypisz(Pole *P);
Mapa * wczytaj_json(Mapa *M, const char *const dane);
Mapa_explore *wczytaj_json_explore(Mapa_explore *M, const char *const dane);



#endif