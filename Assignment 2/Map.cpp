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
#include <stdlib.h>
#include <time.h>

// constructors
Map::Map(int x, int y, int n, int t, int turn) {

	// stores values
	this->mapX = x;
	this->mapY = y;
	this->turn = turn;
	this->t = t;
	this->score = 0;

	int i, j;
	
	// memory allocation of view
	int** view; // for looking boat map
	view = (int**)malloc(sizeof(int*)*x);
	for (i = 0; i < x; i++) {
		view[i] = (int*)malloc(sizeof(int)*y);
		for (j = 0; j < y; j++) {
			view[i][j] = 0;
		}
	}

	// memory allocation of boats
	int** boats; // for looking x, y, type of boat
	boats = (int**)malloc(sizeof(int*)*n);
	for (i = 0; i < n; i++) {
		boats[i] = (int*)malloc(sizeof(int)*3);
		for (j = 0; j < 3; j++) {
			boats[i][j] = -1;
		}
	}

	// initializing num_all and num_now
	for (i = 0; i < 4; i++) {
		this->num_all[i] = 0;
		this->num_now[i] = 0;
	}

	// making boat map
	srand(time(NULL));
	int type, boatx, boaty;
	i = 0;
	while (i < n) {

		// get type, x, y
		type = rand() % 3;
		boatx = rand() % x;
		boaty = rand() % y;

		// when type is boatA
		if (type == 0) {
			// check x, y condition
			if (boatx == 0 || (boatx == x - 1)) continue;
			if (boaty < 1) continue;

			// check collision with other boats
			if (view[boatx][boaty]) continue;
			if (view[boatx-1][boaty]) continue;
			if (view[boatx+1][boaty]) continue;

			// fill informations
			boats[i][0] = 0;
			view[boatx][boaty] = 1;
			view[boatx-1][boaty] = 1;
			view[boatx+1][boaty] = 1;
			num_all[0]++;
		}

		// when type is boatB
		else if (type == 1) {
			// check x, y collision
			if (boatx == x - 1) continue;
			if (boaty < 2) continue;

			// check collision with other boats
			if (view[boatx][boaty]) continue;
			if (view[boatx+1][boaty]) continue;
			if (view[boatx][boaty-1]) continue;
			if (view[boatx+1][boaty-1]) continue;

			// fill informations
			boats[i][0] = 1;
			view[boatx][boaty] = 1;
			view[boatx+1][boaty] = 1;
			view[boatx][boaty-1] = 1;
			view[boatx+1][boaty-1] = 1;
			num_all[1]++;
		}

		// when type is boatC
		else if (type == 2) {
			// check x, y condition
			if (boaty < 1) continue;

			//check collision with other boats
			if (view[boatx][boaty]) continue;

			//fill informations
			boats[i][0] = 2;
			view[boatx][boaty] = 1;
			num_all[2]++;
		}

		// store x, y axis
		boats[i][1] = boatx;
		boats[i][2] = boaty;
		i++;
	}

	// memory allocation of lists of a, b, c, t;
	this->aList = (BoatA**)malloc(sizeof(BoatA*)*this->num_all[0]);
	this->bList = (BoatB**)malloc(sizeof(BoatB*)*this->num_all[1]);
	this->cList = (BoatC**)malloc(sizeof(BoatC*)*this->num_all[2]);
	this->tList = (Torpedo**)malloc(sizeof(Torpedo*)*t);

	// make boats into list
	int num;
	for (i = 0; i < n; i++) {

		// boatA
		if (boats[i][0] == 0) {

			// make boatA
			this->aList[num_now[0]] = new BoatA(boats[i][1], boats[i][2]);
			
			// move randomly
			num = rand() % 4;
			for (j = 0; j < num; j++) this->aList[num_now[0]]->move();
			num_now[0]++;
		}

		// boatB
		else if (boats[i][0] == 1) {

			// make boatB
			this->bList[num_now[1]] = new BoatB(boats[i][1], boats[i][2]);
			
			// move randomly
			num = rand() % 4;
			for (j = 0; j < num; j++) this->bList[num_now[1]]->move();
			num_now[1]++;
		}
		
		// boatC
		else if (boats[i][0] == 2) {

			// make boatC
			this->cList[num_now[2]] = new BoatC(boats[i][1], boats[i][2]);

			// move randomly
			num = rand() % 4;
			for (j = 0; j < num; j++) this->cList[num_now[2]]->move();
			num_now[2]++;
		}
	}

	// make user
	this->user = new Boat(x/2, 0);

	// deallocation of view
	for (i = 0; i < x; i++) {
		delete[]view[i];
	}
	delete[]view;

	// deallocation of boats
	for (i = 0; i < n; i++) {
		delete[]boats[i];
	}
	delete[]boats;
}

