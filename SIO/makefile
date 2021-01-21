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

test-powiekszE: all-mapa
	./mapa L M M R M R M M L

test-powiekszN: all-mapa
	./mapa L L M M M L L M M M

test-powiekszW: all-mapa
	./mapa R L

test-SIOv1.0: all-mapa
	./mapa M R E M E M E M E L M M M M L M M M M M M M L M E R M E R M E L M E L M M M M M L M M M M M M R M M R M M M M M M E L M L M M E L M R M M R M E L M M M E L M R M M R M E R R M L M M M R M

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