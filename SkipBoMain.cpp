//Final Project for CS120
//Written by Nirmal Krishnan, Shiv Krishnan, and Tanay Agarwal
//Nirmal Krishnan, Shiv Krishnan, Tanay Agarwal, Irving Nestor
//nkrishn9, skrish23, tagarwa2, inestor1
//8 May 2015
//600.120 Intermediate Programming
//Section 2
//Joanne Selinski 

#include "Game.h"
#include <stack>
#include <random>
#include <time.h>
#include <exception>
#include <stdexcept>
#include <string>
#include <limits>

using std::cout;
using std::cin;
using std::endl;

//opposite of write vector
void readVector(std::ifstream &myfile, std::vector<int> &v1) {
  int n;
  myfile >> n;
  while(n != -2) {
      v1.push_back(n);
      myfile >> n;
  }
}

//opposite of write stack
void readStack(std::vector<int> &v1, std::stack<int> &s1) {
  for(int i = v1.size() - 1; i >= 0; i--)
    s1.push(v1.at(i));
}

int main(){
    srand(time(NULL));
    Board board;
    int numPlayers;
    int stockSize;
    int choice;
    Player * players[6];
    bool doCheck = false;
    //pre-menu
    do{
        try{
            cout << "1.Start new game" << endl;
            cout << "2.Load existing game" << endl;
            cout << "Choose choice: ";
            cin >> choice;
            if(cin.fail() || (choice != 1 && choice != 2)){
                throw new std::invalid_argument("Illegal input");
            }
            doCheck = true;
        }catch(const std::invalid_argument * e){
            cout << endl;
            cout << "Invalid choice.\n" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            delete e;
        }
    }while (!doCheck);

    if(choice == 1){
        do{ //gathers player information
    		try{
    			cout << "How many players will be playing? ";
    			cin >> numPlayers;
    			if(cin.fail() || numPlayers < 2 || numPlayers > 6)
                    throw new std::invalid_argument("Illegal input");
    		}
            catch(const std::invalid_argument * e){
    			cout << "Invalid choice. Please enter a valid number from 2 to 6:\n";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                delete e;
    		}
    	}while(!(numPlayers >=2 && numPlayers <=6));
        bool loopEnd = false;
        do{ //gathers stock pile information
    		try{
    			cout << "How large are your stock piles? (Enter 0 for Default): ";
    			cin >> stockSize;
                if(stockSize == 0){
                    if(numPlayers >= 2 && numPlayers <= 4){
                        stockSize = 30;
                    }else if(numPlayers == 5 || numPlayers == 6){
                        stockSize = 20;
                    }
                }
            
                if(numPlayers >= 2 && numPlayers <= 4){ //error checking stock piles based on number of plyaers
                    if(cin.fail() || stockSize > 30 || stockSize <= 0) throw new std::invalid_argument("Illegal input");
                }
                if(numPlayers == 5 || numPlayers == 6){
                    if(cin.fail() || stockSize > 20 || stockSize <= 0) throw new std::invalid_argument("Illegal input");
                }
                loopEnd = true;
    		}catch(const std::invalid_argument * e){
                cout << "Invalid size. Please try again." << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                delete e;
    		}
    	}while(!(loopEnd));

    	for(int i = 0; i < numPlayers; i++){
    		std::string playerName;
    		char isComp;
    		cout << "Enter the name of player " << (i+1) << ": ";
    		cin >> playerName;
            bool exceptionCheck = false;
            do{
                try{
                    cout << "Is " << playerName << " a human or a computer (h/c): ";
                    cin >> isComp;
                    if(cin.fail() || (isComp != 'h' && isComp != 'c'))
                        throw new std::invalid_argument("Illegal input");
                    exceptionCheck = true;
                }
                catch(const std::invalid_argument * e){
                    cout << "Invalid input. Please try again." << endl;
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    delete e;
                }
            }while(!exceptionCheck);
    		std::stack<int> tempstack; //temporary stack creating to player stock piles from deck
    		for(int i = 0; i <  stockSize; i++) {
                tempstack.push(board.deck.back());
    			board.deck.pop_back();
    		}
    		if(isComp == 'h'){
                players[i] = new Human(tempstack, board, playerName);
    		}else if(isComp == 'c'){
    			players[i] = new Computer(tempstack, board, playerName);

    		}
            cout << "Created Player Successfully" << endl;
    	}
        Game g1(players, numPlayers, stockSize, board);
        cout << endl;
        g1.runGame();
    }
    else { //loading menu option
        std::string s;
        std::ifstream myfile;
        bool loopCheck = false;
        do{
            cout << "Enter file to load from: ";
            try{
                cin >> s;
                myfile.open(s, std::ios::in);
                if(myfile.fail()){
                    throw new std::invalid_argument("\nThe file you entered cannot be opened. \n");
                }
                loopCheck = true;
            }
            catch(const std::invalid_argument * e){
                cout << e->what() << endl;
                delete e;
            }
        }while(!loopCheck);
        //opposite of saving functions, loads back into game object
        myfile >> numPlayers;
        myfile >> stockSize;
        vector<int> deck1;
        readVector(myfile, deck1);
        vector<int> build1;
        readVector(myfile, build1);
        vector<int> buildpile1[4];
        for(int i = 0; i < 4; i++) {
          readVector(myfile, buildpile1[i]);
        }

        Board board(deck1, build1, buildpile1); 

        for(int i = 0; i < numPlayers; i++) {
            std::string name1;
            myfile >> name1;
            bool isHuman1;
            myfile >> isHuman1;
            bool isTurn1;
            myfile >> isTurn1;
            int hand1[5];
            for(int j = 0; j < 5; j++) {
                myfile >> hand1[j];
            }
            stack<int> trash1[4]; 
            vector<int> trash2[4];
            for(int j = 0; j < 4; j++) {
                readVector(myfile, trash2[j]);
                readStack(trash2[j], trash1[j]);
            }
            stack<int> stock1;
            vector<int> stock2;
            readVector(myfile, stock2);
            readStack(stock2, stock1);
            if(isHuman1) {
                players[i] = new Human(name1, isTurn1, hand1, stock1, board, trash1);
            }
            else {
                players[i] = new Computer(name1, isTurn1, hand1, stock1, board, trash1);
            }
        }
        myfile.close();
        Game g1(players, numPlayers, stockSize, board);
        cout << endl;
        g1.runGame();
      }
    return 0;
}
