#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "../../cJSON/cJSON.h"

#include "polecenia.h"
#include "mapa.h"

static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;

    Memory *mem = (Memory *)userp;

    char *ptr = NULL;

    if (mem->response != NULL)
        ptr = realloc(mem->response, mem->size + realsize + 1);
    else
        ptr = malloc(mem->size + realsize + 1);

    if (ptr == NULL)
    {
        return 0;
    }

    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0;

    return realsize;
}

char *make_request(char *url)
{
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

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            fprintf(stderr, "Błąd! curl_easy_perform() niepowodzenie: %s\n", curl_easy_strerror(res));
        else
            return chunk.response;
        
        curl_easy_cleanup(curl);
    }
    return 0;
}

Pole * info(Dane *M)
{
    Pole *nowe;
    char *url1 = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/qwerty_7";
    char *json;
    json = make_request(url1);
    M = wczytaj_json(M, json);
    nowe = stworz(M);
    free(json);
    zwolnij_dane(M);

    return nowe;
}

Pole * ruch(Pole *P, Dane *M)
{
    Pole *nowe;
    char *url1 = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move/qwerty_7";
    char *json;
    json = make_request(url1);
    M = wczytaj_json(M, json);
    nowe = aktualizuj_ruch(P, M);
    zwolnij_dane(M);
    free(json);

    return nowe;
}

Pole * odkryj(Pole *P, Dane2 *ME)
{
    Pole *nowe;
    char *url1 = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/qwerty_7";
    char *json_explore;
    json_explore = make_request(url1);
    ME = wczytaj_json_explore(ME, json_explore);
    nowe = aktualizuj_odkryj(P,ME);
    zwolnij_dane2(ME);
    free(json_explore);

    return nowe;
}

Pole * prawo(Pole *P, Dane *M)
{
    Pole *nowe;
    char *url1 = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/qwerty_7/right";
    char *json;
    json = make_request(url1);
    M = wczytaj_json(M, json);
    nowe = aktualizuj_kierunek(P, M);
    zwolnij_dane(M);
    free(json);

    return nowe;
}

Pole * lewo(Pole *P, Dane *M)
{
    Pole *nowe;
    char *url1 = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/qwerty_7/left";
    char *json;
    json = make_request(url1);
    M = wczytaj_json(M, json);
    nowe = aktualizuj_kierunek(P, M);
    zwolnij_dane(M);
    free(json);

    return nowe;
}