// check collision and destroy boats and torpedos
void Map::collision() {

	// decrease turn
	this->turn--;

	int i, j;

	// move boats and torpedos
	for (i = 0; i < num_all[0]; i++) { // boatA
		if (this->aList[i] == NULL) continue;
		this->aList[i]->move();
	}
	for (i = 0; i < num_all[1]; i++) { // boatB
		if (this->bList[i] == NULL) continue;
		this->bList[i]->move();
	}
	for (i = 0; i < num_all[2]; i++) { // boatC
		if (this->cList[i] == NULL) continue;
		this->cList[i]->move();
	}
	for (i = 0; i < num_all[3]; i++) { // torpedo
		if (this->tList[i] == NULL) continue;
		this->tList[i]->move();
	}

	// check collision between torpedo and boats
	for (i = 0; i < num_all[3]; i++) {
		for (j = 0; j < num_all[0]; j++) {
			// check boat and torpedo exist
			if (this->tList[i] == NULL) continue;
			if (this->aList[j] == NULL) continue;

			// check x, y axis are same
			if (this->tList[i]->getX() != this->aList[j]->getX()) continue;
			if (this->tList[i]->getY() != this->aList[j]->getY()) continue;

			// check boat is visible
			if (!this->aList[j]->getVisibility()) continue;

			// deallocation
			delete this->tList[i];
			delete this->aList[j];

			// set null
			this->tList[i] = NULL;
			this->aList[j] = NULL;

			// decrease number of torpedo and boat
			num_now[0]--;
			num_now[3]--;

			// increase score
			this->score += 100;
			break;
		}
		for (j = 0; j < num_all[1]; j++) {
			// check boat and torpedo exist
			if (this->tList[i] == NULL) continue;
			if (this->bList[j] == NULL) continue;

			// check x, y axis are same
			if (this->tList[i]->getX() != this->bList[j]->getX()) continue;
			if (this->tList[i]->getY() != this->bList[j]->getY()) continue;

			// check boat is visible
			if (!this->bList[j]->getVisibility()) continue;

			// deallocation
			delete this->tList[i];
			delete this->bList[j];

			// set null
			this->tList[i] = NULL;
			this->bList[j] = NULL;

			// decreases number of torpedo and boat
			num_now[1]--;
			num_now[3]--;

			// increase score
			this->score += 200;
			break;
		}
		for (j = 0; j < num_all[2]; j++) {
			// check boat and torpedo exist
			if (this->tList[i] == NULL) continue;
			if (this->cList[j] == NULL) continue;
			
			// check x, y axis are same
			if (this->tList[i]->getX() != this->cList[j]->getX()) continue;
			if (this->tList[i]->getY() != this->cList[j]->getY()) continue;

			// check boat is visible
			if (!this->cList[j]->getVisibility()) continue;

			// deallocation
			delete this->tList[i];
			delete this->cList[j];
			
			// ser null
			this->tList[i] = NULL;
			this->cList[j] = NULL;

			// decreases number of torpedo and boat
			num_now[2]--;
			num_now[3]--;

			// increase score
			this->score += 300;
			break;
		}

		// check torpedo exist
		if (this->tList[i] == NULL) continue;

		// when torpedo goes out of map
		if (this->tList[i]->getY() >= this->mapY || this->tList[i]->getX() < 0 || this->tList[i]->getX() >= this->mapX) {
			// deallocation
			delete this->tList[i];
			// set null
			this->tList[i] = NULL;
			// decreases number of torpedo
			num_now[3]--;
		}
	}
}

// press Q key
void Map::PressQ() {
	if (num_all[3] == t) return; // when all torpedo used
	this->tList[num_all[3]] = new Torpedo(this->user->getX(), 0); // make torpedo
	this->tList[num_all[3]]->changestatus(1);
	num_all[3]++;
	num_now[3]++;
	collision();
}

// press W key
void Map::PressW() {
	if (num_all[3] == t) return; // when all torpedo used
	this->tList[num_all[3]] = new Torpedo(this->user->getX(), 0); // make torpedo
	num_all[3]++;
	num_now[3]++;
	collision();
}

// press E key
void Map::PressE() {
	if (num_all[3] == t) return; // when all torpedo used
	this->tList[num_all[3]] = new Torpedo(this->user->getX(), 0); // make torpedo
	this->tList[num_all[3]]->changestatus(2);
	num_all[3]++;
	num_now[3]++;
	collision();
}

// press A key
void Map::PressA() {
	if (this->user->getX()) this->user->moveLeft(); // move user left
	collision();
}

