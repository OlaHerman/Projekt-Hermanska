#ifndef _logika_h
#define _logika_h

#include "mapa.h"
#include "polecenia.h"

Pole *SIOv2_0(Pole *P, char *token, Mapa *M, Mapa_explore *ME, char *buffer);
Pole *go_straight(Pole *SIO, Mapa *M, Mapa_explore *ME, char *token, char *buffer);
Pole *LM(Pole *SIO, char *token, Mapa *M, Mapa_explore *ME, char *buffer, int x, int y);
Pole *RM(Pole *SIO, char *token, Mapa *M, Mapa_explore *ME, char *buffer, int x, int y);
Pole *turn_180(Pole *SIO, Mapa *M, Mapa_explore *ME, char *buffer, char *token);

#endif