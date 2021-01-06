all: buildidx key2val val2key actors bacon1 hashfn.o util.o

hashfn.o: hashfn.c
	gcc -std=c99 -Wall -pedantic -c hashfn.c

util.o: util.c util.h
	gcc -std=c99 -Wall -pedantic -c util.c

buildidx.o: buildidx.c util.h hashfn.h
	gcc -std=c99 -Wall -pedantic -c buildidx.c

buildidx: buildidx.o util.o hashfn.o
	gcc -std=c99 -Wall -pedantic -o buildidx buildidx.o util.o hashfn.o

key2val.o: key2val.c util.h hashfn.h
	gcc -std=c99 -Wall -pedantic -c key2val.c

key2val: key2val.o util.o hashfn.o
	gcc -std=c99 -Wall -pedantic -o key2val key2val.o util.o hashfn.o

val2key.o: val2key.c util.h hashfn.h
	gcc -std=c99 -Wall -pedantic -c val2key.c

val2key: val2key.o util.o hashfn.o
	gcc -std=c99 -Wall -pedantic -o val2key val2key.o util.o hashfn.o

actors.o: actors.c util.h hashfn.h
	gcc -std=c99 -Wall -pedantic -c actors.c

actors: actors.o util.o hashfn.o
	gcc -std=c99 -Wall -pedantic -o actors actors.o util.o hashfn.o

bacon1.o: bacon1.c util.h hashfn.h
	gcc -std=c99 -Wall -pedantic -c bacon1.c

bacon1: bacon1.o util.o hashfn.o
	gcc -std=c99 -Wall -pedantic -o bacon1 bacon1.o util.o hashfn.o

clean: 
	rm -i *.o actors bacon1 val2key key2val buildidx