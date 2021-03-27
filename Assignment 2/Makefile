all: torpedo_game clean

torpedo_game : Object.o Torpedo.o Boat.o BoatA.o BoatB.o BoatC.o Map.o main.o
	g++ -o torpedo_game Object.o Torpedo.o Boat.o BoatA.o BoatB.o BoatC.o Map.o main.o

Object.o : Object.cpp
	g++ -c -o Object.o Object.cpp
	
Torpedo.o : Torpedo.cpp
	g++ -c -o Torpedo.o Torpedo.cpp
	
Boat.o : Boat.cpp
	g++ -c -o Boat.o Boat.cpp
	
BoatA.o : BoatA.cpp
	g++ -c -o BoatA.o BoatA.cpp
	
BoatB.o : BoatB.cpp
	g++ -c -o BoatB.o BoatB.cpp
	
BoatC.o : BoatC.cpp
	g++ -c -o BoatC.o BoatC.cpp
	
Map.o : Map.cpp
	g++ -c -o Map.o Map.cpp

main.o : main.cpp
	g++ -c -o main.o main.cpp

clean :
	rm *.o