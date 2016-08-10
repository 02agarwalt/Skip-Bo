//Final Project for CS120
//Written by Shiv Krishnan
//Nirmal Krishnan, Shiv Krishnan, Tanay Agarwal, Irving Nestor
//nkrishn9, skrish23, tagarwa2, inestor1
//8 May 2015
//600.120 Intermediate Programming
//Section 2
//Joanne Selinski 

#ifndef _COMPUTER_H
#define _COMPUTER_H

#include "Player.h"
#include <cstdlib>
#include <stack>
#include <string>

using std::stack;
class Computer : public Player{

//we have friended the test functions so as to allow access to private and protected variables

  friend class playerTest;
  friend class computerTest;
  friend class Test;

 public:
 	//constructor to initialise the variables
  Computer(std::stack<int> & stock, Board & toAdd, std::string nameAdd);
    //constructor to load game
  Computer(std::string name1, bool isTurn1, int hand1[5], std::stack<int> & stockAdd, Board & boardAdd, std::stack<int> trash1[4]);
  //destructor to prevent memory leeks
  virtual~Computer();
  //implements a turn of the player 
  bool takeTurn();
  bool isHuman() const;
  //implements the moveStock function of player
  //bool formoveStock(vector<int> &set);
  int formoveStock(vector<int> &set);
  //implements te moveTrash of the Player class
  bool formoveTrash(vector<int> &set, stack<int> & trash);
  //implements the movehand of the player class
  bool formoveHand(vector<int> &set);
};

#endif
