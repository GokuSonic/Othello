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

  //we now have 2 pieces and denote player as black and agent as white
  black_pieces = 2;
  white_pieces = 2;
   
  //set up turn number
  turnNumber =0;

  //test array of linked list defines an array of node pointers
  Node* possibleMoves[20];

  //initalize the linked list array
  clearLinkedList();


}
//deconstructor
board::~board()
{
  
  clearLinkedList();

}


//Determines who's turn it is
char board:: whosTurn()
{
  if(turnNumber % 2 ==1)
    {
      return 'W';
    }
  else
    {
      return 'B';    
    }
}


//generate possible moves 
void board::generateMoves()
{

  move my_move;
  //clear the array of spots found
  for(int i = 0; i < move_count; i++)
    {
      possible_moves[i] = my_move;      
 
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
  for(int i =0; i < 8; i++)
    {
      for(int j=0; j < 8; j++)
        {
	  //is the space isnt blank then check if its the other player
	  if (othello_field[i][j] == s_player)
	    {
	      //       cout << "found spot " << i << " , " << j << " for: " << s_player <<endl;           
	      isValidSpot(i,j,player);   
	    }       
        }
    }
  drawBoard();
}




void board::clearLinkedList()
{
  //initializes the array to NULL
  for(int i =0; i<20; i++)
    {
      possibleMoves[i] = NULL;
    }
}


void board::addMove(int index, move newMove)
{


  Node  *n1 = new Node;
  Node  *n2 = new Node;
  n1->aMove = newMove;
  n1->Next =NULL;

  bool samePositionFound = false;

  //search array for moves that have the same row/column move        
  for(int i =0; i<index-1;i++)
    {         
      cout << "index= " << i <<endl;
      n2 = possibleMoves[i];

      //make sure the poisition isnt null first
      if(n2 != NULL)
	{  
	  for (n2 = possibleMoves[i]; n2->Next != NULL && !samePositionFound; n2=n2->Next)
	    {
	         
	      move temp_move = n2->aMove;
	      cout << "node search " << "\n temp move row= " << temp_move.row  << " col= " << temp_move.column << endl;
	      cout << "move row = " << newMove.row << " column = " << newMove.column << endl;
	      if(temp_move.row == newMove.row && temp_move.column == newMove.column)
		{
		  cout << "\nfound\n" <<endl;
		  samePositionFound = true;       
		  n2->Next = n1;
		}
	    }
	}

      //Add the new loaction if cant find a match
    }
  if(!samePositionFound)
    {   
      if(possibleMoves[index] ==NULL)
	{     
	  cout <<"adding" <<endl;
	  possibleMoves[index] =n1;
	}
    }   


  //see whats in the linked list debugging only
  for(int i =0; i<=index;i++)
    {
      cout << "index= " <<  i  <<endl;
      n2 = possibleMoves[i];
      cout << "move details: " <<"\n\t";
      move temp = n2->aMove;
      cout << "row= " << temp.row << " col= " << temp.column;
      cout << "\n\t dir = " << temp.dir << endl;
 
    }
  
}




//checks if valid spot
void board::isValidSpot(int row,int column, char current_player)
{
  int flip, temp_row,temp_col;   
  
  move my_move;
  
  //check up
  if(row != 0)
    {
      //      if(othello_field[row -1][column] == ' ')
      //{
        
      flip =0;     
      temp_row = row;
      temp_col= column;

      if(temp_row != 7)
	{
	  while( othello_field[temp_row][temp_col] != player)
	    {
	      if(  othello_field[temp_row][temp_col] == ' ') //|| (othello_field[temp_row][temp_col] >= (char)48 && othello_field[temp_row][temp_col] <= (char)57))
		{
		  flip = 0;
		  break;
		}
	      flip ++;
	      temp_row ++;
	    }
	}     
      if(flip >0)
	{
	  if(othello_field[row-1][column] == ' ')
	    {
	      othello_field[row-1][column] = (char) (move_count+48);
	    }
	  my_move.dir = UP;
	  my_move.flip_count = flip;
	  my_move.row = row -1;
	  my_move.column = column;
	        
	  addMove(move_count,my_move);
	      
	  cout << "\tup\tRow = " << row << " column = " << column << endl;


	  possible_moves[move_count] = my_move;
	  move_count ++;
	}
      //}
    }

  
  //check left
  if(column !=0)
    { 
      // if(othello_field[row][column-1] == ' ')
      //{
        
      flip =0;
      temp_row =row;
      temp_col= column;
        
      if(temp_col != 7)
	{
	  while( othello_field[temp_row][temp_col] != player)
	    {
	      if(  othello_field[temp_row][temp_col] == ' ')// || (othello_field[temp_row][temp_col] >= (char)48 && othello_field[temp_row][temp_col] <= (char)57))
		{
		  flip = 0;
		  break;
		}
	        
	      flip ++;
	      temp_col ++;
	    }
	}
      if(flip >0)
	{
	  if(othello_field[row][column-1] == ' ')
	    {
	      othello_field[row][column-1] = (char) (move_count+48);
	    }   
	  my_move.dir = LEFT;
	  my_move.flip_count = flip;
	  my_move.row = row;
	  my_move.column = column-1;
	        
	  addMove(move_count,my_move);

	  cout << "\tleft\tRow = " << row << " column = " << column << endl;

	  possible_moves[move_count] = my_move;
	  move_count ++;
	}
      //}
    }
  
  
  //check down
  if(row !=7)
    {
      // if(othello_field[row+1][column] == ' ')
      //{
        
      flip =0;
      temp_row =row;
      temp_col= column;
      if(temp_row != 0)
	{
	  while( othello_field[temp_row][temp_col] != player)
	    {
	      if(  othello_field[temp_row][temp_col] == ' ')// || (othello_field[temp_row][temp_col] >= (char)48 && othello_field[temp_row][temp_col] <= (char)57))
		{
		  flip = 0;
		  break;
		}
	        
	      flip ++;
	      temp_row --;
	    }
	}
        
      if(flip >0)
	{
	  if(othello_field[row+1][column] == ' ')
	    {
	      othello_field[row+1][column] = (char) (move_count+48);
	    }
	  my_move.dir = DOWN;
	  my_move.flip_count = flip;
	  my_move.row = row +1;
	  my_move.column = column;
	        
	  addMove(move_count,my_move);

	  cout << "\tdown\tRow = " << row+1  << " column = " << column << endl;
	  possible_moves[move_count] = my_move;
	  move_count ++;
	}
      //}
    }
  


  //check right
  if(column !=7)
    {
      // if( othello_field[row][column+1] == ' ')
      //{
        
      flip =0;
      temp_row =row;
      temp_col= column;
        
      if(temp_col != 0)
	{
	  while( othello_field[temp_row][temp_col] != player)
	    {
	      if(  othello_field[temp_row][temp_col] == ' ' )//|| (othello_field[temp_row][temp_col] >= (char)48 && othello_field[temp_row][temp_col] <= (char)57))
		{
		  flip = 0;
		  break;
		}
	        
	      flip ++;
	      temp_col --;
	    }
	}
      if(flip >0)
	{
	  if(othello_field[row][column+1] == ' ')
	    {
	      othello_field[row][column+1] = (char) (move_count+48);
	    }
	  my_move.dir = RIGHT;
	  my_move.flip_count = flip;
	  my_move.row = row;
	  my_move.column = column+1;

	  addMove(move_count,my_move);
              
	  cout << "\tright\tRow = " << row << " column = " << column+1 << endl;      
	  possible_moves[move_count] = my_move;
	  move_count ++;
	}
      //}
    }
  



  //upLeft
  if(row != 0 || column != 0)
    {
      //   if(othello_field[row -1][column - 1] == ' ')
      //{
        
      flip =0;
      temp_row = row;
      temp_col= column;
      if(temp_row != 7 || temp_col != 7)
	{
	  while( othello_field[temp_row][temp_col] != player)
	    {
	      if(  othello_field[temp_row][temp_col] == ' ')// || (othello_field[temp_row][temp_col] >= (char)48 && othello_field[temp_row][temp_col] <= (char)57))
		{
		  flip = 0;
		  break;
		}
	        
	      flip ++;
	      temp_row++;
	      temp_col++;
	    }
	}
      if(flip >0)
	{
	  if(othello_field[row-1][column-1] == ' ')
	    {
	      othello_field[row-1][column - 1] = (char) (move_count+48);
	    }
	  my_move.dir = upLeft;
	  my_move.flip_count = flip;
	  my_move.row = row -1;
	  my_move.column = column - 1;
	        
	  addMove(move_count,my_move);

	  possible_moves[move_count] = my_move;
	  move_count ++;
	}
      //}
    }




  //upRight
  if(row != 0 || column != 7)
    {
      //   if(othello_field[row -1][column + 1] == ' ')
      //{
        
      flip =0;
      temp_row = row;
      temp_col= column;
        
      if(temp_row != 7 || temp_col != 0)
	{
	  while( othello_field[temp_row][temp_col] != player)
	    {
	      if(  othello_field[temp_row][temp_col] == ' ')// || (othello_field[temp_row][temp_col] >= (char)48 && othello_field[temp_row][temp_col] <= (char)57))
		{
		  flip = 0;
		  break;
		}
	        
	      flip ++;
	      temp_row++;
	      temp_col--;
	    }
	}
      if(flip >0)
	{
	  if(othello_field[row-1][column+1] == ' ')
	    {
	      othello_field[row-1][column + 1] = (char) (move_count+48);
	    }  
	  my_move.dir = upRight;
	  my_move.flip_count = flip;
	  my_move.row = row -1;
	  my_move.column = column + 1;


	  addMove(move_count,my_move);

	        
	  possible_moves[move_count] = my_move;
	  move_count ++;
	}
      //}
    }



  //downLeft
  if(row != 7 || column != 0)
    {
      //   if(othello_field[row + 1][column - 1] == ' ')
      //{
      
      flip =0;
      temp_row = row;
      temp_col= column;
        
      if(temp_row != 0 || temp_col != 7)
	{
	  while( othello_field[temp_row][temp_col] != player)
	    {
	      if(  othello_field[temp_row][temp_col] == ' ')// || (othello_field[temp_row][temp_col] >= (char)48 && othello_field[temp_row][temp_col] <= (char)57))
		{
		  flip = 0;
		  break;
		}
	      
	      flip ++;
	      temp_row--;
	      temp_col++;
	    }
	}
      if(flip >0)
	{
	  if(othello_field[row-1][column+1] == ' ')
	    {
	      othello_field[row-1][column + 1] = (char) (move_count+48);
	    }
	  my_move.dir = downLeft;
	  my_move.flip_count = flip;
	  my_move.row = row + 1;
	  my_move.column = column - 1;


	  addMove(move_count,my_move);
	      
	  possible_moves[move_count] = my_move;
	  move_count ++;
	      
	}
      //}
    }



  //downRight
  if(row != 7 || column != 7)
    {
      // if(othello_field[row + 1][column + 1] == ' ')
      //{
        
      flip =0;
      temp_row = row;
      temp_col= column;
      if(temp_row != 0 || temp_col != 0)
	{
	  while( othello_field[temp_row][temp_col] != player)
	    {
	      if(  othello_field[temp_row][temp_col] == ' ' )//|| (othello_field[temp_row][temp_col] >= (char)48 && othello_field[temp_row][temp_col] <= (char)57))
		{
		  flip = 0;
		  break;
		}
	        
	      flip ++;
	      temp_row--;
	      temp_col--;
	    }
	}
      if(flip >0)
	{
	  if(othello_field[row+1][column+1] == ' ')
	    {
	      othello_field[row+1][column + 1] = (char) (move_count+48);
	    }
	  my_move.dir = downRight;
	  my_move.flip_count = flip;
	  my_move.row = row + 1;
	  my_move.column = column + 1;

	  addMove(move_count,my_move);
	        
	  possible_moves[move_count] = my_move;
	  move_count ++;
	        
	}
      //}
    }


}

void board::updatePieces()
{

  char current_player =  whosTurn();

  if(current_player == 'W')
    {
      white_pieces ++;
      black_pieces --;
    }
  else
    {
      white_pieces --;
      black_pieces ++;
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

  //this is done first since you are placing the orginal piece
  if(current_player == 'B')
    black_pieces ++;
  else
    white_pieces ++;

  //switch case for moves 
  //in enum up = 0 down = 1
  switch (temp_move.dir)
    {

    case 0:
      othello_field[row][column] = current_player;

      for(int i =0; i<flip;i++)
	{  
	         
	  row ++;
	  othello_field[row][column] = current_player;
          updatePieces();

	}
      break;
      
    case 1:
      othello_field[row][column] = current_player;

      for(int i =0; i<flip;i++)
        {

          row --;
          othello_field[row][column] = current_player;
	  updatePieces();

        }

  
      break;

    case 2:
      othello_field[row][column] = current_player;

      for(int i =0; i<flip;i++)
	{

          column ++;
          othello_field[row][column] = current_player;
          updatePieces();

	}

      break;

    case 3:
      othello_field[row][column] = current_player;

      for(int i =0; i<flip;i++)
	{

          column --;
          othello_field[row][column] = current_player;
          updatePieces();

	}

      break;

    case 4:
      othello_field[row][column] = current_player;

      for(int i =0; i<flip;i++)
	{

          column ++;
	  row ++;
          othello_field[row][column] = current_player;
          updatePieces();

	}

      break;

    case 5:
      othello_field[row][column] = current_player;

      for(int i =0; i<flip;i++)
	{

          column --;
          row ++;
          othello_field[row][column] = current_player;
          updatePieces();

	}


      break;

    case 6:
      othello_field[row][column] = current_player;

      for(int i =0; i<flip;i++)
	{

          column ++;
          row --;
          othello_field[row][column] = current_player;
          updatePieces();

	}

      break;

    case 7:
      othello_field[row][column] = current_player;

      for(int i =0; i<flip;i++)
	{

          column --;
          row --;
          othello_field[row][column] = current_player;
          updatePieces();

	}

      break;

   
    default:

      cout << "No MOVES chosen" << endl;
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
	    {}
	  else if(othello_field[i][j] == 'B')
	    {}    
	  else
	    othello_field[i][j] = ' ';
	}
      
    }
    
  //Increase the turn number 
  turnNumber++;
  clearLinkedList();



}



//public function that displays the current state of the board
void board::drawBoard()
{

  cout << "*****Turn: " << turnNumber+1 << " *****" <<endl;
  cout << "     Go player : " <<  whosTurn()<< endl;

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
