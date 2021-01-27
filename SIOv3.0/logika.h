#ifndef _logika_h
#define _logika_h

#include "mapa.h"
#include "polecenia.h"

Pole *SIOv2_0(Pole *P, Dane *M, Dane2 *ME);
Pole *SIOv3_0(Pole *P, Dane *M, Dane2 *ME);
Pole *do_przodu(Pole *SIO, Dane *M, Dane2 *ME);
Pole *lewo_ruch(Pole *SIO, Dane *M, Dane2 *ME, int x, int y);
Pole *prawo_ruch(Pole *SIO, Dane *M, Dane2 *ME, int x, int y);
Pole *obrot_180(Pole *SIO, Dane *M, Dane2 *ME);
int sprawdz_postep(Pole *P, Rozmiar *r);
Rozmiar *znajdz_zewnetrzny_mur(Pole *P);

#endif