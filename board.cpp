//* implementation file*/

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
  

  //we now have 2 pieces and denote player as black and agent as white
  black_pieces = 2;
  white_pieces = 2;
   
  //set up turn number
  turnNumber =0;

}
//deconstructor
board::~board()
{
  
  clearVector();

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
  //clear the vector of spots found
  //for(int i = 0; i < totalMoves.size(); i++)
  //  {
      
  //  }
 
  //gets the current player
  player =  whosTurn();
  //search able player
  char s_player;
     
  //searches for the other player's pieces
  if (player == 'W')
    s_player = 'B';
  else
    s_player = 'W';

  //search the board for possible moves for current player from top left to bottom right 
  for(int i =0; i < 8; i++)
    {
      for(int j=0; j < 8; j++)
        {
	  //is the space isnt blank then check if its the other player
	  if (othello_field[i][j] == s_player)
	    {

	      isValidSpot(i,j,player);   
	    }       
        }
    }
  drawBoard();
}




void board::clearVector()
{
  totalMoves.clear();
}

//checks if valid spot
void board::isValidSpot(int row, int column, char current_player)
{
  int flip, temp_row, temp_col;
  move my_move;
  int size = 0;
  
  //check up
  //check to make sure row isn't 0 so it doesn't cause a segfault when we try to look up
  if(row != 0)
    {//make sure the spot above is a blank spot before we continue. 
      // if(othello_field[temp_row - 1][temp_col] == ' ')
      //{
	  flip = 0;
	  temp_row = row;
	  temp_col = column;
	  //make sure it's not the last row
	  if(temp_row != 7)
	    {//check if current spot isn't player before continuing
	      while(othello_field[temp_row][temp_col] != player)
		{//check against anything that can be in the board. 
		  if(othello_field[temp_row][temp_col] == ' ')
		    {//set flip to 0 so the next loop will never go through
		      flip = 0;
		      break;
		    }
		  //increment temp so we keep looking down.
		  flip++;
		  temp_row++;
		}
	    }
	  if(flip > 0)
	    {
	      if(othello_field[row - 1][column] != 'B' & othello_field[row - 1][column] != 'W')
		{
		  othello_field[row - 1][column] = 'X';
		}
	      
	      my_move.dir = UP;
	      my_move.flip_count = flip;
	      my_move.row = row - 1;
	      my_move.column = column;
	      possible_moves[row - 1][column] = my_move;
	      totalMoves.push_back(possible_moves[row - 1][column]);
	    }
	  // }
    }
  //upRight
  if(row != 0 || column != 7)
    {
      // if(othello_field[temp_row - 1][temp_col + 1] == ' ')
      //{
	  flip =0;
	  temp_row = row;
	  temp_col= column;
        
	  if(temp_row != 7 || temp_col != 0)
	    {
	      while( othello_field[temp_row][temp_col] != player)
		{
		  if(  othello_field[temp_row][temp_col] == ' ')
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
	      if(othello_field[row - 1][column + 1] != 'B' && othello_field[row - 1][column + 1] != 'W')
		{
		  othello_field[row - 1][column + 1] = 'X';
		}
	      my_move.dir = upRight;
	      my_move.flip_count = flip;
	      my_move.row = row -1;
	      my_move.column = column + 1;
	      
	      possible_moves[row - 1][column + 1] = my_move;
	      totalMoves.push_back(possible_moves[row - 1][column + 1]);
	    }
	  //}
    }
  //check right
  if(column != 7)
    {
      flip = 0;
      temp_row =row;
      temp_col= column;
      //if(othello_field[temp_row][temp_col + 1] == ' ')
      //{
	  if(temp_col != 0)
	    {
	      while(othello_field[temp_row][temp_col] != player)
		{
		  if(othello_field[temp_row][temp_col] == ' ')
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
	      if(othello_field[row][column + 1] != 'B' && othello_field[row][column + 1] != 'W')
		{
		  othello_field[row][column + 1] = 'X';
		}	      
	      my_move.dir = RIGHT;
	      my_move.flip_count = flip;
	      my_move.row = row;
	      my_move.column = column+1;
	      
	      possible_moves[row][column + 1] = my_move;
	      totalMoves.push_back(possible_moves[row][column + 1]);
	    }
	  //}
    }
  //downRight
  if(row != 7 || column != 7)
    {     
      //if(othello_field[temp_row + 1][temp_col + 1] == ' ')
      //{
	  flip =0;
	  temp_row = row;
	  temp_col= column;
	  if(temp_row != 0 || temp_col != 0)
	    {
	      while( othello_field[temp_row][temp_col] != player)
		{
		  if(othello_field[temp_row][temp_col] == ' ')
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
	      if(othello_field[row + 1][column + 1] != 'B' && othello_field[row + 1][column + 1] != 'W')
		{
		  othello_field[row + 1][column + 1] = 'X';
		}
	      my_move.dir = downRight;
	      my_move.flip_count = flip;
	      my_move.row = row + 1;
	      my_move.column = column + 1;
	      
	      possible_moves[row + 1][column + 1] = my_move;
	      totalMoves.push_back(possible_moves[row + 1][column + 1]);
	    }
	  //}
    }
  //check down
  if(row !=7)
    {
 
      //if(othello_field[temp_row + 1][temp_col] == ' ')
      //{
	  flip =0;
	  temp_row =row;
	  temp_col= column;
	  if(temp_row != 0)
	    {
	      while(othello_field[temp_row][temp_col] != player)
		{
		  if(othello_field[temp_row][temp_col] == ' ')
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
	      if(othello_field[row + 1][column] != 'B' && othello_field[row + 1][column] != 'W')
		{
		  othello_field[row + 1][column] = 'X';
		}
	      char test = othello_field[row + 1][column];
	      cout << "this is test: " << endl;
	      my_move.dir = DOWN;
	      my_move.flip_count = flip;
	      my_move.row = row +1;
	      my_move.column = column;
	      
	      possible_moves[row + 1][column] = my_move;
	      totalMoves.push_back(possible_moves[row + 1][column]);
	    }
	  //}
    }
  //downLeft
  if(row != 7 || column != 0)
    {
      //if(othello_field[temp_row + 1][temp_col - 1] == ' ')
      //{
	  flip =0;
	  temp_row = row;
	  temp_col= column;    
	  if(temp_row != 0 || temp_col != 7)
	    {
	      while(othello_field[temp_row][temp_col] != player)
		{
		  if(othello_field[temp_row][temp_col] == ' ')
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
	      if(othello_field[row + 1][column - 1] != 'B' && othello_field[row + 1][column - 1] != 'W')
		{
		  othello_field[row + 1][column - 1] = 'X';
		}	      
	      my_move.dir = downLeft;
	      my_move.flip_count = flip;
	      my_move.row = row + 1;
	      my_move.column = column - 1;

	      possible_moves[row + 1][column - 1] = my_move;
	      totalMoves.push_back(possible_moves[row + 1][column - 1]);
	    }
	  //}
    }
  //check left
  if(column !=0)
    { 
      //if(othello_field[temp_row][temp_col - 1] == ' ')
      //{
	  flip =0;
	  temp_row =row;
	  temp_col= column;       
	  if(temp_col != 7)
	    {
	      while(othello_field[temp_row][temp_col] != player)
		{
		  if(othello_field[temp_row][temp_col] == ' ')
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
	      if(othello_field[row][column - 1] != 'B' && othello_field[row][column - 1] != 'W')
		{
		  othello_field[row][column - 1] = 'X';
		}
	      my_move.dir = LEFT;
	      my_move.flip_count = flip;
	      my_move.row = row;
	      my_move.column = column-1;  
	      
	      possible_moves[row][column - 1] = my_move;
	      totalMoves.push_back(possible_moves[row][column - 1]);
	    }
	  //}
    }
  //upLeft
  if(row != 0 || column != 0)
    {
      //if(othello_field[temp_row - 1][temp_col - 1] == ' ')
      //{
      flip =0;
      temp_row = row;
      temp_col= column;
      if(temp_row != 7 || temp_col != 7)
	{
	  while( othello_field[temp_row][temp_col] != player)
	    {
	      if(  othello_field[temp_row][temp_col] == ' ')
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
	  if(othello_field[row - 1][column - 1] != 'B' && othello_field[row - 1][column - 1] != 'W')
	    {
	      othello_field[row - 1][column - 1] = 'X';
	    }
	  my_move.dir = upLeft;
	  my_move.flip_count = flip;
	  my_move.row = row -1;
	  my_move.column = column - 1;
	  
	  possible_moves[row - 1][column - 1] = my_move;
	  totalMoves.push_back(possible_moves[row - 1][column - 1]);
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

void board::confirmMove(int r, int c)
{
  for(int i = 0; i < totalMoves.size(); i ++)
    {
      move temp_move = totalMoves[i];
      direction dir = temp_move.dir;
      int flip = temp_move.flip_count;
      int row = temp_move.row;
      int column = temp_move.column;
      if(row == r && column == c)
	{
	  cout << "traversing through confirm moves" << endl;
	  cout << "dir: " << dir << " flip: " << flip << " row: " << row << " column: " << column << endl;
	  sendMove(dir, flip, row, column);
	}
    }
  
  //leave all but B and W spaces
  for(int i =0; i <8; i++)
    {
      for(int j=0; j<8; j++)
	{
	  //change all the number spaces to ' ' spaces again
	  if(othello_field[i][j] == 'W')
	    {}
	  else if(othello_field[i][j] == 'B')
	    {}    
	  else
	    othello_field[i][j] = ' ';
	}
      
    }
  turnNumber++;
  clearVector();
}

//finializes the move to the board clears all the numbers on the board
//updates black and white pieces
//update move count
void board::sendMove(direction dir, int flip, int row, int column)
{
  char current_player = whosTurn();
  
  switch(dir)
    {
    case 0:
      othello_field[row][column] = current_player;
      for(int i = 0; i < flip; i++)
	{
	  row++;
	  othello_field[row][column] = current_player;
	  updatePieces();
	}
      break;

    case 1:
      othello_field[row][column] = current_player;

      for(int i = 0; i < flip; i++)
	{
	  row--;
	  othello_field[row][column] = current_player;
	  updatePieces();
	}
      break;

    case 2:
      othello_field[row][column] = current_player;

      for(int i = 0; i < flip; i++)
	{
	  column++;
	  othello_field[row][column] = current_player;
	  updatePieces();
	}
      break;

    case 3:
      othello_field[row][column] = current_player;

      for(int i = 0; i < flip; i++)
	{
	  column--;
	  othello_field[row][column] = current_player;
	  updatePieces();
	}
      break;

    case 4:
      othello_field[row][column] = current_player;

      for(int i = 0; i < flip; i++)
	{
	  column++;
	  row++;
	  othello_field[row][column] = current_player;
	  updatePieces();
	}
      break;

    case 5:
      othello_field[row][column] = current_player;

      for(int i = 0; i < flip; i++)
	{
	  column--;
	  row++;
	  othello_field[row][column] = current_player;
	  updatePieces();
	}
      break;

    case 6:
      othello_field[row][column] = current_player;

      for(int i = 0; i < flip; i++)
	{
	  column++;
	  row--;
	  othello_field[row][column] = current_player;
	  updatePieces();
	}
      break;

    case 7:
      othello_field[row][column] = current_player;

      for(int i = 0; i < flip; i++)
	{
	  column--;
	  row--;
	  othello_field[row][column] = current_player;
	  updatePieces();
	}
      break;

    default:

      cout << "No MOVES chosen" << endl;
      break;

    }
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
	  if(othello_field[i][j] == 'B' || othello_field[i][j] == 'W')
	    {
	      cout << othello_field[i][j] << "|";
	    }
	  else
	    {
	      //to adjust the color of the text choices
	      cout << "\033[1;32m" << othello_field[i][j] << "\033[0m" << "|";
	    }   
	} 
      cout <<endl;
    }

  cout << "White Pieces: " << white_pieces << endl;
  cout << "Black Pieces: " << black_pieces << endl;
}

//finds the winner of the game
void board::findWinner()
{

  if(white_pieces > black_pieces)
    cout << "\n\n********White is the winner********\n\n" <<endl;
  if(white_pieces < black_pieces)
    cout << "\n\n********Black is the winner********\n\n" <<endl;

  if(white_pieces == black_pieces)
    cout << "\n\n********Black is the winner********\n\n" <<endl;

}

//checks if the game is over
bool board::checkIfEnd()
{

  // one player cant move anymore
  if(white_pieces ==0 ||  black_pieces == 0)
    return true;


  return false;

}

/*
//public AI CALL
void board::aiTurn(int depth)
{

  // find the best move possible via Alpha beta pruning
  char Ai_move = AI(othello_field, 3, black_pieces, white_pieces,0,0);

  sendMove(Ai_move);


}

//AI with hursitic function call and alpha beta pruning
char board::AI(char othello[][8], int depth, int black_best, int white_best, int alpha, int beta)
{
  char selection;
  int score = evaluate(othello, selection);

  //if blacks
   
  
  //

  /*
   int score = findSolution(othello);
      
   if(score ==3)
     current char;
   if(score ==-3)
     return score;
  

}

//finds the best move 

int board::evaluate(char othello[][8], char& selection)
{

       int weights[8][8] = 
	 { {4, -3, 2, 2, 2, 2, -3, 4},
	   {-3, -4, -1, -1, -1, -1, -4, -3},
	   {2, -1, 1, 0, 0, 1, -1, 2},
	   {2, -1, 0, 1, 1, 0, -1, 2},
	   {2, -1, 0, 1, 1, 0, -1, 2},
	   {2, -1, 1, 0, 0, 1, -1, 2},
	   {-3, -4, -1, -1, -1, -1, -4, -3},
	   {4, -3, 2, 2, 2, 2, -3, 4} };
          
       //generate moves
       //get all moves flip count + weight valuve
       // return best value

}
*/
