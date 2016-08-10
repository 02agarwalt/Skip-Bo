//Final Project for CS120
//Written by Shiv Krishnan
//Nirmal Krishnan, Shiv Krishnan, Tanay Agarwal, Irving Nestor
//nkrishn9, skrish23, tagarwa2, inestor1
//8 May 2015
//600.120 Intermediate Programming
//Section 2
//Joanne Selinski 

#ifndef Project_Board_h
#define Project_Board_h
#include <vector>
#include <iostream>
#include <string>

using std::vector;

class Board {
  friend class Test;
  public:
  vector<int> deck;
  vector<int> build;
  vector<int> buildpile[4];
  //constructor
  Board();
  ~Board();
  //constructor for load
  Board(vector<int> &deck1, vector<int> &build1, vector<int> buildpile1[4]);
  //adds the completed buildpiles to build which is added to deck   
  void incrementbuild(vector<int> &tempbuild);
  //checks if deck is empty
  bool checkifemptydeck();
  //replaces empty deck
  void refilldeck();
  //display buildpiles
  void displayBuilds();
};

#endif

