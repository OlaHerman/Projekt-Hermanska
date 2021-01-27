#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "../../cJSON/cJSON.h"

#include "mapa.h"
#include "polecenia.h"
#include "logika.h"

Pole *stworz(Dane *M) //Tworzy i przydziela pamięć dla struktury Pole
{
    int i, j;
    Pole *nowe;
    nowe = (Pole *)malloc(sizeof(Pole));
    nowe->index = (char **)malloc(sizeof(char *) * N);
    for (i = 0; i < N; i++)
        nowe->index[i] = (char *)malloc(sizeof(char) * N);

    nowe->rozmiar_x = N;
    nowe->rozmiar_y = N;

    for (i = 0; i < nowe->rozmiar_x; i++)
    {
        for (j = 0; j < nowe->rozmiar_y; j++)
            nowe->index[i][j] = '.';
    }
    nowe->delta_x = M->current_x - C;
    nowe->delta_y = M->current_y - C;

    nowe->zajety_x = C;
    nowe->zajety_y = C;

    nowe->kierunek = M->direction;
    nowe->rodzaj_pola = M->field_type;
    nowe->field_bonus = M->field_bonus;
    nowe->krok = M->step;

    if (strcmp(nowe->rodzaj_pola, "grass") == 0)
        nowe->index[C][C] = 'G';
    if (strcmp(nowe->rodzaj_pola, "sand") == 0)
        nowe->index[C][C] = 'S';

    return nowe;
}

Pole *powieksz(Pole *P)
{
    Pole *nowe;
    if (strcmp(P->kierunek, "E") == 0)
        nowe = powieksz_E(P);
    else if (strcmp(P->kierunek, "N") == 0)
        nowe = powieksz_N(P);
    else if (strcmp(P->kierunek, "W") == 0)
        nowe = powieksz_W(P);
    else if (strcmp(P->kierunek, "S") == 0)
        nowe = powieksz_S(P);

    zwolnij_pole(P);

    return nowe;
}

Pole *powieksz_E(Pole *P)
{
    Pole *nowe;
    nowe = (Pole *)malloc(sizeof(Pole));
    int i, j;
    nowe->rozmiar_x = 2 * P->rozmiar_x;
    nowe->rozmiar_y = P->rozmiar_y;
    nowe->delta_x = P->delta_x;
    nowe->delta_y = P->delta_y;

    nowe->index = (char **)malloc(sizeof(char *) * nowe->rozmiar_y);
    for (i = 0; i < nowe->rozmiar_y; i++)
        nowe->index[i] = (char *)malloc(sizeof(char) * nowe->rozmiar_x);

    for (i = 0; i < nowe->rozmiar_y; i++)
    {
        for (j = 0; j < nowe->rozmiar_x; j++)
        {
            if (j < P->rozmiar_x)
                nowe->index[i][j] = P->index[i][j];

            else
                nowe->index[i][j] = '.';
        }
    }

    nowe->zajety_x = P->zajety_x;
    nowe->zajety_y = P->zajety_y;
    nowe->kierunek = P->kierunek;
    nowe->rodzaj_pola = P->rodzaj_pola;
    nowe->field_bonus = P->field_bonus;
    nowe->krok = P->krok;

    return nowe;
}

Pole *powieksz_N(Pole *P)
{
    Pole *nowe;
    nowe = (Pole *)malloc(sizeof(Pole));
    int i, j;
    nowe->rozmiar_x = P->rozmiar_x;
    nowe->rozmiar_y = 2 * P->rozmiar_y;
    nowe->delta_x = P->delta_x;
    nowe->delta_y = P->delta_y;

    nowe->index = (char **)malloc(sizeof(char *) * nowe->rozmiar_y);
    for (i = 0; i < nowe->rozmiar_y; i++)
        nowe->index[i] = (char *)malloc(sizeof(char) * nowe->rozmiar_x);

    for (i = 0; i < nowe->rozmiar_y; i++)
    {
        for (j = 0; j < nowe->rozmiar_x; j++)
        {
            if (i < P->rozmiar_y)
                nowe->index[i][j] = P->index[i][j];

            else
                nowe->index[i][j] = '.';
        }
    }

    nowe->zajety_x = P->zajety_x;
    nowe->zajety_y = P->zajety_y;
    nowe->kierunek = P->kierunek;
    nowe->rodzaj_pola = P->rodzaj_pola;
    nowe->field_bonus = P->field_bonus;
    nowe->krok = P->krok;

    return nowe;
}

