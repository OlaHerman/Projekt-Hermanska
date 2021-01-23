#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "../../cJSON/cJSON.h"

#include "logika.h"
#include "polecenia.h"
#include "mapa.h"

Pole *RM(Pole *SIO, char *token, Mapa *M, char *buffer, int x, int y){
  Pole *nowe;
  FILE *f;
  int X, Y;
  nowe = SIO;

  if(x == SIO->current_x & y == SIO->current_y)
    return nowe;

  right(token);
  f = fopen(token, "r"); 
  fread(buffer,1,2048,f);
  fclose(f);
  M = wczytaj_json(M, buffer);
  nowe = update_direction(nowe, M);
  zwolnij_mape(M);

  X = nowe->current_x;
  Y = nowe->current_y;

  move(token);
  f = fopen(token, "r"); 
  fread(buffer,1,2048,f);
  fclose(f);
  M = wczytaj_json(M, buffer);
  nowe = update_move(nowe, M);
  zwolnij_mape(M);
  wypisz(nowe);

  if(check_border(nowe) == 1)
    nowe = powieksz(nowe);

  if(X != nowe->current_x || Y != nowe->current_y)//Jeśli czołg się ruszył
    nowe = RM(nowe, token, M, buffer, x, y);

  else{
    nowe = LM(nowe, token, M, buffer, x, y);
  }
  return nowe;
}


Pole *LM(Pole *SIO, char *token, Mapa *M, char *buffer, int x, int y){
  Pole *nowe;
  FILE *f;
  int X, Y;
  nowe = SIO;

  if(x == SIO->current_x & y == SIO->current_y)
    return nowe;

  left(token);
  f = fopen(token, "r"); 
  fread(buffer,1,2048,f);
  fclose(f);
  M = wczytaj_json(M, buffer);
  nowe = update_direction(nowe, M);
  zwolnij_mape(M);

  X = nowe->current_x;
  Y = nowe->current_y;

  move(token);
  f = fopen(token, "r"); 
  fread(buffer,1,2048,f);
  fclose(f);
  M = wczytaj_json(M, buffer);
  nowe = update_move(nowe, M);
  zwolnij_mape(M);
  wypisz(nowe);

  if(check_border(nowe) == 1)
    nowe = powieksz(nowe);

  if(X != nowe->current_x || Y != nowe->current_y)//Jeśli czołg się ruszył
    return nowe;

  else{
    nowe = LM(nowe, token, M, buffer, x, y);
  }
  return nowe;
}

Pole *SIOv2_0(Pole *P, char *token, Mapa *M, char *buffer){
  int i,j,x,y,X,Y,a;
  Pole *SIO;
  FILE *f;
  SIO = P;
  x = 0; //współrzędna pomocnicza x przed ruchem
  y = 0;  //współrzędna pomocnicza y przed ruchem

  while(x != SIO->current_x || y != SIO->current_y){
    x = SIO->current_x;
    y = SIO->current_y;
    move(token);
    f = fopen(token, "r"); 
    fread(buffer,1,2048,f);
    fclose(f);
    M = wczytaj_json(M, buffer);
    SIO = update_move(SIO, M);
    zwolnij_mape(M);
    wypisz(SIO);
    if(check_border(SIO) == 1){
      SIO = powieksz(SIO);
    }
  }
  
  
  x = SIO->current_x;
  y = SIO->current_y;
  X = x;
  Y = y;


  SIO = LM(SIO, token, M, buffer, X, Y);
  wypisz(SIO);

  while(X != SIO->current_x || Y != SIO->current_y)
  {
    X = x;
    Y = y;
    SIO = RM(SIO, token, M, buffer, X, Y);
    if(check_border(SIO) == 1)
      SIO = powieksz(SIO);
  }

  return SIO;

  SIO = LM(SIO, token, M, buffer, X, Y);
  SIO = LM(SIO, token, M, buffer, X, Y);

  x = 0; //współrzędna pomocnicza x przed ruchem
  y = 0;  //współrzędna pomocnicza y przed ruchem

  while(x != SIO->current_x || y != SIO->current_y){
    x = SIO->current_x;
    y = SIO->current_y;
    move(token);
    f = fopen(token, "r"); 
    fread(buffer,1,2048,f);
    fclose(f);
    M = wczytaj_json(M, buffer);
    SIO = update_move(SIO, M);
    zwolnij_mape(M);
    wypisz(SIO);
    if(check_border(SIO) == 1){
      SIO = powieksz(SIO);
    }
  }

  X = -1000;
  Y = -1000;
  x = SIO->current_x;
  y = SIO->current_y;

  SIO = LM(SIO, token, M, buffer, X, Y);
  wypisz(SIO);

  while(X != SIO->current_x || Y != SIO->current_y)
  {
    X = x;
    Y = y;
    SIO = RM(SIO, token, M, buffer, X, Y);
    if(check_border(SIO) == 1)
      SIO = powieksz(SIO);
  }


  return SIO;
}