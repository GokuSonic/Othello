/* implementation file*/

#include "board.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>



//constructor
board::board()
{

    move_count =0;

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

   move my_move;
   //clear the array of spots found
   for(int i =0; i>move_count; i++)
   {
       possible_moves[i] =my_move;      
 
   }
   move_count =0;

    //gets the current player
    player =  whosTurn();
    //search able player
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
	      isValidSpot(i,j,player);   
	    }       
        }
    }

    drawBoard();
}




//checks if valid spot
void board::isValidSpot(int row,int column, char current_player)
{
     int flip, temp_row,temp_col;   
     
     move my_move;


     //check up
     if(row != 0)
     {
          if(othello_field[row -1][column] == ' ')
          {
        
             flip =0;     
             temp_row =row;
	     temp_col= column;
         
       
             while( othello_field[temp_row][temp_col] != player )
    	     {
 
    	         flip ++;
                 temp_row ++;
	     }
         
             if(flip >0)
	     {

	         othello_field[row-1][column] = (char) (move_count+48);
	   
	         my_move.dir = UP;
	         my_move.flip_count = flip;
                 my_move.row = row -1;
		 my_move.column = column;
           
		 possible_moves[move_count] = my_move;
		 move_count ++;

	     }
          }
     }

     //check left
     if(column !=0)
     { 
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

	          othello_field[row][column-1] = (char) (move_count+48);

		  my_move.dir = LEFT;
		  my_move.flip_count = flip;
		  my_move.row = row;
		  my_move.column = column-1;

		  possible_moves[move_count] = my_move;
		  move_count ++;

	        }
	  }
     }

     //check down
     if(row !=7)
     {
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

                 othello_field[row+1][column] = (char) (move_count+48);
            
                 my_move.dir = DOWN;
                 my_move.flip_count = flip;
		 my_move.row = row +1;
		 my_move.column = column;

		 possible_moves[move_count] = my_move;
		 move_count ++;

	      }
           }
     }

      //check right
      if(column !=7)
      {
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

		 othello_field[row][column+1] = (char) (move_count+48);
   
                 my_move.dir = RIGHT;
		 my_move.flip_count = flip;
		 my_move.row = row;
		 my_move.column = column+1;

		 possible_moves[move_count] = my_move;
		 move_count ++;

	       }
	    }
      }

}


//finializes the move to the board clears all the numbers on the board
//updates black and white pieces
//update move count

void board::sendMove(int choice)
{


  move temp_move =  possible_moves[choice];
  int flip = temp_move.flip_count;
  int row = temp_move.row;
  int column = temp_move.column;
  

  char current_player =  whosTurn();



  //switch case for moves 
  //in enum up = 0 down = 1

  switch (temp_move.dir)
  {

      case 0:
	othello_field[row][column] = current_player;
        black_pieces ++;

	for(int i =0; i<flip;i++)
	{  
	   
	    row ++;
            othello_field[row][column] = current_player;
            black_pieces ++;
            white_pieces--;

	}
      break;
      
      case 1:
      break;

      case 2:
      break;

      case 3:
      break;

      case 4:
      break;

      case 5:
      break;

      case 6:
      break;

      case 7:
      break;

      case 8:
      break;

      default:
      break;

  }


  
   //leave all but B and W spaces
   for(int i =0; i <8; i++)
    {

      for(int j=0; j<8; j++)
      {
            //change all the number spaces to ' ' spaces again
	

            //jane woke up fix this
	    if(othello_field[i][j] == 'W')
	    {

	    }
            else if(othello_field[i][j] == 'B')
	    {

	    }    
            else
              othello_field[i][j] = ' ';

      }

    }
    
   //Increase the turn number 
   turnNumber++;

   drawBoard();

}



//public function that displays the current state of the board
void board::drawBoard()
{

  cout << "*****Turn: " << turnNumber+1 << " *****" <<endl;
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

    cout << "Black Pieces: " << black_pieces << endl;
    cout << "White Pieces: " << white_pieces << endl;

}
