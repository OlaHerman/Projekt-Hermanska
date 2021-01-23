#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "../../cJSON/cJSON.h"

#include "mapa.h"
#include "polecenia.h"
#include "logika.h"

/*
Legenda znaków na mapie:
. - nieodkryte pole
g - trawa
s - piasek
w - ściana

G - trawa zajęta przez czołg
S - piasek zajęty przez czołg
*/


Pole *stworz(Mapa *M)
{
    int i,j;
    Pole *nowe;
    nowe = (Pole*) malloc(sizeof(Pole));
    nowe->index = (char**) malloc(sizeof(char*) * N);
        for(i=0;i<N;i++)
        nowe->index[i] = (char*) malloc(sizeof(char) * N);
    
    nowe->rozmiar_x = N;
    nowe->rozmiar_y = N;

    for(i=0;i<nowe->rozmiar_x;i++)
    {
        for(j=0;j<nowe->rozmiar_y;j++)
            nowe->index[i][j] = '.'; 
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

Pole * powieksz(Pole *P){
    Pole *nowe;
    if(strcmp(P->direction, "E") == 0)
        nowe = powieksz_E(P);
    else if(strcmp(P->direction, "N") == 0)
        nowe = powieksz_N(P);
    else if(strcmp(P->direction, "W") == 0)
        nowe = powieksz_W(P);
    else if(strcmp(P->direction, "S") == 0)
        nowe = powieksz_S(P);

    zwolnij_pole(P);

    return nowe;
}

Pole *powieksz_E(Pole *P){
    Pole *nowe;
    nowe = (Pole*) malloc(sizeof(Pole));
    int i, j;
    nowe->rozmiar_x = 2*P->rozmiar_x;
    nowe->rozmiar_y = P->rozmiar_y;
    nowe->delta_x = P->delta_x;
    nowe->delta_y = P->delta_y;

    nowe->index = (char**) malloc(sizeof(char*) * nowe->rozmiar_y);
        for(i=0;i<nowe->rozmiar_y;i++)
        nowe->index[i] = (char*) malloc(sizeof(char) * nowe->rozmiar_x);

    for(i=0;i<nowe->rozmiar_y;i++){
        for(j=0;j<nowe->rozmiar_x;j++){
            if(j<P->rozmiar_x){
                //printf("Wypełniam wcześniej znane pole x:%d y:%d %c\n ",j,i, P->index[i][j]);
                nowe->index[i][j] = P->index[i][j];
            }
            else{
                nowe->index[i][j] = '.';
                //printf("Wypełnilem puste pole x:%d y:%d - %c\n",j,i,nowe->index[i][j] );
            }
        }
    }

    nowe->current_x = P->current_x;
    nowe->current_y = P->current_y;
    nowe->direction = P->direction;
    nowe->field_type = P->field_type;
    nowe->field_bonus = P->field_bonus;

    return nowe;
}

Pole *powieksz_N(Pole *P){
    Pole *nowe;
    nowe = (Pole*) malloc(sizeof(Pole));
    int i, j;
    nowe->rozmiar_x = P->rozmiar_x;
    nowe->rozmiar_y = 2*P->rozmiar_y;
    nowe->delta_x = P->delta_x;
    nowe->delta_y = P->delta_y;

    nowe->index = (char**) malloc(sizeof(char*) * nowe->rozmiar_y);
        for(i=0;i<nowe->rozmiar_y;i++)
        nowe->index[i] = (char*) malloc(sizeof(char) * nowe->rozmiar_x);

    for(i=0;i<nowe->rozmiar_y;i++){
        for(j=0;j<nowe->rozmiar_x;j++){
            if(i<P->rozmiar_y){
                //printf("Wypełniam wcześniej znane pole x:%d y:%d %c\n ",j,i, P->index[i][j]);
                nowe->index[i][j] = P->index[i][j];
            }
            else{
                nowe->index[i][j] = '.';
                //printf("Wypełnilem puste pole x:%d y:%d - %c\n",j,i,nowe->index[i][j] );
            }
        }
    }

    nowe->current_x = P->current_x;
    nowe->current_y = P->current_y;
    nowe->direction = P->direction;
    nowe->field_type = P->field_type;
    nowe->field_bonus = P->field_bonus;

    return nowe;
}

Pole *powieksz_W(Pole *P){
    Pole *nowe;
    nowe = (Pole*) malloc(sizeof(Pole));
    int i, j;
    nowe->rozmiar_x = 2*P->rozmiar_x;
    nowe->rozmiar_y = P->rozmiar_y;
    nowe->delta_x = P->delta_x - P->rozmiar_x;
    nowe->delta_y = P->delta_y;

    nowe->index = (char**) malloc(sizeof(char*) * nowe->rozmiar_y);
        for(i=0;i<nowe->rozmiar_y;i++)
        nowe->index[i] = (char*) malloc(sizeof(char) * nowe->rozmiar_x);

    for(i=0;i<nowe->rozmiar_y;i++){
        for(j=0;j<nowe->rozmiar_x;j++){
            if(j>=P->rozmiar_x){
                //printf("Wypełniam wcześniej znane pole x:%d y:%d %c\n ",j,i, P->index[i][j-size_x]);
                nowe->index[i][j] = P->index[i][j-P->rozmiar_x];
            }
            else{
                nowe->index[i][j] = '.';
                //printf("Wypełnilem puste pole x:%d y:%d - %c\n",j,i,nowe->index[i][j] );
            }
        }
    }

    nowe->current_x = P->current_x + P->rozmiar_x;
    nowe->current_y = P->current_y;
    nowe->direction = P->direction;
    nowe->field_type = P->field_type;
    nowe->field_bonus = P->field_bonus;

    return nowe;
}

Pole *powieksz_S(Pole *P){
    Pole *nowe;
    nowe = (Pole*) malloc(sizeof(Pole));
    int i, j;
    nowe->rozmiar_x = P->rozmiar_x;
    nowe->rozmiar_y = 2*P->rozmiar_y;
    nowe->delta_x = P->delta_x;
    nowe->delta_y = P->delta_y - P->rozmiar_y;

    nowe->index = (char**) malloc(sizeof(char*) * nowe->rozmiar_y);
        for(i=0;i<nowe->rozmiar_y;i++)
        nowe->index[i] = (char*) malloc(sizeof(char) * nowe->rozmiar_x);

    for(i=0;i<nowe->rozmiar_y;i++){
        for(j=0;j<nowe->rozmiar_x;j++){
            if(i>=P->rozmiar_y){
                //printf("Wypełniam wcześniej znane pole x:%d y:%d %c\n ",j,i, P->index[i-size_y][j]);
                nowe->index[i][j] = P->index[i-P->rozmiar_y][j];
            }
            else{
                nowe->index[i][j] = '.';
                //printf("Wypełnilem puste pole x:%d y:%d - %c\n",j,i,nowe->index[i][j] );
            }
        }
    }

    nowe->current_x = P->current_x;
    nowe->current_y = P->current_y + P->rozmiar_y;
    nowe->direction = P->direction;
    nowe->field_type = P->field_type;
    nowe->field_bonus = P->field_bonus;

    return nowe;
}


int check_border(Pole *P){
    if(P->current_x == P->rozmiar_x -1 ||P->current_x == 0||P->current_y == P->rozmiar_y -1||P->current_y == 0)//Trzeba powiekszyć w stronę P->direction
        return 1;
    else 
        return 0;
}

Pole *update_direction(Pole *P, Mapa *M)
{
    Pole *nowe;
    nowe = P;
    nowe->direction = M->direction;

    return nowe;
}

Pole *update_move(Pole *P, Mapa *M){
    int X, Y, x, y, p;
    char *new_field = M->field_type;
    char *old_field = P->field_type;

    Pole *nowe;
    nowe = P;
    
    X = M->current_x - P->delta_x;//Pole na które ruszył się czołg
    Y = M->current_y - P->delta_y;
    x = P->current_x;//Pole na którym wcześniej stał czołg
    y = P->current_y;
    //printf("Poprzednie pole: x:%d y:%d to %s\n", x, y, old_field);
    //printf("Nowe pole: x:%d y:%d to %s\n", X, Y, new_field);

    if(X == x & Y == y){//Tank move failed
        //printf("Czołg przywalił w ścianę\n");
        if(strcmp(nowe->direction, "N")==0){
            nowe->index[Y+1][X] = 'w';
        }
        else if(strcmp(nowe->direction, "E")==0){
            nowe->index[Y][X+1] = 'w';
        }
        else if(strcmp(nowe->direction, "S")==0){
            nowe->index[Y-1][X] = 'w';
        }
        else if(strcmp(nowe->direction, "W")==0){
            nowe->index[Y][X-1] = 'w';
        }
    }

    else if(X != x || Y != y){//Tank move successful
        nowe->current_y = Y;
        nowe->current_x = X;
        nowe->field_type = new_field;

        if(strcmp(new_field, "grass") == 0){
            nowe->index[Y][X] = 'G';
            //printf("Pole x:%d y:%d to teraz G\n", X, Y);
            nowe->field_type = new_field;
        }
        else if(strcmp(new_field, "sand") == 0){
            nowe->index[Y][X] = 'S';
            //printf("Pole x:%d y:%d to teraz S\n", X, Y);
            nowe->field_type = new_field;
        }
        if(strcmp(old_field, "grass") == 0){
            nowe->index[y][x] = 'g';
            //printf("Pole x:%d y:%d zamioniono z G na g\n", x, y);
        }
        else if(strcmp(old_field, "sand") == 0){
            nowe->index[y][x] = 's';
            //printf("Pole x:%d y:%d zamioniono z S na s\n", x, y);
        }
    }
    return nowe;
}

Pole *update_explore(Pole *P, Mapa_explore *ME){
    int i,j, x, y;
    char *field_type;
    Pole *nowe;
    nowe = P;
    for(i=0;i<3;i++){
        strcpy(field_type, ME->type[i]);
        
        x = ME->x[i] - P->delta_x;
        y = ME->y[i] - P->delta_y;
        //printf("%d pole przede mną to x:%d y:%d typ: %s\n",i+1, x, y, ME->type[i]);
        if(strcmp(field_type, "grass") == 0)
            nowe->index[y][x] = 'g';
        else if(strcmp(field_type, "sand") == 0)
            nowe->index[y][x] = 's';
        else if(strcmp(field_type, "wall") == 0)
            nowe->index[y][x] = 'w';
    }
    return nowe;
}


void wypisz(Pole *P)
{
    int i,j,Y;
    for(i=0;i<P->rozmiar_y;i++)
    {
        Y = P->rozmiar_y-i-1;
        for(j = 0;j<P->rozmiar_x;j++)
            printf("%c  ", P->index[Y][j]);
    printf("\n\n");
    }
    if(strcmp(P->direction, "S") == 0)
        printf("Tank heading down.\n");
    else if(strcmp(P->direction, "N") == 0)
        printf("Tank heading up.\n");
    else if(strcmp(P->direction, "W") == 0)
        printf("Tank heading left.\n");
    else if(strcmp(P->direction, "E") == 0)
        printf("Tank heading right.\n");
    printf("\n");
}

void zapisz(Pole *P, char *file)
{
    FILE * fin = fopen(file, "w");
    int i,j,Y;
    fprintf(fin,"%d %d\n", P->rozmiar_y, P->rozmiar_x);
    fprintf(fin, "%s\n", P->direction);
    for(i=0; i<P->rozmiar_y; i++){
        Y = P->rozmiar_y-i-1;
        for(j=0;j<P->rozmiar_x;j++){
        fprintf(fin, "%c ",P->index[Y][j]);
        }
    fprintf(fin, "\n");
    }
    fclose(fin);
    printf("Map saved.\n");
}

/*Pole *wczytaj_mape(char *file){
    FILE *fin = fopen(file, "r");

    if (fin == NULL) {
        printf("BŁĄD! Nie moge otworzyc pliku: %s.\n", file);
        exit(-1);
    }

    int i,j;
    char *s;
    Pole *wczytane = (Pole*) malloc(sizeof(Pole));
    
    fscanf(fin, "%d %d", &wczytane->rozmiar_y, &wczytane->rozmiar_x);
    
    fscanf(fin, "%s", s);
    
    wczytane->direction = (char*) malloc(sizeof(char));
    wczytane->direction = s;
    
    wczytane->index = (char**) malloc(sizeof(char*) * wczytane->rozmiar_y);
        for(i=0;i<wczytane->rozmiar_y;i++)
        wczytane->index[i] = (char*) malloc(sizeof(char) * wczytane->rozmiar_x);
    

    for(i=0;i<wczytane->rozmiar_y;i++)
        for(j=0;j<wczytane->rozmiar_x;j++){
            fscanf(fin, "%s", s);
            printf("Co to za pole? %s\n", s);
            if(s == "v"){
            wczytane->index[i][j] = 'v';
            }
            

            printf("lol2\n");
            printf("%s\n", wczytane->index[i][j]);
            printf("lol3\n");
            if(strcmp(wczytane->index[i][j], "G") == 0){
                wczytane->current_y = i;
                wczytane->current_x = j;
                wczytane->field_type = (char*) malloc(sizeof(char) * (strlen("grass")+1));
                wczytane->field_type = "grass";
            }
            else if(strcmp(wczytane->index[i][j], "S") == 0){
                wczytane->current_y = i;
                wczytane->current_x = j;
                wczytane->field_type = (char*) malloc(sizeof(char) * (strlen("sand")+1));
                wczytane->field_type = "sand";
            }
        }
        wczytane->field_bonus = (char*) malloc(sizeof(char));
        wczytane->field_bonus = "";
    printf("lol\n");
    
    return wczytane;
}*/

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
    int i = 0;
    const cJSON *file = NULL;
    const cJSON *status =NULL;
    const cJSON *payload =NULL;
    const cJSON *list =NULL;
    
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

        nowa->x[i]=x->valueint;
        
        nowa->y[i]=y->valueint;
        nowa->type[i] = (char*) malloc(sizeof(char) * strlen((type->valuestring) + 1));
        strcpy(nowa->type[i], type->valuestring);
        i++;
    }
    return nowa;
}

void zwolnij_mape(Mapa *M){
    free(M);
}

void zwolnij_mape_explore(Mapa_explore *ME){
    free(ME);
}

void zwolnij_pole(Pole *P){
    int i;
    for(i=0;i<P->rozmiar_y;i++)
        free(P->index[i]);
    free(P->index);
    free(P);
}