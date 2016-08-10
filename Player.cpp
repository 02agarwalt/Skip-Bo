//Final Project for CS120
//Written by Nirmal Krishnan
//Nirmal Krishnan, Shiv Krishnan, Tanay Agarwal, Irving Nestor
//nkrishn9, skrish23, tagarwa2, inestor1
//8 May 2015
//600.120 Intermediate Programming
//Section 2
//Joanne Selinski 

#include "Player.h"
using std::stack;
using std::cout;
using std::endl;

Player::Player(std::stack<int> & stockAdd, Board & boardAdd, std::string nameAdd) :  name(nameAdd), b1(boardAdd), stock(stockAdd) {
    isTurn = false;
    for(int i =0; i<5; i++){
        this->hand[i] = -1;
    }
    fillHand();
}

Player::Player(std::string name1, bool isTurn1, int hand1[5], std::stack<int> & stockAdd, Board & boardAdd, std::stack<int> trash1[4]) : b1(boardAdd) {
  name = name1;
  isTurn = isTurn1;
  for(int i = 0; i < 4; i++) {
    hand[i] = hand1[i];
    trash[i] = trash1[i];
  }
  hand[4] = hand1[4];
  stock = stockAdd;
}

Player::~Player(){   
}

//moves card from hand to cards in play on board
bool Player::moveHand(int toMove, vector<int> & set){
  if(set.size() != 11 && (set.size() + 1 == (unsigned)(hand[toMove]) || hand[toMove] == 0)){
        set.push_back(hand[toMove]);
        hand[toMove] = -1;
        return true;
  }else if(set.size() == 11 && (set.size() +1 == (unsigned)(hand[toMove]) || hand[toMove] == 0)){
        set.push_back(hand[toMove]);
        b1.incrementbuild(set);
        set.clear();
        hand[toMove] = -1;
        return true;
    }else{
        return false;
    }
}

//moves card from trash pile to cards in play on board
bool Player::moveTrash(vector<int> &set, stack<int> &trash){
    if(trash.empty()){
        return false;
    }else if(set.size() != 11 && (set.size() + 1 == (unsigned)trash.top() || trash.top() == 0)){
        set.push_back(trash.top());
        trash.pop();
        //b1.displayBuilds();
        //cout << *this;
        return true;
    }else if(set.size() == 11 && (set.size() + 1 == (unsigned)trash.top() || trash.top() == 0)){
        set.push_back(trash.top());
        b1.incrementbuild(set);
        set.clear();
        trash.pop();
        return true;
    }else{
        return false;
    }
}

//moves card from countdown pile to cards in play on board
//move countdown returns 2 if game is over
//return 1 if true
//returns 0 if false
int Player::moveStock(vector<int> &set){
  if(set.size() != 11 && (set.size() +1 == (unsigned)stock.top() || stock.top() == 0)){
        set.push_back(stock.top());
        stock.pop();
        if(stock.size() == 0)
            return 2;
        else
            return 1;
  }else if(set.size() == 11 && (set.size() + 1 == (unsigned)stock.top() || stock.top() == 0)){
        set.push_back(stock.top());
        b1.incrementbuild(set);
        set.clear();
        stock.pop();
        if(stock.size() == 0)
            return 2;
        else
            return 1;
    }else{
        return 0;
    }
}

//checks if hand is empty
bool Player::isEmpty(){
    for(int i = 0; i < 5; i++){
        if(hand[i] >= 0) {
            return false;
        }
    }
    return true;
}

//moves card from hand to trash
void Player::dumpCard(int toMove, stack<int> &trash){ //moves card from hand to trash
    trash.push(hand[toMove]);
    hand[toMove] = -1;
}

/*fill/refill hand up. hand needs
 to be filled at the beginning of each turn*/
void Player::fillHand() {
    for(int i = 0; i < 5; i++) {
        if(hand[i] < 0) {
            b1.refilldeck();
            hand[i] = b1.deck.back();
            b1.deck.pop_back();
        }
    }
}

//output stream operator
std::ostream& operator<<(std::ostream& output, const Player& toPrint){
    //print extra info if its a human
    if(toPrint.isTurn && toPrint.isHuman()){
        output << "Current Player (" << toPrint.name << "):" << std::endl;
        output << "Hand: ";
        for(int i =0; i<5; i++){
            if(toPrint.hand[i] > 0){
                output << toPrint.hand[i] << " ";
            }
            if(toPrint.hand[i] == 0){
                output << "Skip-Bo" << " ";
            }
        }
        output << std::endl;
    }else{
        output << toPrint.name << ":" << std::endl;
    }
    
    output << "Discard Piles:  ";
    for(int i =0; i<4; i++){
        if(toPrint.trash[i].empty()){
            output << "Empty  ";
        }else{
            if(toPrint.trash[i].top() == 0){
                output << "Skip-Bo" << " ";
            }else{
                output << toPrint.trash[i].top() << "  ";
            }
        }
    }
    output << "\n" << "Stock Pile: ";
    if(toPrint.stock.top() == 0){
        output << "Skip-Bo (" << toPrint.stock.size() << ")" << std::endl;
    }else{
        output << toPrint.stock.top() << " (" << toPrint.stock.size() << ")" << std::endl;
    }
    return output;
}



