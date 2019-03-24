#include <iostream>
#include "board.h"


//start of the game
int main()
{

    //creates a new instance of the game
    board myGame;
    char move;

    //do while loop goes here

    do
    {
    
       cout << "\n\n----Human's Turn----\n" << endl;       
       myGame.generateMoves();

       cout << "Choose one of the moves: ";
       cin >> move;

       myGame.sendMove(move);

       cout << "\n\n\t----Computer's Turn----\n" << endl;       
       myGame.aiTurn(3);
 
       //keeps going until the game is over 
    }while(!myGame.checkIfEnd());

    myGame.findWinner();

    return 0;
}



