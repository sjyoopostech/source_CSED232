/*
 * name		: Seungjae Yoo
 * email	: sjyoo@postech.ac.kr
 * date		: 2017.11.12
 */

// headers
#include "Object.h"
#include "Torpedo.h"
#include "Boat.h"
#include "BoatA.h"
#include "BoatB.h"
#include "BoatC.h"
#include "Map.h"

// libraries
#include <iostream>
#include <string>

// using std namespace
using namespace std;

// directly used functions
void startMenu();
int is_int(string line);

int main() {

	// map object
	Map* map;

	// while having game
	while(1) {
		system("cls");

		// setting game
		startMenu();
		string type;
		cin >> type;
		if (type.length() != 1) exit(0);
		if (type.at(0) == '1') { // basic game
			map = new Map(5, 10, 5, 8, 35);
		}
		else if (type.at(0) == '2') { // user-defined game
			int x, y, n;
			while (1) {
				cout << "X Axis : ";
				cin >> type;
				if (!is_int(type)) {
					cout << "Wrong input type" << endl;
					continue;
				}
				x = atoi(type.c_str());
				if (x < 3) {
					cout << "Please put larger X" << endl;
					continue;
				}
				if (x > 100) {
					cout << "Please put smaller X" << endl;
					continue;
				}
				break;
			}
			while (1) {
				cout << "Y Axis : ";
				cin >> type;
				if (!is_int(type)) {
					cout << "Wrong input type" << endl;
					continue;
				}
				y = atoi(type.c_str());
				if (y < 3) {
					cout << "Please put larger Y" << endl;
					continue;
				}
				if (y > 100) {
					cout << "Please put smaller Y" << endl;
					continue;
				}
				break;
			}
			while (1) {
				cout << "Boats : ";
				cin >> type;
				if (!is_int(type)) {
					cout << "Wrong input type" << endl;
					continue;
				}
				n = atoi(type.c_str());
				if (n > x*(y-1)/5) {
					cout << "Please put smaller n" << endl;
					continue;
				}
				break;
			}
			map = new Map(x, y, n, (int)(1.5*n), x*n+y);
		}
		else exit(0); // when other input comes

		map->PrintScreen(); // print initial screen

		// having a game
		while (1) {
			cin >> type;
			if (type.length() != 1) { // when this is not a character
				map->PrintScreen();
				continue;
			}
			char a = type.at(0);

			if (a == 'Q' || a == 'q') { // press Q
				map->PressQ();
				map->PrintScreen();
			}
			else if (a == 'W' || a == 'w') { // press W
				map->PressW();
				map->PrintScreen();
			}
			else if (a == 'E' || a == 'e') { // press E
				map->PressE();
				map->PrintScreen();
			}
			else if (a == 'A' || a == 'a') { // press A
				map->PressA();
				map->PrintScreen();
			}
			else if (a == 'S' || a == 's') { // press S
				map->PressS();
				map->PrintScreen();
			}
			else if (a == 'D' || a == 'd') { // press D
				map->PressD();
				map->PrintScreen();
			}
			else { // other key pressed
				//map->PrintScreen();
				continue;
			}

			if (map->result() == 1) { // when victories
				map->victory();
				break;
			}
			else if (map->result() == -1) { // when defeats
				map->defeat();
				break;
			}
		}

		// play one more or not
		cout << "U want play again? Y/N" << endl;
		while (1) {
			cin >> type;
			if (type.length() == 1) {
				if (type.at(0) == 'Y' || type.at(0) == 'y') break;
				else if (type.at(0) == 'N' || type.at(0) == 'n') exit(0);
			}
			cout << "Please press Y/N" << endl;
		}
	}

	return 0;
}

// prints start menu
void startMenu() {
	cout << "==========================" << endl;
	cout << "welcome to torpido game!" << endl;
	cout << "1. start default game!" << endl;
	cout << "2. start custom game!" << endl;
	cout << endl;
	cout << "else. quit" << endl;
	cout << "==========================" << endl;
	cout << endl;
	cout << "your command : ";
}

// check line is int
// reused and edited from my code of assignment 1 (pizzaria)
int is_int(string line) {
	for (int i = 0; i < line.length(); i++) {
		if (line.at(i) < 0x30 || line.at(i) > 0x39) return 0;
	}
	return 1;
}