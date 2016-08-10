//Final Project for CS120
//Written by Nirmal Krishnan
//Nirmal Krishnan, Shiv Krishnan, Tanay Agarwal, Irving Nestor
//nkrishn9, skrish23, tagarwa2, inestor1
//8 May 2015
//600.120 Intermediate Programming
//Section 2
//Joanne Selinski 

#ifndef Project_Game_h
#define Project_Game_h
#include "Board.h"
#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include <stdexcept>
#include <string>
#include <fstream>
#include <iostream>
#include <limits>

class Game{

public:
	//Game constructor
	Game(Player * toAdd[6], int playerCount, int size, Board & boardAdd);
	//Destructor
	~Game();
	//Board object
	Board & b1;
	//number of players in game
	int numPlayers;
	//size of stock piles
	int stockSize;
	//collection of players in game
	Player ** players;
	//all encompassing function
	void runGame();
	//writes vectors to the file
    void writeVector(std::ofstream &myfile, const vector<int> & v1);
	//writes stacks to files
	void writeStack(std::ofstream &myfile, stack<int> s1);
    //saves the game
	void saveGame();
};

#endif