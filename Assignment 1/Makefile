all: pizzaria clean

pizzaria : Dough.o DoughList.o Edge.o EdgeList.o Topping.o ToppingList.o main.o
	g++ -o pizzaria Dough.o DoughList.o Edge.o EdgeList.o Topping.o ToppingList.o main.o

Topping.o : Topping.cpp
	g++ -c -o Topping.o Topping.cpp

Dough.o : Dough.cpp
	g++ -c -o Dough.o Dough.cpp

Edge.o : Edge.cpp
	g++ -c -o Edge.o Edge.cpp

ToppingList.o : ToppingList.cpp
	g++ -c -o ToppingList.o ToppingList.cpp

DoughList.o : DoughList.cpp
	g++ -c -o DoughList.o DoughList.cpp

EdgeList.o : EdgeList.cpp
	g++ -c -o EdgeList.o EdgeList.cpp

main.o : main.cpp
	g++ -c -o main.o main.cpp

clean :
	rm *.o