#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "../cJSON/cJSON.h"

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
    char index[100][100];
    int current_x;
    int current_y;
} Pole;

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

Pole *stworz(){
    Pole *nowe;
    nowe = (Pole*) malloc(sizeof(Pole));
    for(int i=0;i<100;i++){
        for(int j=0;j<100;j++)
            nowe->index[i][j] = '0'; 
    }
    
    return nowe;
}

Pole * dodaj(Pole *P, Mapa *M){
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

Mapa * wczytaj_json(Mapa *M, const char *const dane){
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

Mapa_explore *wczytaj_json_explore(Mapa_explore *M, const char *const dane){
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

    cJSON_ArrayForEach(lol, list){
        
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

char * make_request(char *url){
    CURL *curl;
    CURLcode res;
    Memory chunk;
    chunk.size = 0;
    chunk.response = NULL;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        //curl_easy_setopt(curl, CURLOPT_HEADER, 1L);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        res = curl_easy_perform(curl);
        

        if (res != CURLE_OK)
            fprintf(stderr, "Błąd! curl_easy_perform() niepowodzenie: %s\n", curl_easy_strerror(res));
        else
        {
            printf("%s", chunk.response);

            FILE *fin = fopen("qwerty_7.json", "w");
            fprintf(fin,"%s\n", chunk.response);
            fclose(fin);
        }

        free(chunk.response);
        curl_easy_cleanup(curl);
    }
    return 0;
}

int info(char *token) {
char *url1 = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/qwerty_7";

    make_request(url1);
}

int move(char *token) {
char *url1 = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move/qwerty_7";

    make_request(url1);
}

int explore(char *token) {
char *url1 = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/qwerty_7";

    make_request(url1);
}

int right(char *token) {
char *url1 = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/qwerty_/right";

    make_request(url1);
}

int left(char *token) {
char *url1 = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/qwerty_7/left";

    make_request(url1);
}

int main(int argc, char **argv)
{
  char *a = "qwerty_7.json";
  char buffer[2048];
  FILE *f = fopen(a, "r"); 
  fread(buffer,1,2048,f);
  fclose(f);
  Mapa *M;
  Mapa_explore *ME;
    for (int i=1;i<argc;i++){
      if(strcmp(argv[i], "move") == 0){
        move(a);

        M = wczytaj_json(M, buffer);

        //printf("%d %d %s %s %s %s %d %s %s\n", M->current_x, M->current_y, M->status, M->name, M->current_session, M->direction, M->step, M->field_type, M->field_bonus);

        Pole *P = stworz(M);
        wypisz(P);
      }
      if(strcmp(argv[i], "right") == 0){
        right(a);
        M = wczytaj_json(M, buffer);
        //printf("%d %d %s %s %s %s %d %s %s\n", M->current_x, M->current_y, M->status, M->name, M->current_session, M->direction, M->step, M->field_type, M->field_bonus);

        Pole *P = stworz(M);
        wypisz(P);
      }
      if(strcmp(argv[i], "left") == 0){
        left(a);
        M = wczytaj_json(M, buffer);
        //printf("%d %d %s %s %s %s %d %s %s\n", M->current_x, M->current_y, M->status, M->name, M->current_session, M->direction, M->step, M->field_type, M->field_bonus);

        Pole *P = stworz(M);
        wypisz(P);
      }
      if(strcmp(argv[i], "explore") == 0){
        explore(a);
        ME = wczytaj_json_explore(ME, buffer);
        //printf("%d %d %d %d %d %d %s %s %s\n", ME->x[0], ME->x[1], ME->x[2], ME->y[0], ME->y[1], ME->y[2], ME->type[0], ME->type[1], ME->type[2]);

        Pole *P = stworz(M);
        wypisz(P);
      }
      if(strcmp(argv[i], "info") == 0){
        info(a);
        M = wczytaj_json(M, buffer);
        //printf("%d %d %s %s %s %s %d %s %s\n", M->current_x, M->current_y, M->status, M->name, M->current_session, M->direction, M->step, M->field_type, M->field_bonus);

        Pole *P = stworz(M);
        wypisz(P);
      } 
    }
    return 0;
}