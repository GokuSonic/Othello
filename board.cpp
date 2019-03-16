/* implementation file*/

#include "board.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>



//constructor
board::board()
{
    //inital state of the board
    for(int i =0; i <8; i++)
    {
      for(int j=0; j<8; j++)
	{
	   othello_field[i][j] = ' ';
	}
    }

    //i had a plan here but went with another... 

    /*    //zero out position arrays
    for(int i =0; i<31 ; i++)
    {
        black_array [i]=0;
        white_array [i]=0;
    }
    */

   //starting 4 pieces
   othello_field[3][3]= 'B';
   othello_field[3][4]= 'W';
   othello_field[4][3]= 'W';
   othello_field[4][4]= 'B';



   //we now have 2 pieces and denote player as black and agent as white
   black_pieces = 2;
   white_pieces = 2;
   

   player = 'B';
   agent = 'W';


}

//deconstructor
board::~board()
{
}



// find the current player move's  pieces
//when found check  (in the continuing) up down left right diagonal for oposing player pieces
// if found at direction check opposing direction if space  is ' '
//then is possible move change to current counter space.



//generate possible moves (NEEDS FLIP AMOUNT FUNCTION)
void board::generateMoves(char player)
{
    //search the board for possible moves from top left to bottom right 
    for(int i =0; i <8; i++)
    {
        for(int j=0; j<8; j++)
        {
            if (othello_field[i][j] == player)
	    {
	       cout << "found spot";
               
	    }       
        }
    }

}


//checks if valid spot
void board::isValidSpot(int row,int column)
{


}



//public function that displays the current state of the board
void board::drawBoard()
{

    //formating
    cout << "  ";
    //displays the numbering on the top of the board
    for(int i =0; i <8; i++)
    {
      cout << i+1 <<" ";

    }
    cout <<endl;

    //displays the rows and content of the baord
    for(int i =0; i <8; i++)
    {
         //formatting
         cout << i+1 <<"|";
         for(int j=0; j<8; j++)
	 {
             cout << othello_field[i][j] << "|";
	 } 
         cout <<endl;
    }

}