// press S key
void Map::PressS() {
	collision();
}

// press D key
void Map::PressD() {
	if (this->user->getX()<this->mapX-1) this->user->moveRight(); // move user right
	collision();
}

// clear screen
void Map::ClearScreen() {
	system("cls");
}

// print screen
void Map::PrintScreen() {

	this->ClearScreen();
	int i, j;
	
	// memory allocation of view
	int** view;
	view = (int**)malloc(sizeof(int*)*this->mapX);
	for (i = 0; i < this->mapX; i++) {
		view[i] = (int*)malloc(sizeof(int)*this->mapY);
		for (j = 0; j < this->mapY; j++) {
			view[i][j] = 0;
		}
	}

	// making boat map
	for (i = 0; i < this->num_all[0]; i++) {
		if (this->aList[i] == NULL) continue;
		view[this->aList[i]->getX()][this->aList[i]->getY()] = 1;
	}
	for (i = 0; i < this->num_all[1]; i++) {
		if (this->bList[i] == NULL) continue;
		view[this->bList[i]->getX()][this->bList[i]->getY()] = 2;
	}
	for (i = 0; i < this->num_all[2]; i++) {
		if (this->cList[i] == NULL) continue;
		if (!this->cList[i]->getVisibility()) continue;
		view[this->cList[i]->getX()][this->cList[i]->getY()] = 3;
	}
	for (i = 0; i < this->num_all[3]; i++) {
		if (this->tList[i] == NULL) continue;
		view[this->tList[i]->getX()][this->tList[i]->getY()] = 4;
	}
	view[this->user->getX()][this->user->getY()] = 5;

	// print information
	std::cout << "Boat(s) Remain : " << this->num_now[0] + this->num_now[1] + this->num_now[2] << std::endl;
	std::cout << "Attempt(s) Remain : " << this->turn << std::endl;
	std::cout << "Torpido(s) Remain : " << this->t - this->num_all[3] << std::endl;
	std::cout << "Score : " << this->score << std::endl;

	// print map
	std::cout << "=====";
	for (i = 0; i < this->mapX; i++) {
		std::cout << "==";
	}
	std::cout << std::endl;
	for (j = this->mapY-1; j >= 0; j--) {
		std::cout << "|| ";
		for (i = 0; i < this->mapX; i++) {
			switch (view[i][j]) {
			case 0:
				std::cout << "~ ";
				break;
			case 1:
				std::cout << "A ";
				break;
			case 2:
				std::cout << "B ";
				break;
			case 3:
				std::cout << "C ";
				break;
			case 4:
				std::cout << "^ ";
				break;
			case 5:
				std::cout << "U ";
				break;
			}
		}
		std::cout << "||" << std::endl;
	}
	std::cout << "=====";
	for (i = 0; i < this->mapX; i++) {
		std::cout << "==";
	}
	std::cout << std::endl;

	// deallocation of view
	for (i = 0; i < this->mapX; i++) {
		delete[]view[i];
	}
	delete[]view;
}

// get result
int Map::result() {
	// when victory, return 1
	if (this->num_now[0] + this->num_now[1] + this->num_now[2] == 0) return 1;

	// when defeat, return -1
	if (this->turn == 0) return -1;
	if (num_now[3] == 0 && num_all[3] == this->t) return -1;

	// when in game, return 0
	return 0;
}

// print screen when victory
void Map::victory() {
	this->ClearScreen();
	this->score += this->turn * 500;
	this->score += (this->t - this->num_all[3]) * 400;
	std::cout << "=================" << std::endl;
	std::cout << "    Victory!!!   " << std::endl;
	std::cout << "=================" << std::endl;
	std::cout << std::endl;
	std::cout << "Boat(s) Remain : " << this->num_now[0] + this->num_now[1] + this->num_now[2] << std::endl;
	std::cout << "Attempt(s) Remain : " << this->turn << std::endl;
	std::cout << "Torpido(s) Remain : " << this->t - this->num_all[3] << std::endl;
	std::cout << "Score : " << this->score << std::endl;
}

// print screen when defeat
void Map::defeat() {
	this->ClearScreen();
	std::cout << "================" << std::endl;
	std::cout << "    Defeat!!!   " << std::endl;
	std::cout << "================" << std::endl;
	std::cout << std::endl;
	std::cout << "Boat(s) Remain : " << this->num_now[0] + this->num_now[1] + this->num_now[2] << std::endl;
	std::cout << "Attempt(s) Remain : " << this->turn << std::endl;
	std::cout << "Torpido(s) Remain : " << this->t - this->num_all[3] << std::endl;
	std::cout << "Score : " << this->score << std::endl;
}

