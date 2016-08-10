//Final Project for CS120
//Written by Shiv Krishnan
//Nirmal Krishnan, Shiv Krishnan, Tanay Agarwal, Irving Nestor
//nkrishn9, skrish23, tagarwa2, inestor1
//8 May 2015
//600.120 Intermediate Programming
//Section 2
//Joanne Selinski 

#include "Computer.h"
#include <stack>
#include <iostream>
#include <stdlib.h>
#include <time.h>

Computer::Computer(std::stack<int> & stock, Board & toAdd, std::string nameAdd): Player(stock, toAdd, nameAdd){
}

Computer::~Computer(){
    
}

Computer::Computer(std::string name1, bool isTurn1, int hand1[5], std::stack<int> & stockAdd, Board & boardAdd, std::stack<int> trash1[4]): Player(name1, isTurn1, hand1,   stockAdd, boardAdd, trash1) {
}

bool Computer::isHuman() const{
    return false;
}

bool Computer::takeTurn(){
    //control for the loop. loop ends when this is true
    bool endloop = false;
    int x=0;
    //std::cout << "!";
    while(!endloop) {
        //when deck is empty it refills the deck
        if(Player::isEmpty())
            Player::fillHand();
        x++;
        int k = 0;
        for(int i = 0; i < 4; i++) {
            k = formoveStock(b1.buildpile[i]);
            if(k==2){
                return true;
            }
            if(k==1)
                break;
        }
        if(k)
            continue;
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                k = formoveTrash(b1.buildpile[i], Player::trash[j]);
                if(k)
                    break;
            }
            if(k)
                break;
        }
        if(k)
            continue;
        
        for(int i = 0; i < 4; i++) {
            if(formoveHand(b1.buildpile[i]))
                if(k)
                    break;
        }
        //dumps card into the trash.
        //when card is dumped into trash turn ends
        if(k)
            continue;
        
        for(int i=0;i< 5;i++) {
            //Player::fillHand(false);
            if(Player::hand[i]>0) {
                dumpCard(i, trash[x%4]);
                endloop = true;
                break;
            }
            
        }
    }
    Player::fillHand();
    return false;
}


int Computer::formoveStock(vector<int> &set) {
    int m = Player::moveStock(set);
    //exits() code and destroys object to prevent leaaks
    if(m == 2){
        std::cout<<"Computer " << this->name  << " has won!" << std::endl;
        return 2;
    }
    else if(m == 1) {
        return 1;
    }
    else {
        return 0;
    }
}

bool Computer::formoveTrash(vector<int> &set, stack<int> & trash) {
    bool valid = Player::moveTrash(set, trash);
    return valid;
}

bool Computer::formoveHand(vector<int> &set) {
    for(int i=0; i < 5; i++) {
        if(Player::moveHand(i, set)) {
            return true;
        }
    }
    return false;
}



