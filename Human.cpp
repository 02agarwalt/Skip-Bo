//Final Project for CS120
//Written by Nirmal Krishnan
//Nirmal Krishnan, Shiv Krishnan, Tanay Agarwal, Irving Nestor
//nkrishn9, skrish23, tagarwa2, inestor1
//8 May 2015
//600.120 Intermediate Programming
//Section 2
//Joanne Selinski 

#include "Human.h"
#include <stdlib.h>
#include <exception>
#include <stdexcept>

using std::cout;
using std::cin;
using std::endl;

Human::Human(std::stack<int> & stock, Board & toAdd, std::string nameAdd): Player(stock, toAdd, nameAdd){
}

Human::Human(std::string name1, bool isTurn1, int hand1[5], std::stack<int> & stockAdd, Board & boardAdd, std::stack<int> trash1[4]): Player(name1, isTurn1, hand1, stockAdd, boardAdd, trash1) {
}

Human::~Human(){
}

bool Human::isHuman() const{
    return true;
}

bool Human::takeTurn(){

    while (true)
    {
        if(Player::isEmpty())
            Player::fillHand();
        cout << endl;
        b1.displayBuilds();
        cout << endl;
        cout << *this;
        //print menu
        cout << endl;
        cout << this->name << "'s Turn:" << endl;
        cout << "1) Move card from hand to build pile\n";
        cout << "2) Move card from discard pile to build pile\n";
        cout << "3) Move card from stock pile to build pile\n";
        cout << "4) Move card from hand to discard pile\n";
        
        //take user input
        int choice = 0;
        do
        {
            try
            {
                cout << "Enter choice: ";
                cin >> choice;
                if(cin.fail()) throw new std::invalid_argument("Illegal input");
            }
            catch(const std::invalid_argument * e)
            {
                cout << "Invalid choice. Please enter a valid number from 1 to 6:\n";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                delete e;
            }
        } while (!(choice >= 1 && choice <= 6));
        
        if(choice == 1)
        {
            cout << "Select card from hand: ";
            int choice2;
            try
            {
                //check if input is a number
                cin >> choice2;
                if(cin.fail()) throw new std::invalid_argument("Invalid choice");
                
                //check if input exists in hand
                bool cardExists = false;
                int handPos = -1;
                for(int i = 0; i < 5; i++)
                {
                    if(choice2 == this->hand[i])
                    {
                        cardExists = true;
                        handPos = i;
                    }
                }
                if(!cardExists) throw new std::domain_error("Card doesn't exist in hand");
                
                //take input for build pile choice
                int choice3;
                cout << "Enter build pile to move card into: ";
                cin >> choice3;
                if(cin.fail() || choice3< 1 || choice3 > 4){
                    cout << "This build pile does not exist" << endl;
                }
                else{
                    if(!moveHand(handPos, b1.buildpile[choice3-1])){
                        cout << "This move is not valid" << endl;
                    }
                }
            }
            catch(const std::invalid_argument *  e)
            {
                cout << e->what() << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                delete e;
            }
            catch(const std::domain_error * e)
            {
                cout << e->what() << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                delete e;
            }
            
        }
        else if(choice == 2)
        {
            cout << "Which discard pile would you like to move cards from: ";
            int choice2;
            try
            {
                //check if input is a number
                cin >> choice2;
                if(cin.fail() || choice2 > 4 || choice2 < 1) throw new std::invalid_argument("Invalid choice");
                //take input for build pile choice
                int choice3;
                cout << "Enter build pile to move card into: ";
                cin >> choice3;
                if(cin.fail() || choice3< 1 || choice3 > 4){
                    cout << "This build pile does not exist" << endl;
                }
                else{
                    if(!moveTrash(b1.buildpile[choice3-1], this->trash[choice2-1])){
                        cout << "This move is not valid" << endl;
                    }
                }
            }
            catch(const std::invalid_argument * e)
            {
                cout << e->what() << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                delete e;
            }
        }
        else if(choice == 3)
        {
            cout << "Which build pile would you like to move the stock pile card to: ";
            int choice2;
            try
            {
                //check if input is a number
                cin >> choice2;
                if(cin.fail() || choice2 > 4 || choice2 < 1) throw new std::invalid_argument("Invalid choice");
                //take input for build pile choice
                int result = moveStock(b1.buildpile[choice2-1]);
                if(result == 0){
                    cout << "This move is not valid" << endl;
                }else if(result == 2){
                    cout << this->name << " wins!" << endl;
                    return true;
                }
            }
            catch(const std::invalid_argument *  e)
            {
                cout << e->what() << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                delete e;
            }
            
        }
        else if(choice == 4){
            cout << "Select card from hand: ";
            int choice2;
            try
            {
                //check if input is a number
                cin >> choice2;
                if(cin.fail()) throw new std::invalid_argument("Invalid choice");
                
                //check if input exists in hand
                bool cardExists = false;
                int handPos = -1;
                for(int i = 0; i < 5; i++)
                {
                    if(choice2 == this->hand[i])
                    {
                        cardExists = true;
                        handPos = i;
                    }
                }
                if(!cardExists) throw new std::domain_error("Card doesn't exist in hand");
                
                //take input for discard pile choice
                int choice3;
                cout << "Enter discard pile to move card into: ";
                cin >> choice3;
                if(cin.fail() || choice3< 1 || choice3 > 4){
                    cout << "This discard pile does not exist" << endl;
                }
                else{
                    dumpCard(handPos, this->trash[choice3-1]);
                    this->isTurn = false;
                    break;
                }
            }
            catch(const std::invalid_argument * e)
            {
                cout << e->what() << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                delete e;
            }
            catch(const std::domain_error * e)
            {
                cout << e->what() << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                delete e;
            }
            
        }
    }
    Player::fillHand();
    return false;
}

