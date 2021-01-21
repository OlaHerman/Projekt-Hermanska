#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "../../cJSON/cJSON.h"

#include "mapa.h"
#include "polecenia.h"


int main(char argc, char **argv){
  Mapa *M;
  Mapa_explore *ME;
  Pole *P;

  int i;
  char *mapa = "test.txt";
  char buffer[2048];
  char *a = "qwerty_7.json";

  info(a);
  FILE *f;
  f = fopen(a, "r"); 
  fread(buffer,1,2048,f);
  fclose(f);
  M = wczytaj_json(M, buffer);
  P = stworz(M);
  zwolnij_mape(M);
  wypisz(P);
/*
  explore(a);
  f = fopen(a, "r"); 
  fread(buffer,1,2048,f);
  fclose(f);
  ME = wczytaj_json_explore(ME, buffer);
  P = update_explore(P, ME);
  //printf("%d %d %s\n", ME->x[0], ME->y[0], ME->type[0]);
  wypisz(P);

  return 0;
*/
  // printf("%d %d\n", P->delta_x, P->delta_y);
  // for(i=0;i<1;i++){
  // P = powieksz(P);
  // wypisz(P);
  // }
  // return 0;

  for(i=0;i<argc;i++){
    if(strcmp(argv[i], "L") == 0){
      left(a);
      f = fopen(a, "r"); 
      fread(buffer,1,2048,f);
      fclose(f);
      M = wczytaj_json(M, buffer);
      P = update_direction(P, M);
      wypisz(P);
    }
    else if(strcmp(argv[i], "R") == 0){
      right(a);
      f = fopen(a, "r"); 
      fread(buffer,1,2048,f);
      fclose(f);
      M = wczytaj_json(M, buffer);
      P = update_direction(P, M);
      zwolnij_mape(M);
      wypisz(P);
    }
    else if(strcmp(argv[i], "M") == 0){
      move(a);
      f = fopen(a, "r"); 
      fread(buffer,1,2048,f);
      fclose(f);
      M = wczytaj_json(M, buffer);
      P = update_move(P, M);
      zwolnij_mape(M);
      wypisz(P);  
    }
    else if(strcmp(argv[i], "E") == 0){
      explore(a);
      f = fopen(a, "r"); 
      fread(buffer,1,2048,f);
      fclose(f);
      ME = wczytaj_json_explore(ME, buffer);
      P = update_explore(P, ME);
      zwolnij_mape_explore(ME);
      wypisz(P); 
    }
    if(check_border(P) == 1)
      P = powieksz(P);
  }
  zapisz(P , mapa);  
  zwolnij_pole(P);
  return 0;
}