#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "../../cJSON/cJSON.h"

#include "mapa.h"
#include "polecenia.h"

/*
Legenda znaków na mapie:
v - nieodkryte pole
g - trawa
s - piasek
w - ściana

G - trawa zajęta przez czołg
S - piasek zajęty przez czołg
*/


Pole *stworz(Mapa *M)
{
    Pole *nowe;
    nowe = (Pole*) malloc(sizeof(Pole));

    nowe->rozmiar_x = N;
    nowe->rozmiar_y = N;

    for(int i=0;i<nowe->rozmiar_x;i++)
    {
        for(int j=0;j<nowe->rozmiar_y;j++)
            nowe->index[i][j] = 'v'; 
    }
    nowe->delta_x = M->current_x - C;
    nowe->delta_y = M->current_y - C;

    nowe->current_x = C;
    nowe->current_y = C;

    nowe->direction = M->direction;

    nowe->field_type = M->field_type;

    nowe->field_bonus = M->field_bonus;

    if(strcmp(nowe->field_type, "grass") == 0)
        nowe->index[C][C] = 'G';
    if(strcmp(nowe->field_type, "sand") == 0)
        nowe->index[C][C] = 'S';


    return nowe;
}

Pole * update_direction(Pole *P, Mapa *M)
{
    Pole *nowe;
    nowe = P;
    nowe->direction = M->direction;


    return nowe;
}


void wypisz(Pole *P)
{
    for(int i=0;i<P->rozmiar_x;i++)
    {
        for(int j = 0;j<P->rozmiar_y;j++)
            printf("%c   ", P->index[i][j]);
    printf("\n\n");
    }
    if(strcmp(P->direction, "S") == 0)
        printf("Czołg skierowany w dół.\n");
    else if(strcmp(P->direction, "N") == 0)
        printf("Czołg skierowany w górę.\n");
    else if(strcmp(P->direction, "W") == 0)
        printf("Czołg skierowany w lewo.\n");
    else if(strcmp(P->direction, "E") == 0)
        printf("Czołg skierowany w prawo.\n");
    printf("\n");
}

void zapisz(Pole *P, char *file)
{
    FILE * fin = fopen(file, "w");

    for(int i=0; i<P->rozmiar_x; i++){
        for(int j=0;j<P->rozmiar_y;j++){
        fprintf(fin, "%c ",P->index[i][j]);
        }
    fprintf(fin, "\n");
    }
    fclose(fin);
}

Mapa * wczytaj_json(Mapa *M, const char *const dane)
{
    Mapa *nowa;
    nowa = (Mapa*) malloc(sizeof(Mapa));
    const cJSON *lol = NULL;
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
    nowa->status = (char*) malloc(sizeof(char) * (strlen(status->valuestring)+1));
    nowa->status = status->valuestring;

    payload = cJSON_GetObjectItemCaseSensitive(dane_cjson, "payload");
        cJSON_ArrayForEach(lol, payload)
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

Mapa_explore *wczytaj_json_explore(Mapa_explore *M, const char *const dane)
{
    Mapa_explore *nowa = NULL;
    nowa = (Mapa_explore*) malloc(sizeof(Mapa_explore));
    int i =0;
    const cJSON *lol = NULL;
    const cJSON *status =NULL;
    const cJSON *payload =NULL;
    const cJSON *list =NULL;
    
    cJSON *dane_cjson = cJSON_Parse(dane);

    status = cJSON_GetObjectItemCaseSensitive(dane_cjson, "status");
    nowa->status = status->valuestring;

    payload = cJSON_GetObjectItemCaseSensitive(dane_cjson, "payload");

    list = cJSON_GetObjectItemCaseSensitive(payload, "list");

    cJSON_ArrayForEach(lol, list)
    {
        
        cJSON *x = cJSON_GetObjectItemCaseSensitive(lol, "x");
        cJSON *y = cJSON_GetObjectItemCaseSensitive(lol, "y");
        cJSON *type = cJSON_GetObjectItemCaseSensitive(lol, "type");

        nowa->x[i]=x->valueint;
        
        nowa->y[i]=y->valueint;
        nowa->type[i] = (char*) malloc(sizeof(char) * strlen((type->valuestring) + 1));
        strcpy(nowa->type[i], type->valuestring);
        i++;
    }
    return nowa;
}