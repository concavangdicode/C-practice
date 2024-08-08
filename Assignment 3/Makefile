concordence.exe: index_list.c concordence.c index_list.o
	gcc -g -Wall index_list.o concordence.c -o concordence.exe
main.exe: main_list.c index_list.c index_list.h
	gcc -g -Wall main_list.c index_list.o -o main.exe -DNDEBUG
index_list.o: index_list.c index_list.h
	gcc -c -Wall index_list.c -o index_list.o -DNDEBUG
clean:
	rm index_list.o main.exe concordence.exe