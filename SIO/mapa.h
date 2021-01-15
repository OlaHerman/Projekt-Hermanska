#ifndef _MAPA_H
#define _MAPA_H

#include "polecenia.h"

#define MAX_SIZE 100

#define N 5

#define C 2

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
    char index[N][N];
    int delta_x;
    int delta_y;
    int current_x;
    int current_y;
    char *direction;
    char *field_type;
    char*field_bonus;
    int rozmiar_x;
    int rozmiar_y;
} Pole;

void zapisz(Pole *P, char *file);
Pole *stworz(Mapa *M);
Pole * update_direction(Pole *P, Mapa *M);
void wypisz(Pole *P);
Mapa * wczytaj_json(Mapa *M, const char *const dane);
Mapa_explore *wczytaj_json_explore(Mapa_explore *M, const char *const dane);



#endif