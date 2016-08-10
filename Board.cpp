//Final Project for CS120
//Written by Shiv Krishnan
//Nirmal Krishnan, Shiv Krishnan, Tanay Agarwal, Irving Nestor
//nkrishn9, skrish23, tagarwa2, inestor1
//8 May 2015
//600.120 Intermediate Programming
//Section 2
//Joanne Selinski 

#include "Board.h"
#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

Board::Board() {
    this->refilldeck();
}

Board::Board(vector<int> &deck1, std::vector<int> &build1, vector<int> buildpile1[4]) {
  
  deck = deck1;
  build = build1;
  for(int i = 0; i < 4; i++) {
    buildpile[i] = buildpile1[i];
  }

}

Board::~Board(){
    
}

void Board::incrementbuild(vector<int> &tempbuild) {
    
    for(unsigned int i = 0; i < tempbuild.size(); i++) {
        build.push_back(tempbuild.at(i));
    }
    tempbuild.clear();
}


bool Board::checkifemptydeck() {
    if(deck.size() == 0)
        return true;
    else
        return false;
}


void Board::refilldeck() {
    if(checkifemptydeck()) {
        if(build.size() == 0) {
            for(int i = 0; i < 12; i++) {
                for(int j = 0; j < 13; j++)
                    build.push_back(j);
            }
            for(int i = 0; i < 6; i++)
                build.push_back(0);
        }

        while(build.size() > 0){
            int n = rand() % build.size();
            deck.push_back(build.at(n));
            build[n] = build.back();
            build.pop_back();
        }
    }
    
}

void Board::displayBuilds(){
    cout << "Build Piles: ";
    for(int i = 0; i < 4; i++){
        if(this->buildpile[i].empty()){
            cout << "Empty ";
        }else{
            cout << this->buildpile[i].size() << " ";
        }
    }
    cout << endl;
}




