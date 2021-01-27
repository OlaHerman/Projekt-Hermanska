#ifndef _MAPA_H
#define _MAPA_H

#define MAX_SIZE 100

#define N 5
#define C 2

#define W 12
#define K 9

typedef struct _Memory
{
    char *response;
    size_t size;
} Memory;

typedef struct _Dane
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

} Dane;

typedef struct _Dane2
{
    char *status;
    char *type[3];
    int x[3];
    int y[3];
} Dane2;

typedef struct _Pole
{
    char **index;
    int delta_x;
    int delta_y;
    int zajety_x;
    int zajety_y;
    char *kierunek;
    char *rodzaj_pola;
    char *field_bonus;
    int rozmiar_x;
    int rozmiar_y;
    int krok;
} Pole;

typedef struct _Rozmiar
{
    int X, Y;

} Rozmiar;


Pole *stworz(Dane *M);
Pole *powieksz(Pole *P);
int sprawdz_granice(Pole *P);
Pole *powieksz_E(Pole *P);
Pole *powieksz_N(Pole *P);
Pole *powieksz_W(Pole *P);
Pole *powieksz_S(Pole *P);

Pole *aktualizuj_kierunek(Pole *P, Dane *M);
Pole *aktualizuj_ruch(Pole *P, Dane *M);
Pole *aktualizuj_odkryj(Pole *P, Dane2 *ME);

Dane *wczytaj_json(Dane *M, const char *const dane);
Dane2 *wczytaj_json_explore(Dane2 *ME, const char *const dane);

void wypisz(Pole *P);
void zapisz(Pole *P, char *file);

void zwolnij_dane(Dane *M);
void zwolnij_dane2(Dane2 *ME);
void zwolnij_pole(Pole *P);

#endif