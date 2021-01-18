all:
	cc main.c polecenia.c mapa.c logika.c odpowiedz.c -lcurl -o projekt ../../cJSON/cjson.o

all-mapa:
	cc mapa_main.c polecenia.c mapa.c -lcurl -o mapa ../../cJSON/cjson.o

test-mapa: all-mapa	
	./mapa

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

test-explore: all
	./projekt explore