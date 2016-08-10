//Final Project for CS120
//Written by Irving Nestor
//Nirmal Krishnan, Shiv Krishnan, Tanay Agarwal, Irving Nestor
//nkrishn9, skrish23, tagarwa2, inestor1
//8 May 2015
//600.120 Intermediate Programming
//Section 2
//Joanne Selinski 

#include "Computer.h"
#include "Player.h"
#include "Human.h"
#include <iostream>
#include <cassert>
#include <stack>

using std::cout;
using std::endl;

class Test{
    
public:
    
  static void computerTest(){
        
        std::stack<int> stock;
        stock.push(0);
        stock.push(7);
        stock.push(10);
        stock.push(3);
        stock.push(1);
        Board b1;
        
        Computer *c1Ptr = new Computer(stock, b1, "Computer 1");
        Computer &c1 = *c1Ptr;
        
        c1.hand[0] = 2;
        c1.hand[1] = 4;
        c1.hand[2] = 6;
        c1.hand[3] = 0;
        c1.hand[4] = 12;
        c1.trash[1].push(2);
        c1.trash[0].push(1);
        
        c1.isTurn = true;
        cout << c1 << endl;
        
        c1.takeTurn();
        assert(c1.stock.top() == 10);
        assert(c1.trash[1].top() == 6);
        assert(c1.trash[0].empty() == 1);
        assert(c1.trash[3].empty() == 1);
        assert(c1.trash[2].empty() == 1);
	delete c1Ptr;
	}
    
  static void humanTest(){
        std::stack<int> stock;
        stock.push(0);
        stock.push(7);
        stock.push(10);
        stock.push(1);
        stock.push(3);
        
        Board b1;
        
        Human * t1Ptr = new Human(stock, b1, "Tanay");
        Human &t1 = *t1Ptr;
        t1.isTurn = true;
        
        assert(t1.stock.top() == 3);
        t1.stock.pop();
        
        assert(t1.stock.top() == 1);
        t1.stock.pop();
        
        assert(t1.stock.top() == 10);
        t1.stock.pop();
        
        assert(t1.stock.top() == 7);
        t1.stock.pop();
        
        assert(t1.stock.top() == 0);
        t1.stock.pop();
        
        assert(t1.stock.empty()); //check to see if it is empty
        
        
        //refill countdown pile for further testing
        t1.stock.push(0);
        t1.stock.push(7);
        t1.stock.push(5);
        t1.stock.push(3);
        t1.stock.push(1);
        
        //here we wont move the variables into the boards buildpile but into our
        //own defined set as we want to have complete control and are only looking
        // to test functions and member of player and not those of board
        vector<int> set;
        
        //testing moveCountdown
        assert(t1.moveStock(set) == 1);
        assert(t1.stock.top() == 3);
        
        assert(t1.moveStock(set) == 0);
        assert(t1.stock.top() == 3);
        
        t1.hand[0] = 2;
        t1.hand[1] = 4;
        t1.hand[2] = 6;
        t1.hand[3] = 0;
        t1.hand[4] = 12;
        
        
        assert(t1.moveHand(0, set));
        assert(!(t1.moveHand(1, set)));
        
        t1.dumpCard(1, t1.trash[0]);
        assert(t1.trash[0].top() == 4);
        
        assert(t1.moveStock(set) == 1); //3 should now be able to be added
        
        assert(t1.moveTrash(set, t1.trash[0]));
        assert(t1.trash[0].empty());
        
        
        assert(set.size() == 4);
        
        assert(t1.moveStock(set) == 1);
        
        t1.dumpCard(4, t1.trash[1]);
        t1.dumpCard(3, t1.trash[1]);
        
        
        assert(t1.moveTrash(set, t1.trash[1]));
        assert(set.size() == 6);
        assert(t1.trash[1].top() == 12);
        assert(t1.moveStock(set) == 1);
        cout << t1 << endl;
        assert(t1.moveStock(set) == 2);
        delete(t1Ptr);
    }

  static void boardTest(){

    Board board;

    assert(board.deck.size() != 0); //deck should be filled using refilldeck()
    assert(!board.checkifemptydeck());
    assert(board.deck.size() == 162);

    //force empty deck for testing
    for(int x = 0; x < 162; x++){
      board.deck.pop_back();
    }    
    assert(board.checkifemptydeck());
    
    board.refilldeck();
    assert(board.deck.size() != 0);
    assert(!board.checkifemptydeck());
    assert(board.deck.size() == 162);

    //force a "tempbuild" for testing
    vector<int> tempbuild;
    for(int x = 0; x < 12; x++)
      tempbuild.push_back(0);

    board.incrementbuild(tempbuild);
    assert(board.build.size() == 12);

    for(int x = 0; x < 30; x++)
      tempbuild.push_back(10);

    board.incrementbuild(tempbuild);
    assert(board.build.size() == 42);

    for(int x = 0; x < 12; x++)
      assert(board.build.at(x) == 0);
    for(int x = 12; x < 42; x++)
      assert(board.build.at(x) == 10);

  }

};

int main(void){
    cout<<"Running tests..."<<endl;
    Test::boardTest();
    Test::computerTest();
    Test::humanTest();
    cout<<"...All tests passed"<<endl;
}
