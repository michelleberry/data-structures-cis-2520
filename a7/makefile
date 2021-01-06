all: ttt1.o ttt2.o show_node count_nodes alphatoe

ttt1.o: ttt1.c ttt.h
	gcc -std=c99 -Wall -pedantic -c ttt1.c 

ttt2.o: ttt2.c ttt.h
	gcc -std=c99 -Wall -pedantic -c ttt2.c

show_node.o: show_node.c ttt.h
	gcc -std=c99 -Wall -pedantic -c show_node.c

show_node: show_node.o ttt.h
	gcc -std=c99 -Wall -pedantic -o show_node show_node.o ttt1.o ttt2.o

count_nodes.o: count_nodes.c ttt.h
	gcc -std=c99 -Wall -pedantic -c count_nodes.c

count_nodes: count_nodes.o ttt.h
	gcc -std=c99 -Wall -pedantic -o count_nodes count_nodes.o ttt1.o ttt2.o

alphatoe.o: alphatoe.c ttt.h
	gcc -std=c99 -Wall -pedantic -c alphatoe.c

alphatoe: alphatoe.o ttt.h
	gcc -std=c99 -Wall -pedantic -o alphatoe alphatoe.o ttt1.o ttt2.o

clean:
	rm -i *.o