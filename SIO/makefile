all:
	cc main.c polecenia.c mapa.c logika.c odpowiedz.c -lcurl -o projekt ../../cJSON/cjson.o

all-mapa:
	cc mapa_main.c polecenia.c mapa.c -lcurl -o mapa ../../cJSON/cjson.o

test-mapa: all-mapa	
	./mapa

test-kolo: all-mapa	
	./mapa L M E L M E L M E L M E

test-sciana: all-mapa
	./mapa R M L

test-powieksz: all-mapa
	./mapa L M M R M R M M L

test-powiekszN: all-mapa
	./mapa L L M M M L L M M M

test: all
	./projekt

test-memory: all
	valgrind ./projekt L

test-move: all
	./projekt move

test-left: all
	./projekt L

test-right: all
	./projekt R

test-explore: all-mapa
	./mapa