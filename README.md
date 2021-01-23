# Projekt-Hermanska
Projekt na seminarium z podstaw programowania

SIO - Symulator Inteligentnego Odkurzacza 

Program podzielony jest na moduły: main, mapa, polecenia i logika. Zawiera również plik makefile. Kazy z nich ma swoje zastosowanie. Moduł mapa tworzy obszar, w którym będzie poruszał się później nasz odkurzacz, zapsiuje ją też do pliku, przechowuje ją i alokuje pamieć. Moduł polecenia ma za zadanie komunikować się z serwerem i zwracać odpowiedź o stanie pól, przetważa odpowiedź jaką dostaje na jezyk programowania czytelny dla programu i za pomocą biblioteki cJSON zwraca wynik jako dane. Kolejny moduł -logika, interpretuje położenie odkurzacza, porusza sie nim po mapie za pomocą algorytmu. Wszystkie te moduły podpięte są pod plik main.c, który zawiera również biblioteki używane w programie razem z biblioteką cJSON.


Autorzy: 
Aleksandra Hermańska
Marcin Pietrzak
