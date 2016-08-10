//Final Project for CS120
//Written by Nirmal Krishnan
//Nirmal Krishnan, Shiv Krishnan, Tanay Agarwal, Irving Nestor
//nkrishn9, skrish23, tagarwa2, inestor1
//8 May 2015
//600.120 Intermediate Programming
//Section 2
//Joanne Selinski 

#ifndef __ProjectPlayer__Human__
#define __ProjectPlayer__Human__

#include "Player.h"
#include <cstdlib>
#include <stack>
#include <string>
#include <limits>

using std::stack;

class Human: public Player{
	friend class Test;
    public:
    	virtual ~Human();
        Human(std::stack<int>  & stock, Board & toAdd, std::string nameAdd); //constructor, takes in stock pile and board
        Human(std::string name1, bool isTurn1, int hand1[5], std::stack<int> & stockAdd, Board & boardAdd, std::stack<int> trash1[4]);//constructor for loadgame
        bool takeTurn(); //all encompassing take turn function
        bool isHuman() const;
};
#endif /* defined(__ProjectPlayer__Human__) */

