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

   //starting 4 pieces
   othello_field[3][3]= 'W';
   othello_field[3][4]= 'B';
   othello_field[4][3]= 'B';
   othello_field[4][4]= 'W';

   //test board pieces this will seg fault
   /* othello_field[0][0]= 'W';
   othello_field[7][7]= 'W';
   othello_field[0][7]= 'W';
   othello_field[7][0]= 'W';

   othello_field[0][1]= 'B';
   othello_field[6][7]= 'B';
   othello_field[0][6]= 'B';
   othello_field[6][0]= 'B';
   */



   //we now have 2 pieces and denote player as black and agent as white
   black_pieces = 2;
   white_pieces = 2;
   
   //sets the players icons
   player = 'B';
   agent = 'W';

   //set up turn number
   turnNumber =0;

}


//deconstructor
board::~board()
{
}



//Determines who's turn it is
char board:: whosTurn()
{
   if(turnNumber % 2 ==1)
      return 'W';
   else
      return 'B';    

}



//generate possible moves (NEEDS FLIP AMOUNT FUNCTION)
void board::generateMoves()
{

   //clear the array of spots found
   for(int i =0; i <2; i++)
   {
      for(int j=0; j<64; j++)
        {
	  possibleMove[i][j] = -1;
        }
   }

    //gets the current player
    player =  whosTurn();
    char s_player;
     
    //searches for the other player's pieces
    if (player == 'W')
      s_player = 'B';
    else
      s_player = 'W';

 
    //search the board for possible moves from top left to bottom right 
    for(int i =0; i <8; i++)
    {
        for(int j=0; j<8; j++)
        {
	    //is the space isnt blank then check if its the other player
            if (othello_field[i][j] == s_player)
	    {
	      cout << "found spot " << i << " , " << j << " for: " << s_player <<endl;           
                isValidSpot(i,j);   
	    }       
        }
    }

    drawBoard();
}


//from the found spots check spaces around those for possible moves
void board::checker()
{



}



//checks if valid spot
bool board::isValidSpot(int row,int column)
{
     int flip, temp_row,temp_col;   

  
     //gets the current player
     player =  whosTurn();  

     //check up
     if(othello_field[row -1][column] == ' ')
     {
        
         flip =0;     
         temp_row =row;
	 temp_col= column;
         
       
         while( othello_field[temp_row][temp_col] != player)
	 {
 
    	     flip ++;
             temp_row ++;
	 }
         
         if(flip >0)
	 {

	   othello_field[row-1][column] = (char) (flip+48);
	 }
     }

     //check left
     if(othello_field[row][column-1] == ' ')
     {

         flip =0;
         temp_row =row;
         temp_col= column;


         while( othello_field[temp_row][temp_col] != player)
	 {

             flip ++;
             temp_col ++;
	 }

         if(flip >0)
	 {

	     othello_field[row][column-1] = (char) (flip+48);
	 }
     }


     //check down
     if(othello_field[row+1][column] == ' ')
     {

         flip =0;
         temp_row =row;
         temp_col= column;


         while( othello_field[temp_row][temp_col] != player)
	   {

             flip ++;
             temp_row --;
	   }

         if(flip >0)
	   {

             othello_field[row+1][column] = (char) (flip+48);
	   }
       }

     //check right
     if( othello_field[row][column+1] == ' ')
     {

         flip =0;
         temp_row =row;
         temp_col= column;


         while( othello_field[temp_row][temp_col] != player)
	   {

             flip ++;
             temp_col --;
	   }

         if(flip >0)
	   {

             othello_field[row][column+1] = (char) (flip+48);
	   }
       }



}



//public function that displays the current state of the board
void board::drawBoard()
{

    //formating
    cout << "  ";
    //displays the numbering on the top of the board
    for(int i =0; i <8; i++)
    {
      cout << i <<" ";

    } 
    cout <<endl;

    //displays the rows and content of the baord
    for(int i =0; i <8; i++)
    {
         //formatting
         cout << i <<"|";
         for(int j=0; j<8; j++)
	 {
             cout << othello_field[i][j] << "|";
	 } 
         cout <<endl;
    }

}
