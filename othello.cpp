
#include <iostream>
#include "board.h"


//start of the game
int main()
{

    //creates a new instance of the game
    board myGame;
    int move;

    cout <<"\n----Player's turn----" <<endl;
    myGame.generateMoves();
    cout << "Choose one of the moves: " << endl;
    cin >> move;



    return 0;
}