Pole *powieksz_W(Pole *P)
{
    Pole *nowe;
    nowe = (Pole *)malloc(sizeof(Pole));
    int i, j;
    nowe->rozmiar_x = 2 * P->rozmiar_x;
    nowe->rozmiar_y = P->rozmiar_y;
    nowe->delta_x = P->delta_x - P->rozmiar_x;
    nowe->delta_y = P->delta_y;

    nowe->index = (char **)malloc(sizeof(char *) * nowe->rozmiar_y);
    for (i = 0; i < nowe->rozmiar_y; i++)
        nowe->index[i] = (char *)malloc(sizeof(char) * nowe->rozmiar_x);

    for (i = 0; i < nowe->rozmiar_y; i++)
    {
        for (j = 0; j < nowe->rozmiar_x; j++)
        {
            if (j >= P->rozmiar_x)
                nowe->index[i][j] = P->index[i][j - P->rozmiar_x];

            else
                nowe->index[i][j] = '.';
        }
    }

    nowe->zajety_x = P->zajety_x + P->rozmiar_x;
    nowe->zajety_y = P->zajety_y;
    nowe->kierunek = P->kierunek;
    nowe->rodzaj_pola = P->rodzaj_pola;
    nowe->field_bonus = P->field_bonus;
    nowe->krok = P->krok;

    return nowe;
}

Pole *powieksz_S(Pole *P)
{
    Pole *nowe;
    nowe = (Pole *)malloc(sizeof(Pole));
    int i, j;
    nowe->rozmiar_x = P->rozmiar_x;
    nowe->rozmiar_y = 2 * P->rozmiar_y;
    nowe->delta_x = P->delta_x;
    nowe->delta_y = P->delta_y - P->rozmiar_y;

    nowe->index = (char **)malloc(sizeof(char *) * nowe->rozmiar_y);
    for (i = 0; i < nowe->rozmiar_y; i++)
        nowe->index[i] = (char *)malloc(sizeof(char) * nowe->rozmiar_x);

    for (i = 0; i < nowe->rozmiar_y; i++)
    {
        for (j = 0; j < nowe->rozmiar_x; j++)
        {
            if (i >= P->rozmiar_y)
                nowe->index[i][j] = P->index[i - P->rozmiar_y][j];

            else
                nowe->index[i][j] = '.';
        }
    }

    nowe->zajety_x = P->zajety_x;
    nowe->zajety_y = P->zajety_y + P->rozmiar_y;
    nowe->kierunek = P->kierunek;
    nowe->rodzaj_pola = P->rodzaj_pola;
    nowe->field_bonus = P->field_bonus;
    nowe->krok = P->krok;

    return nowe;
}

int sprawdz_granice(Pole *P)
{
    if (P->zajety_x == P->rozmiar_x - 1 || P->zajety_x == 0 || P->zajety_y == P->rozmiar_y - 1 || P->zajety_y == 0) //Trzeba powiekszyć w stronę P->kierunek
        return 1;
    else
        return 0;
}

Pole *aktualizuj_kierunek(Pole *P, Dane *M)
{
    Pole *nowe;
    nowe = P;
    nowe->kierunek = M->direction;
    nowe->krok = M->step;

    return nowe;
}

Pole *aktualizuj_ruch(Pole *P, Dane *M)
{
    int X, Y, x, y, p;
    char *nowe_pole = M->field_type;
    char *stare_pole = P->rodzaj_pola;

    Pole *nowe;
    nowe = P;

    X = M->current_x - P->delta_x; //Pole na które ruszył się czołg
    Y = M->current_y - P->delta_y;
    x = P->zajety_x; //Pole na którym wcześniej stał czołg
    y = P->zajety_y;
    nowe->krok = M->step;

    if (X == x & Y == y) //Czołg się nie ruszył
    {
        if (strcmp(nowe->kierunek, "N") == 0)
        {
            nowe->index[Y + 1][X] = 'w';
        }
        else if (strcmp(nowe->kierunek, "E") == 0)
        {
            nowe->index[Y][X + 1] = 'w';
        }
        else if (strcmp(nowe->kierunek, "S") == 0)
        {
            nowe->index[Y - 1][X] = 'w';
        }
        else if (strcmp(nowe->kierunek, "W") == 0)
        {
            nowe->index[Y][X - 1] = 'w';
        }
    }

    else if (X != x || Y != y) //Czołg się ruszył
    {
        nowe->zajety_y = Y;
        nowe->zajety_x = X;
        nowe->rodzaj_pola = nowe_pole;

        if (strcmp(nowe_pole, "grass") == 0)
        {
            nowe->index[Y][X] = 'G';
            nowe->rodzaj_pola = nowe_pole;
        }
        else if (strcmp(nowe_pole, "sand") == 0)
        {
            nowe->index[Y][X] = 'S';
            nowe->rodzaj_pola = nowe_pole;
        }
        if (strcmp(stare_pole, "grass") == 0)
            nowe->index[y][x] = 'g';

        else if (strcmp(stare_pole, "sand") == 0)
            nowe->index[y][x] = 's';
    }
    return nowe;
}

Pole *aktualizuj_odkryj(Pole *P, Dane2 *ME)
{
    int i, j, x, y;
    char *rodzaj_pola;
    Pole *nowe;
    nowe = P;
    for (i = 0; i < 3; i++)
    {
        strcpy(rodzaj_pola, ME->type[i]);

        x = ME->x[i] - P->delta_x;
        y = ME->y[i] - P->delta_y;

        if (strcmp(rodzaj_pola, "grass") == 0)
            nowe->index[y][x] = 'g';
        else if (strcmp(rodzaj_pola, "sand") == 0)
            nowe->index[y][x] = 's';
        else if (strcmp(rodzaj_pola, "wall") == 0)
            nowe->index[y][x] = 'w';
    }
    return nowe;
}

