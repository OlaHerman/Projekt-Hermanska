all:
	cc main.c polecenia.c mapa.c logika.c odpowiedz.c -lcurl -o projekt ../../cJSON/cjson.o

test: all
	./projekt

test-memory: all
	valgrind ./projekt left

test-move: all
	./projekt move

test-left: all
	./projekt left

test-right: all
	./projekt right

test-explore: all
	./projekt explore