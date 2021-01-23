#ifndef _logika_h
#define _logika_h

#include "mapa.h"
#include "polecenia.h"
#include "odpowiedz.h"

Pole *SIOv2_0(Pole *P, char *token, Mapa *M, char *buffer);
Pole *LM(Pole *SIO, char *token, Mapa *M, char *buffer, int x, int y);
Pole *RM(Pole *SIO, char *token, Mapa *M, char *buffer, int x, int y);

#endif