#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "../../cJSON/cJSON.h"

#include "polecenia.h"
#include "mapa.h"
#include "logika.h"

//SIO - Symulator Inteligentnego Odkurzacza

int main(char argc, char **argv)
{
  Mapa *M;
  Mapa_explore *ME;
  Pole *P;

  int i;
  char *mapa = "mapa.txt";
  char buffer[2048];
  char *a = "qwerty_7.json";

  info(a);
  FILE *f;
  f = fopen(a, "r");
  fread(buffer, 1, 2048, f);
  fclose(f);
  M = wczytaj_json(M, buffer);
  P = stworz(M);
  zwolnij_mape(M);
  wypisz(P);

  for (i = 0; i < argc; i++)
  {
    if (strcmp(argv[i], "L") == 0)
    {
      left(a);
      f = fopen(a, "r");
      fread(buffer, 1, 2048, f);
      fclose(f);
      M = wczytaj_json(M, buffer);
      P = update_direction(P, M);
      zwolnij_mape(M);
      wypisz(P);
    }
    else if (strcmp(argv[i], "R") == 0)
    {
      right(a);
      f = fopen(a, "r");
      fread(buffer, 1, 2048, f);
      fclose(f);
      M = wczytaj_json(M, buffer);
      P = update_direction(P, M);
      zwolnij_mape(M);
      wypisz(P);
    }
    else if (strcmp(argv[i], "M") == 0)
    {
      move(a);
      f = fopen(a, "r");
      fread(buffer, 1, 2048, f);
      fclose(f);
      M = wczytaj_json(M, buffer);
      P = update_move(P, M);
      zwolnij_mape(M);
      wypisz(P);
    }
    else if (strcmp(argv[i], "E") == 0)
    {
      explore(a);
      f = fopen(a, "r");
      fread(buffer, 1, 2048, f);
      fclose(f);
      ME = wczytaj_json_explore(ME, buffer);
      P = update_explore(P, ME);
      zwolnij_mape_explore(ME);
      wypisz(P);
    }
    else if (strcmp(argv[i], "SIOv2.0") == 0)
      P = SIOv2_0(P, a, M, ME, buffer);

    if (check_border(P) == 1)
      P = powieksz(P);
  }

  wypisz(P);
  zapisz(P, mapa);
  zwolnij_pole(P);

  return 0;
}