void wypisz(Pole *P)
{
    int i, j, Y;
    for (i = 0; i < P->rozmiar_y; i++)
    {
        Y = P->rozmiar_y - i - 1;
        for (j = 0; j < P->rozmiar_x; j++)
            printf("%c  ", P->index[Y][j]);
        printf("\n\n");
    }
    printf("Czołg skierowany w stronę %s\n\n", P->kierunek);
}

void zapisz(Pole *P, char *file)
{
    FILE *fin = fopen(file, "w");
    int i, j, Y;
    fprintf(fin, "%d %d\n", P->rozmiar_y, P->rozmiar_x);
    fprintf(fin, "%s\n", P->kierunek);
    for (i = 0; i < P->rozmiar_y; i++)
    {
        Y = P->rozmiar_y - i - 1;
        for (j = 0; j < P->rozmiar_x; j++)
        {
            fprintf(fin, "%c ", P->index[Y][j]);
        }
        fprintf(fin, "\n");
    }
    fclose(fin);
    printf("Mapa zapisana.\n");
}

Dane *wczytaj_json(Dane *M, const char *const dane)
{
    Dane *nowa;
    nowa = (Dane *)malloc(sizeof(Dane));
    const cJSON *file = NULL;
    const cJSON *status;
    const cJSON *payload;
    const cJSON *name;
    const cJSON *current_x;
    const cJSON *current_y;
    const cJSON *current_session;
    const cJSON *direction = NULL;
    const cJSON *step;
    const cJSON *field_type;
    const cJSON *field_bonus;

    cJSON *dane_cjson = cJSON_Parse(dane);

    status = cJSON_GetObjectItemCaseSensitive(dane_cjson, "status");
    nowa->status = status->valuestring;

    payload = cJSON_GetObjectItemCaseSensitive(dane_cjson, "payload");
    cJSON_ArrayForEach(file, payload)
    {
        cJSON *name = cJSON_GetObjectItemCaseSensitive(payload, "name");
        nowa->name = name->valuestring;

        cJSON *current_x = cJSON_GetObjectItemCaseSensitive(payload, "current_x");
        nowa->current_x = current_x->valueint;

        cJSON *current_y = cJSON_GetObjectItemCaseSensitive(payload, "current_y");
        nowa->current_y = current_y->valueint;

        cJSON *current_session = cJSON_GetObjectItemCaseSensitive(payload, "current_session");
        nowa->current_session = current_session->valuestring;

        cJSON *direction = cJSON_GetObjectItemCaseSensitive(payload, "direction");
        nowa->direction = direction->valuestring;

        cJSON *step = cJSON_GetObjectItemCaseSensitive(payload, "step");
        nowa->step = step->valueint;

        cJSON *field_type = cJSON_GetObjectItemCaseSensitive(payload, "field_type");
        nowa->field_type = field_type->valuestring;

        cJSON *field_bonus = cJSON_GetObjectItemCaseSensitive(payload, "field_bonus");
        nowa->field_bonus = field_bonus->valuestring;
    }
    return nowa;
}

Dane2 *wczytaj_json_explore(Dane2 *M, const char *const dane)
{
    Dane2 *nowa = NULL;
    nowa = (Dane2 *)malloc(sizeof(Dane2));
    int i = 0;
    const cJSON *file = NULL;
    const cJSON *status = NULL;
    const cJSON *payload = NULL;
    const cJSON *list = NULL;

    cJSON *dane_cjson = cJSON_Parse(dane);

    status = cJSON_GetObjectItemCaseSensitive(dane_cjson, "status");
    nowa->status = status->valuestring;

    payload = cJSON_GetObjectItemCaseSensitive(dane_cjson, "payload");

    list = cJSON_GetObjectItemCaseSensitive(payload, "list");

    cJSON_ArrayForEach(file, list)
    {

        cJSON *x = cJSON_GetObjectItemCaseSensitive(file, "x");
        cJSON *y = cJSON_GetObjectItemCaseSensitive(file, "y");
        cJSON *type = cJSON_GetObjectItemCaseSensitive(file, "type");

        nowa->x[i] = x->valueint;

        nowa->y[i] = y->valueint;
        nowa->type[i] = (char *)malloc(sizeof(char) * strlen((type->valuestring) + 1));
        strcpy(nowa->type[i], type->valuestring);
        i++;
    }
    return nowa;
}

void zwolnij_dane(Dane *M)
{
    free(M);
}

void zwolnij_dane2(Dane2 *ME)
{
    free(ME);
}

void zwolnij_pole(Pole *P)
{
    int i;
    for (i = 0; i < P->rozmiar_y; i++)
        free(P->index[i]);
    free(P->index);
    free(P);
}