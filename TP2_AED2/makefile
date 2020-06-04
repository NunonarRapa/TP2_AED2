all: tp2

tp2: main.o AuxRecord.o CitiesEdges.o CitiesGraph.o WorldCities.o
	gcc -g -o tp main.o ./AuxRecord/AuxRecord.o ./CitiesEdges/CitiesEdges.o ./CitiesGraph/CitiesGraph.o ./WorldCities/WorldCities.o

main.o: main.c 
	gcc -g -o main.o main.c -c -W -Wall -pedantic

AuxRecord.o: ./AuxRecord/AuxRecord.c ./AuxRecord/AuxRecord.h
	gcc -g -o ./AuxRecord/AuxRecord.o ./AuxRecord/AuxRecord.c -c -W -Wall -ansi -pedantic

CitiesEdges.o: ./CitiesEdges/CitiesEdges.c ./CitiesEdges/CitiesEdges.h
	gcc -g -o ./CitiesEdges/CitiesEdges.o ./CitiesEdges/CitiesEdges.c -c -W -Wall -pedantic

CitiesGraph.o: ./CitiesGraph/CitiesGraph.c ./CitiesGraph/CitiesGraph.h
	gcc -g -o ./CitiesGraph/CitiesGraph.o ./CitiesGraph/CitiesGraph.c -c -W -Wall -pedantic

WorldCities.o: ./WorldCities/WorldCities.c ./WorldCities/WorldCities.h
	gcc -g -o ./WorldCities/WorldCities.o ./WorldCities/WorldCities.c -c -W -Wall -pedantic

clean:
	del /Q /S *.o *~ tp