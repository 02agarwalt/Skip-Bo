//Final Project for CS120
//Written by Nirmal Krishnan
//Nirmal Krishnan, Shiv Krishnan, Tanay Agarwal, Irving Nestor
//nkrishn9, skrish23, tagarwa2, inestor1
//8 May 2015
//600.120 Intermediate Programming
//Section 2
//Joanne Selinski 

#include "Game.h"

using std::cout;
using std::cin;
using std::endl;

Game::Game(Player * toAdd[6], int playerCount, int size, Board & boardAdd): b1(boardAdd), numPlayers(playerCount), stockSize(size), players(toAdd){}

Game::~Game(){
    for(int i=0; i<numPlayers; i++){
        delete players[i];
    }
}

void Game::runGame(void){
    bool boolEnd = false;
    int playerTurn = -1;
    //used to find which player's turn it is in the case of loading game
    for(int i = 0; i < numPlayers; i++){
        if(players[i]->isTurn){
            playerTurn = i;
        }
    }

    int i;

    if(playerTurn == -1){
        i = 0;
    }else{
        i = playerTurn;
    }

    while(!boolEnd){
        for(; i < numPlayers; i++){
            players[i]->isTurn = true;
            if(players[i]->isHuman()){
                while(true){
                    cout << players[i]->name << "'s Turn:\n";
                    cout << "1)Take your turn\n2)Save Game\n3)Exit\nEnter Choice: ";
                    int choice;
                    bool loopEnd = false;
                    //error checking user input
                    do{
                        try {
                            cin >> choice;
                            if(cin.fail() || choice < 1 || choice > 3)
                                throw new std::invalid_argument("Illegal input");
                            loopEnd = true;
                        } catch (const std::invalid_argument * e) {
                            cout << "Invalid input. Please try again." << endl;
                            cin.clear();
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            delete e;
                        }
                    }while(!loopEnd);
                    //take user turn, aka do nothing
                    if(choice ==1){
                        break;
                    }else if(choice == 2){ 
                        this->saveGame();
                        boolEnd = true;
                        break;
                    }else{
                        boolEnd = true;
                        break;
                    }
                    cout << endl;
                }
                if(boolEnd){
                    break;
                }
            }
            if(!boolEnd){
                if(players[i]->isHuman()){
                    cout << endl;
                    for(int j = 0; j < numPlayers; j++){ //display other player's information
                        if(i!=j){
                            cout << (*players[j]);
                        }
                    }
                }
                if(players[i]->takeTurn()){ //players turn taken
                    boolEnd = true;
                    break;
                }
                players[i]->isTurn = false; //no longer player's turn
                if(boolEnd){
                    break;
                }
            }
        }
        i = 0;
    }
}

//saves the game
void Game::saveGame() {
    
    std::string s;
    cout << "Enter file to save to: ";
    cin >> s;
    std::ofstream myfile;
    myfile.open(s, std::ios::out);
    myfile << numPlayers << endl; //Saving player info
    myfile << stockSize << endl; //Saving stock size
    Board &b = (*players)[0].b1;
    writeVector(myfile, b.deck); //Saving board
    writeVector(myfile, b.build);
    for(int i = 0; i < 4; i++) {
        writeVector(myfile, b.buildpile[i]);
    }
    //saves individual player info
    for(int i = 0; i < numPlayers; i++) {
        Player * p = (players[i]);
        myfile << p->name << endl;
        myfile << p->isHuman() << endl;
        
        myfile << p->isTurn <<endl;
        for(int i = 0; i < 5; i++) {
            myfile << p->hand[i] << " ";
        }
        myfile << endl;
        for(int i = 0; i < 4; i++) {
            writeStack(myfile, p->trash[i]);
        }
        writeStack(myfile, p->stock);
    }
    myfile.close();
    
}

void Game::writeVector(std::ofstream &myfile, const vector<int> & v1) {
    for(unsigned int i = 0; i < v1.size(); i++) {
        myfile << v1[i] << " ";
    }
    myfile << "-2" << endl;
}

void Game::writeStack(std::ofstream &myfile, stack<int> s1) {
  while(s1.size() > 0) {
        myfile << s1.top() << " ";
        s1.pop();
    }
    myfile << "-2" << endl;
    
    
}