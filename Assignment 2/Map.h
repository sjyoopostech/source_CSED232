#pragma once

// headers
#include "Object.h"
#include "Torpedo.h"
#include "Boat.h"
#include "BoatA.h"
#include "BoatB.h"
#include "BoatC.h"

class Map {
private :
	// storages of boats, torpedo, user
	BoatA** aList;
	BoatB** bList;
	BoatC** cList;
	Torpedo** tList;
	Boat* user;

	// stores number of boats and torpedos
	int num_all[4];
	int num_now[4];
	
	// map size
	int mapX;
	int mapY;

	// remain turn
	int turn;

	// maximum torpedo
	int t;

	// score
	int score;

	// check collision and destroy boats and torpedos
	void collision();

	// clear screen
	void ClearScreen();

public :
	// constructors
	Map(int x, int y, int boat, int torpido, int turn);

	// press button functions - newly defiend PressQ and PressE
	void PressQ();
	void PressW();
	void PressE();
	void PressA();
	void PressS();
	void PressD();

	// print screen
	void PrintScreen();

	// determine victory or defeat
	int result();

	// print screen when victory
	void victory();

	// print screen when defeat
	void defeat();
	
};