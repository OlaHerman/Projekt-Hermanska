#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "../../cJSON/cJSON.h"

#include "logika.h"
#include "polecenia.h"
#include "mapa.h"

Pole *prawo_ruch(Pole *SIO, Dane *M, Dane2 *ME, int x, int y)
{
  Pole *nowe;
  int X, Y;
  nowe = SIO;

  nowe = prawo(nowe, M);

  X = nowe->zajety_x;
  Y = nowe->zajety_y;

  nowe = ruch(nowe, M);

  if (sprawdz_granice(nowe) == 1)
  {
    if (strcmp(SIO->kierunek, "W") == 0)
    {
      x = x + SIO->rozmiar_x;
    }
    else if (strcmp(SIO->kierunek, "S") == 0)
    {
      y = y + SIO->rozmiar_y;
    }
    nowe = powieksz(nowe);
  }

  nowe = odkryj(nowe, ME);
  wypisz(nowe);

  if (x == nowe->zajety_x & y == nowe->zajety_y)
    return nowe;
  

  if (X != nowe->zajety_x || Y != nowe->zajety_y) //Jeśli czołg się ruszył
  {
    nowe = prawo_ruch(nowe, M, ME, x, y);
    return nowe;
  }

  else //Jeśli czołg został w miejscu
  {
    nowe = lewo_ruch(nowe, M, ME, x, y);
    return nowe;
  }
  return nowe;
}

Pole *lewo_ruch(Pole *SIO, Dane *M, Dane2 *ME, int x, int y)
{
  Pole *nowe;
  int X, Y;
  nowe = SIO;

  nowe = lewo(nowe, M);

  X = nowe->zajety_x;
  Y = nowe->zajety_y;

  nowe = ruch(nowe, M);

  if (sprawdz_granice(nowe) == 1)
  {
    if (strcmp(SIO->kierunek, "W") == 0)
    {
      x = x + SIO->rozmiar_x;
    }
    else if (strcmp(SIO->kierunek, "S") == 0)
    {
      y = y + SIO->rozmiar_y;
    }
    nowe = powieksz(nowe);
  }

  nowe = odkryj(nowe, ME);
  wypisz(nowe);

  if (X != nowe->zajety_x || Y != nowe->zajety_y) //Jeśli czołg się ruszył
  {
    nowe = prawo_ruch(nowe, M, ME, x, y);
    return nowe;
  }

  else //Jeśli czołg został w miejscu
  { 
    nowe = lewo_ruch(nowe, M, ME, x, y);
    return nowe;
  }
  return nowe;
}

Pole *do_przodu(Pole *SIO, Dane *M, Dane2 *ME)
{
  int x, y;
  Pole *nowe;
  nowe = SIO;

  x = SIO->zajety_x;
  y = SIO->zajety_y;

  nowe = ruch(SIO, M);

  if (sprawdz_granice(nowe) == 1)
    nowe = powieksz(nowe);

  odkryj(nowe, ME);

  wypisz(nowe);

  if (nowe->zajety_x != x || nowe->zajety_y != y) //Jeśli czołg się ruszył
    nowe = do_przodu(nowe, M, ME);
  

  return nowe;
}

Pole *obrot_180(Pole *SIO, Dane *M, Dane2 *ME)
{
  int i;
  Pole *nowe;
  nowe = SIO;

  for (i = 0; i < 2; i++)
  {
    prawo(nowe, M);
  }
  return nowe;
}

Rozmiar *znajdz_zewnetrzny_mur(Pole *P){
  int i, j, m, n;
  Rozmiar *r;
  r = (Rozmiar*) malloc(sizeof(Rozmiar));

  for(i=0; i<P->rozmiar_y;i++){
    for(j=0;j<P->rozmiar_x;j++){
      if(P->index[P->rozmiar_y - i - 1][j] == 'w'){
        m = P->rozmiar_y - i - 1;
        n = j;
        while(P->index[m][n+1] == 'w' || n + 1 == P->rozmiar_x - 1)
          n++;
        r->X = n - j + 1;
        while(P->index[m - 1][n] == 'w'){
          m--;
          if(m == 0)
          break;
        }
        r->Y = P->rozmiar_y - i - 1 - m + 1;
        while(P->index[m][n-1] == 'w'){
          n--;
          if(n == 0)
            break;
        }
        while(P->index[m + 1][n] == 'w'){
          m++;
          if(m == P->rozmiar_y -1)
            break;
        }
        if(m == P->rozmiar_y - i - 1 & n == j)
          return r;
        
        return NULL;
        }
        else if(P->index[P->rozmiar_y - i - 1][j] == 'g' || P->index[P->rozmiar_y - i - 1][j] == 's' || P->index[P->rozmiar_y - i - 1][j] == 'S' || P->index[P->rozmiar_y - i - 1][j] == 'G' )
          return NULL;
      }
    }
  return NULL;
}

int sprawdz_postep(Pole *P, Rozmiar *r){
  int i, j, a;
  a = 0;
  if(r == NULL)
    return 0;

  for(i=0; i<P->rozmiar_y;i++)
    for(j=0;j<P->rozmiar_x;j++)
      if(P->index[i][j] != '.')
        a++;
  if(a == r->X*r->Y) //Cała mapa odkryta
    return 1;
  
  return 0;
}



Pole *SIOv2_0(Pole *P, Dane *M, Dane2 *ME)
{
  int x, y;
  Pole *SIO;
  SIO = P;

  SIO = do_przodu(SIO, M, ME);

  x = SIO->zajety_x;
  y = SIO->zajety_y;

  SIO = lewo_ruch(SIO, M, ME, x, y);
  
  SIO = do_przodu(SIO, M, ME);
  
  SIO = obrot_180(SIO, M, ME);

  x = SIO->zajety_x;
  y = SIO->zajety_y;

  SIO = lewo_ruch(SIO, M, ME, x, y);

  wypisz(SIO);

  return SIO;
}

Pole *SIOv3_0(Pole *P, Dane *M, Dane2 *ME){
  int x, y;
  int ruch_poczatkowy, ruch_koncowy;
  Pole *SIO;
  SIO = P;
  Rozmiar *r = NULL;
  ruch_poczatkowy = SIO->krok;

  while(sprawdz_postep(SIO, r) != 1)
  {
    SIO = do_przodu(SIO, M, ME);

    x = SIO->zajety_x;
    y = SIO->zajety_y;

    SIO = lewo_ruch(SIO, M, ME, x, y);

    r = znajdz_zewnetrzny_mur(SIO);

    if(r != NULL)
      break;
  
  SIO = do_przodu(SIO, M, ME);
  
  SIO = obrot_180(SIO, M, ME);

  SIO = ruch(SIO, M);
  SIO = prawo(SIO, M);
  SIO = ruch(SIO, M);
  SIO = ruch(SIO, M);
  SIO = prawo(SIO, M);
  }
  ruch_koncowy = SIO->krok;


  printf("Odkryto całą mapę w %d ruchach.\n", ruch_koncowy - ruch_poczatkowy);

  return SIO;
}