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
  Dane *M;
  Dane2 *ME;
  Pole *P;

  int i;
  char *mapa = "mapa.txt";

  P = info(M);
  wypisz(P);

  for (i = 0; i < argc; i++)
  {
    if (strcmp(argv[i], "L") == 0)
    {
      P = lewo(P, M);

      wypisz(P);
    }
    else if (strcmp(argv[i], "R") == 0)
    {
      P = prawo(P, M);
      wypisz(P);
    }
    else if (strcmp(argv[i], "M") == 0)
    {
      P = ruch(P, M);
      wypisz(P);
    }
    else if (strcmp(argv[i], "E") == 0)
    {
      P = odkryj(P, ME);
      wypisz(P);
    }
    else if (strcmp(argv[i], "SIOv2.0") == 0)
      P = SIOv2_0(P, M, ME);
    else if(strcmp(argv[i], "SIOv3.0") == 0)
      P = SIOv3_0(P, M, ME);
    if (sprawdz_granice(P) == 1)
      P = powieksz(P);

  }
  zapisz(P, mapa);
  zwolnij_pole(P);

  return 0;
}
