#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "../../cJSON/cJSON.h"

#include "logika.h"
#include "polecenia.h"
#include "mapa.h"

Pole *RM(Pole *SIO, char *token, Mapa *M, Mapa_explore *ME, char *buffer, int x, int y)
{
  Pole *nowe;
  FILE *f;
  int X, Y;
  nowe = SIO;

  right(token);
  f = fopen(token, "r");
  fread(buffer, 1, 2048, f);
  fclose(f);
  M = wczytaj_json(M, buffer);
  nowe = update_direction(nowe, M);
  zwolnij_mape(M);

  X = nowe->current_x;
  Y = nowe->current_y;

  move(token);
  f = fopen(token, "r");
  fread(buffer, 1, 2048, f);
  fclose(f);
  M = wczytaj_json(M, buffer);
  nowe = update_move(nowe, M);
  zwolnij_mape(M);

  if (check_border(nowe) == 1)
  {
    if (strcmp(SIO->direction, "W") == 0)
    {
      x = x + SIO->rozmiar_x;
    }
    else if (strcmp(SIO->direction, "S") == 0)
    {
      y = y + SIO->rozmiar_y;
    }
    nowe = powieksz(nowe);
  }

  explore(token);
  f = fopen(token, "r");
  fread(buffer, 1, 2048, f);
  fclose(f);
  ME = wczytaj_json_explore(ME, buffer);
  nowe = update_explore(nowe, ME);
  zwolnij_mape_explore(ME);
  wypisz(nowe);

  printf("Pole wyjściowe: x:%d y:%d\n Pole aktualne: x:%d y:%d\n", x, y, nowe->current_x, nowe->current_y);

  if (x == nowe->current_x & y == nowe->current_y)
  {
    printf("Czołg stoi na polu wyjściowym po ruchu RM\n");
    return nowe;
  }

  if (X != nowe->current_x || Y != nowe->current_y) //Jeśli czołg się ruszył
  {
    nowe = RM(nowe, token, M, ME, buffer, x, y);
    return nowe;
  }

  else //Jeśli czołg został w miejscu
  {
    nowe = LM(nowe, token, M, ME, buffer, x, y);
    return nowe;
  }
  return nowe;
}

Pole *LM(Pole *SIO, char *token, Mapa *M, Mapa_explore *ME, char *buffer, int x, int y)
{
  Pole *nowe;
  FILE *f;
  int X, Y;
  nowe = SIO;

  left(token);
  f = fopen(token, "r");
  fread(buffer, 1, 2048, f);
  fclose(f);
  M = wczytaj_json(M, buffer);
  nowe = update_direction(nowe, M);
  zwolnij_mape(M);

  X = nowe->current_x;
  Y = nowe->current_y;

  move(token);
  f = fopen(token, "r");
  fread(buffer, 1, 2048, f);
  fclose(f);
  M = wczytaj_json(M, buffer);
  nowe = update_move(nowe, M);
  zwolnij_mape(M);

  if (check_border(nowe) == 1)
  {
    if (strcmp(SIO->direction, "W") == 0)
    {
      x = x + SIO->rozmiar_x;
    }
    else if (strcmp(SIO->direction, "S") == 0)
    {
      y = y + SIO->rozmiar_y;
    }
    nowe = powieksz(nowe);
  }

  explore(token);
  f = fopen(token, "r");
  fread(buffer, 1, 2048, f);
  fclose(f);
  ME = wczytaj_json_explore(ME, buffer);
  nowe = update_explore(nowe, ME);
  zwolnij_mape_explore(ME);
  wypisz(nowe);

  printf("Pole wyjściowe: x:%d y:%d\n Pole aktualne: x:%d y:%d\n", x, y, nowe->current_x, nowe->current_y);

  if (X != nowe->current_x || Y != nowe->current_y) //Jeśli czołg się ruszył
  {
    nowe = RM(nowe, token, M, ME, buffer, x, y);
    return nowe;
  }

  else //Jeśli czołg został w miejscu
  { 
    nowe = LM(nowe, token, M, ME, buffer, x, y);
    return nowe;
  }
  return nowe;
}

Pole *go_straight(Pole *SIO, Mapa *M, Mapa_explore *ME, char *token, char *buffer)
{
  int x, y;
  Pole *nowe;
  nowe = SIO;
  FILE *f;

  x = SIO->current_x;
  y = SIO->current_y;

  move(token);
  f = fopen(token, "r");
  fread(buffer, 1, 2048, f);
  fclose(f);
  M = wczytaj_json(M, buffer);
  nowe = update_move(nowe, M);
  zwolnij_mape(M);

  if (check_border(nowe) == 1)
    nowe = powieksz(nowe);

  explore(token);
  f = fopen(token, "r");
  fread(buffer, 1, 2048, f);
  fclose(f);
  ME = wczytaj_json_explore(ME, buffer);
  nowe = update_explore(nowe, ME);
  zwolnij_mape_explore(ME);

  wypisz(nowe);

  printf("Pole poprzednie: x:%d y:%d\n Pole nowe: x:%d y:%d\n", x, y, nowe->current_x, nowe->current_y);

  if (nowe->current_x != x || nowe->current_y != y) //Jeśli czołg się ruszył
  { 
    nowe = go_straight(nowe, M, ME, token, buffer);
  }

  return nowe;
}

Pole *turn_180(Pole *SIO, Mapa *M, Mapa_explore *ME, char *buffer, char *token)
{
  int i;
  Pole *nowe;
  nowe = SIO;
  FILE *f;

  for (i = 0; i < 2; i++)
  {
    left(token);
    f = fopen(token, "r");
    fread(buffer, 1, 2048, f);
    fclose(f);
    M = wczytaj_json(M, buffer);
    nowe = update_direction(nowe, M);
    zwolnij_mape(M);
  }
  return nowe;
}

Pole *SIOv2_0(Pole *P, char *token, Mapa *M, Mapa_explore *ME, char *buffer)
{
  int x, y;
  Pole *SIO;
  SIO = P;

  SIO = go_straight(SIO, M, ME, token, buffer);

  x = SIO->current_x;
  y = SIO->current_y;

  SIO = LM(SIO, token, M, ME, buffer, x, y);

  SIO = turn_180(SIO, M, ME, buffer, token);

  SIO = go_straight(SIO, M, ME, token, buffer);

  x = SIO->current_x;
  y = SIO->current_y;

  SIO = LM(SIO, token, M, ME, buffer, x, y);

  wypisz(SIO);

  return SIO;
}