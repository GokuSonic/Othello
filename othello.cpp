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
    

       myGame.generateMoves();

       cout << "Choose one of the moves: ";
       cin >> move;

       myGame.sendMove(move);

       /*
        //the AI's turn
       cout <<"\n----Ai's turn----" <<endl;
       myGame.generateMoves();

       cout << "Choose one of the moves: " << endl;
       cin >> move;

       myGame.sendMove(move);

       */


        //end of do while loop
 
        //find winner of game goes here

    }while(true);

    return 0;
}



