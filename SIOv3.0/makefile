all:
	cc main.c polecenia.c mapa.c logika.c -lcurl -o projekt ../../cJSON/cjson.o

all-mapa:
	cc mapa_main.c polecenia.c mapa.c logika.c -lcurl -o mapa ../../cJSON/cjson.o

all-SIO:
	cc mapa_main.c polecenia.c mapa.c logika.c -lcurl -o sio1 ../../cJSON/cjson.o

test-SIOv2.0: all
	./projekt SIOv2.0

test-SIOv3.0: all	
	./projekt SIOv3.0

test: all	
	./projekt

test-kolo: all	
	./projekt L M E L M E L M E L M E

test-sciana: all
	./projekt R M L

test-powiekszE: all
	./projekt L M M R M R M M L

test-powiekszN: all
	./projekt L L M M M L L M M M

test-memory: all
	valgrind --leak-check=full ./projekt L 

test-move: all
	./projekt move

test-left: all
	./projekt L

test-right: all
	./projekt R

test-explore: all
	./mapa E