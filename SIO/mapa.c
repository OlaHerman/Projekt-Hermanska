#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "../cJSON/cJSON.h"

#include "mapa.h"
#include "polecenia.h"

static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp)
{
    
    size_t realsize = size * nmemb;

    Memory *mem = (Memory *) userp;

    char *ptr = NULL;

    if (mem->response != NULL)
        ptr = realloc(mem->response, mem->size + realsize + 1);
    else
        ptr = malloc(mem->size + realsize + 1);

    if (ptr == NULL)
        return 0; 

    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0;

    return realsize;
}

Pole *stworz()
{
    Pole *nowe;
    nowe = (Pole*) malloc(sizeof(Pole));
    for(int i=0;i<100;i++)
    {
        for(int j=0;j<100;j++)
            nowe->index[i][j] = '0'; 
    }
    
    return nowe;
}

Pole * dodaj(Pole *P, Mapa *M)
{
    Pole *nowe = P;

    



    return nowe;
}

void wypisz(Pole *P)
{
    Pole *po;

    for(int i=50;i<70;i++)
    {
        for(int j = 50;j<70;j++)
            printf("%c   ", po->index[i][j]);
    printf("\n");
    }
}

Mapa * wczytaj_json(Mapa *M, const char *const dane)
{
    Mapa *nowa;
    const cJSON *lol = NULL;
    const cJSON *status;
    const cJSON *payload;
    const cJSON *name;
    const cJSON *current_x;
    const cJSON *current_y;
    const cJSON *current_session;
    const cJSON *direction;
    const cJSON *step;
    const cJSON *field_type;
    const cJSON *field_bonus;

    cJSON *dane_cjson = cJSON_Parse(dane);

    status = cJSON_GetObjectItemCaseSensitive(dane_cjson, "status");
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