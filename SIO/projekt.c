#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
 
#define W 12
#define K 9
typedef struct _Macierz 
{
    int r;
    int c;
    int **tab;
}Macierz;
 
Macierz* wczytaj(int a, int b) 
{
    int i,j;
    Macierz *m=(Macierz*) malloc(sizeof(Macierz));
    // fscanf(fin, "%d", &(*m).r);
    // fscanf(fin, "%d", &(*m).c);
    m->r=a;
    m->c=b;
    m->tab = (int**) malloc(sizeof(int*) * m->r);
    for (i=0;i<m->r;i++)
        m->tab[i] = (int*) malloc(sizeof(int) * m->c);
 
    return m;
}
 
void wypisz(Macierz *m) 
{
    int i, j;
    for (i = 0; i < m->r; i++) 
    {
    printf("[ ");
        for (j=0; j < m->c; j++) 
        {
            printf("%d ", m->tab[i][j]);
        }
            printf("]\n");
    }
    printf("\n");
}
 
void zwolnij(Macierz *m)
{
    for (int i = 0; i <m->r; i++) 
    free(m->tab[i]);
    free(m->tab);
    free(m);
}
 
typedef struct _Memory
{
    char *response;
    size_t size;
} Memory;
 
static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp)
{
    /* to jest rzeczywista liczba bajtów przekazanych przez curl */
    size_t realsize = size * nmemb;
 
    /* jawnie konwertujemy (void*) na naszą strukturę, bo wiemy, że będziemy ją tutaj otrzymywać */
    Memory *mem = (Memory *) userp;
 
    char *ptr = NULL;
 
    /* Sprawdzamy czy pierwszy raz wywołujemy funkcję i trzeba zaalokować pamięć po raz pierwszy,
    czy trzeba zrobić reallokację (która kopiuje automatycznie starą zawartość w nowe miejsce) */
    if (mem->response != NULL)
        ptr = realloc(mem->response, mem->size + realsize + 1);
    else
        ptr = malloc(mem->size + realsize + 1);
 
    if (ptr == NULL)
        return 0; /* brak pamięci! */
 
    /* teraz zapamiętujemy nowy wskaźnik i doklejamy na końcu dane przekazane przez curl w 
       obszarze pamięci wskazywanym przez data */
    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0; // to na końcu dodajemy bo to w końcu string, i zawsze powinien się skończyć!
 
    return realsize;
}
 
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
        curl_easy_setopt(curl, CURLOPT_HEADER, 1L);
 
        /* to jest funkcja 'callback', która będzie wywołana przez curl gdy odczyta on kawałek danych
       ta funkcja musi mieć wywołanie zgodne z wymaganiami, które możesz sprawdzić tutaj:
       https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
 
        /* to jest adress struktury, który będzie przekazywany do naszej funkcji 'callback',
       do tej struktury nasz funkcja 'callback' będzie dopisywać wynik */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
 
        /* Wykonaj zapytanie 'synchronicznie', to znaczy następna linijka kodu nie wykona się
       dopóki nie nadejdzie odpowiedź z serwera. */
        res = curl_easy_perform(curl);
 
        /* Sprawdzamy czy wystapił jakis błąd? */
        if (res != CURLE_OK)
            fprintf(stderr, "Błąd! curl_easy_perform() niepowodzenie: %s\n", curl_easy_strerror(res));
        else
        {
            printf("%s", chunk.response);
        }
 
        /* zawsze po sobie sprzątaj */
        free(chunk.response);
        curl_easy_cleanup(curl);
    }
}

int info(char *token) 
{
 
    // http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/token
    char *url = (char*)malloc(sizeof(char*));
    strcpy(url,"http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info");
    strcat(url,"/");
    strcat(url,token);
    make_request(url);
    free(url);
    return 0;
}
 
int move(char *token) {
    // http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move/token
    char *url = (char*)malloc(sizeof(char*));
    strcpy(url,"http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move");
    strcat(url,"/");
    strcat(url,token);
    make_request(url);
    free(url);
    return 0;
}
 
int rotate(char *token, char *direction)
{
    // http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/token/direction
    char *url = (char*)malloc(sizeof(char*));
    strcpy(url,"http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate");
    strcat(url,"/");
    strcat(url,token);
    strcat(url,"/");
    strcat(url,direction);
    make_request(url);
    free(url);
    return 0;
}
 
int main(int argc, char **argv)
{
    Macierz *a;
    a=wczytaj(9,12);
    /*X-unknown field ; W - WALL; G-GRASS; S-SAND;
    KONCOWA MACIERZ
     W W W W W W W W W
     W G G G G W G G W
     W G W W G W G W W
     W G G W G W G G W
     W G G G G G G G W
     W G W W G W G G W
     W G W S G W G G W
     W G W W G W G W W
     W G S W G W S S W
     W G S G G W G G W
     W G G G G W G G w
     W w W W W W W W W*/
 
    wypisz(a);
    char *swiat=(char*)malloc(sizeof(char*));
    strcpy(swiat,"qwerty_7");
    // char *url;
    if (argc==1)
    {
        printf("podaj operacje!\n");
        printf("Move - \"M\"; Rotate - \"Rr/Rl\"; Info - \"info\"\n");
    }
    else
    for (int i=1;i<argc;i++)
    {
        if(strcmp(argv[i],"M")==0)
        move(swiat);
        else if(strcmp(argv[i],"Rr")==0)
        rotate(swiat,"right");
        else if(strcmp(argv[i],"Rl")==0)
        rotate(swiat,"left");
        else if(strcmp(argv[i],"info")==0)
        info(swiat);
        else
        {
        printf("podaj operacje!\n");
        printf("Move - \"M\"; Rotate - \"Rr/Rl\"; Info - \"info\"\n");
        }
    }
    // char *url = argc < 2 ? "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/qwerty_7" : argv[1];
 
    return 0;
}