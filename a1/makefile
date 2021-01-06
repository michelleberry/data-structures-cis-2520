all: test_getbytes test_getbits test_bits2ull test_bits2ll test_spff test_dpff

test_getbytes: test_getbytes.o bandb.o
	gcc -std=c99 -Wall -pedantic -o test_getbytes test_getbytes.o bandb.o

test_getbits: test_getbits.o bandb.o
	gcc -std=c99 -Wall -pedantic -o test_getbits test_getbits.o bandb.o

test_bits2ull: test_bits2ull.o bandb.o
	gcc -std=c99 -Wall -pedantic -o test_bits2ull test_bits2ull.o bandb.o

test_bits2ll: test_bits2ll.o bandb.o
	gcc -std=c99 -Wall -pedantic -o test_bits2ll test_bits2ll.o bandb.o

test_spff: test_spff.o bandb.o
	gcc -std=c99 -Wall -pedantic -o test_spff test_spff.o bandb.o

test_dpff: test_dpff.o bandb.o 
	gcc -std=c99 -Wall -pedantic -o test_dpff test_dpff.o bandb.o

test_getbytes.o: test_getbytes.c bandb.h
	gcc -std=c99 -Wall -pedantic -c test_getbytes.c

test_getbits.o: test_getbits.c bandb.h
	gcc -std=c99 -Wall -pedantic -c test_getbits.c

test_bits2ull.o: test_bits2ull.c bandb.h
	gcc -std=c99 -Wall -pedantic -c test_bits2ull.c

test_bits2ll.o: test_bits2ll.c bandb.h
	gcc -std=c99 -Wall -pedantic -c test_bits2ll.c

test_spff.o: test_spff.c bandb.h
	gcc -std=c99 -Wall -pedantic -c test_spff.c

test_dpff.o: test_dpff.c bandb.h
	gcc -std=c99 -Wall -pedantic -c test_dpff.c

bandb.o: bandb.c 
	gcc -std=c99 -Wall -pedantic -c bandb.c 

clean: 
	rm -i test_getbytes test_getbytes.o test_getbits test_getbits.o test_bits2ll test_bits2ll.o test_bits2ull test_bits2ull.o test_spff test_spff.o test_dpff test_dpff.o bandb.o