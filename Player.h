//Final Project for CS120
//Written by Nirmal Krishnan
//Nirmal Krishnan, Shiv Krishnan, Tanay Agarwal, Irving Nestor
//nkrishn9, skrish23, tagarwa2, inestor1
//8 May 2015
//600.120 Intermediate Programming
//Section 2
//Joanne Selinski 

#ifndef Project_Player_h
#define Project_Player_h
#include <stack>
#include <string>
#include <iostream>
#include "Board.h"

//stock pile == countdown pile
//discard pile == trash

using std::stack;

class Player{
    friend class Test;
    friend class Game;

public:
    Player(std::stack<int> & stockAdd, Board & boardAdd, std::string nameAdd);
    Player(std::string name1, bool isTurn, int hand[5], std::stack<int> & stockAdd, Board & boardAdd, std::stack<int> trash1[4]);
    virtual ~Player();
    //name of the player
    std::string name;
    //true if current player else false
    bool isTurn;
    //true if human, false if computer
    virtual bool isHuman() const = 0;

protected:
    //players current hand
    int hand[5];
    //object of the board class
    Board & b1;
    //array containing the four dump piles
    stack<int> trash[4];
    //stack containing the countdown cards
    stack<int> stock;


    //toMove denotes card position in the array in the functions below
    bool moveHand(int toMove, vector<int> & set); //moves card from hand to cards in play on board
    bool moveTrash(vector<int> & set, stack<int> &trash); //moves card from trash pile to cards in play on board
    //move countdown returns 2 if game is over
    //return 1 if true
    //returns 0 if false
    int moveStock(vector<int> & set); //moves card from countdown pile to cards in play on board
    void dumpCard(int toMove, stack<int> &trash); //moves card from hand to trash
    bool isEmpty(); //checks if hand is empty

    /*fill/refill hand up
    if input true then fill hand, else refill hand. hand needs
    to be filled at the beginning of each turn*/
    void fillHand();
    
public:
    virtual bool takeTurn() = 0; //all inclusive function for computer and human interaction, returns true if game is won, false otherwise
    friend std::ostream& operator<<(std::ostream& output, const Player& toPrint);
};

#endif

