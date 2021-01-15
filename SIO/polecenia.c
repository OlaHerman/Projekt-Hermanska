#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "../cJSON/cJSON.h"

#include "polecenia.h"
#include "mapa.h"

char * make_request(char *url)
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

int info(char *token) 
{
    char *url1 = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/qwerty_7";

    make_request(url1);
}

int move(char *token) 
{
    char *url1 = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move/qwerty_7";

    make_request(url1);
}

int explore(char *token) 
{
    char *url1 = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/qwerty_7";
    
    make_request(url1);
}

int right(char *token) 
{
    char *url1 = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/qwerty_/right";

    make_request(url1);
}

int left(char *token) 
{
    char *url1 = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/qwerty_7/left";

    make_request(url1);
}