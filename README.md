# Projekt-SIO
Projekt na seminarium z podstaw programowania

SIO - Symulator Inteligentnego Odkurzacza 

Program podzielony jest na moduły: main, mapa, polecenia i logika. Każdy z nich ma swoje zastosowanie.
Moduł mapa tworzy obszar, w którym będzie poruszał się później nasz odkurzacz, zapsiuje ją też do pliku, przechowuje ją i alokuje pamieć.
Moduł polecenia ma za zadanie komunikować się z serwerem i zwracać odpowiedź o stanie pól, przetważa odpowiedź jaką dostaje na jezyk programowania czytelny dla programu i za pomocą biblioteki cJSON zwraca wynik jako dane.
Kolejny moduł - logika, interpretuje położenie odkurzacza, porusza sie nim po mapie za pomocą algorytmu. 
Wszystkie te moduły podpięte są pod plik main.c, który zawiera również biblioteki używane w programie razem z biblioteką cJSON. 
Program zawiera również plik makefile, który ułatwia uruchomienie go.

Program został stworzony w celu automatycznego odkrycia mapy gry "Logo Worlds" dostępnej na stronie "http://edi.iem.pw.edu.pl:30000/index.html"

Aby uruchomić program, najpierw trzeba sprawdzić,czy zainstalowana biblioteka cJSON jest poprawnie zaadresowana.
Kiedy wszystko zostało sprawdzone, możemy skompilować program używając "make".

Skompilowany program możemy używać manualnie lub sprawić, żeby działał automatycznie.

Jeśli chcemy używać go manualnie, w konsoli musimy wpisać "./projekt" i po spacji wypisywać komendy, które program ma wykonać.
Dostępne komendy:
M - move - sprawia, że czołg rusza się do przodu,
L - left - obraca czołg w lewo,
R - right - obraca czołg w prawo,
E - explore - odkrywa 3 pola w prostopadłej linii do kierunku czołgu.

Aby uruchomić algorytm, który sam będzie odkrywał mapę należy wpisać "./projekt SIOv2.0" lub "make test-SIOv2.0".



Autorzy: 
Aleksandra Hermańska
Marcin Pietrzak
