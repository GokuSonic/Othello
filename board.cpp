//* implementation file*/

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




void board::clearLinkedList()
{

  Node  *n1 = new Node;
  Node  *n2 = new Node;


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
    for(int i =0; i<index;i++)
    {         
        n2 = possibleMoves[i];

        //make sure the poisition isnt null first
        if(n2 != NULL)
	{  

	    //if first node in linked list
	    if(n2->Next == NULL)
	    { 

	        move temp_move = n2->aMove;

	        if(temp_move.row == newMove.row && temp_move.column == newMove.column)
	        {
		    samePositionFound = true;
		    n2->Next = n1;
	        }
	    }
            else
	    {

	      /*	        cout<< "there are multiple moves in this tern " << endl;
                while(n2->Next !=NULL)
		{  
		  cout << "loop " << endl;
		     n2 = n2->Next;
     		}
		n2->Next = n1;*/
	    } 

	    /*
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
		}*/
	 }

    //Add the new loaction if cant find a match
    }
  if(!samePositionFound)
    {   
      if(possibleMoves[index] ==NULL)
	{     
	  possibleMoves[index] =n1;
	}
    }   
  
  
  //see whats in the linked list debugging only
  /*  for(int i =0; i<index;i++)
    {
      cout << "index= " <<  i  <<endl;
      n2 = possibleMoves[i];
      cout << "move details: " <<"\n\t";
      move temp = n2->aMove;
      cout << "row= " << temp.row << " col= " << temp.column;
      cout << "\n\t dir = " << temp.dir << endl;
 
    }
  */

  //cout<< "--------------------leaving function" << endl;

}




//checks if valid spot
void board::isValidSpot(int row,int column, char current_player)
{
  int flip, temp_row,temp_col;   

  char tempChar = ' ';
  move my_move;
  
  //check up
  if(row != 0)
    {
      flip =0;     
      temp_row = row;
      temp_col= column;

      if(temp_row != 7)
	{
	  while( othello_field[temp_row][temp_col] != player)
	    {
	      if(  othello_field[temp_row][temp_col] == ' ' || (othello_field[temp_row][temp_col] >= (char)48 && othello_field[temp_row][temp_col] <= (char)57) 
                   || (othello_field[temp_row][temp_col] >= (char)97 && othello_field[temp_row][temp_col] <= (char)122))
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
            
            decToChar( move_count,tempChar);
            
            othello_field[row-1][column] = tempChar;

	  }
	  my_move.dir = UP;
	  my_move.flip_count = flip;
	  my_move.row = row -1;
	  my_move.column = column;
	        
	  addMove(move_count,my_move);
	      
	  move_count ++;
	  // drawBoard();
	  //cin >> flip; 	  
	}
     
    }

  
  //check left
  if(column !=0)
    { 
 
        
      flip =0;
      temp_row =row;
      temp_col= column;
        
      if(temp_col != 7)
	{
	  while( othello_field[temp_row][temp_col] != player)
	    {
	      if(  othello_field[temp_row][temp_col] == ' ' || (othello_field[temp_row][temp_col] >= (char)48 && othello_field[temp_row][temp_col] <= (char)57)
		   || (othello_field[temp_row][temp_col] >= (char)97 && othello_field[temp_row][temp_col] <= (char)122))

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

            decToChar( move_count,tempChar);
	    othello_field[row][column-1] =  tempChar;


	  }   
	  my_move.dir = LEFT;
	  my_move.flip_count = flip;
	  my_move.row = row;
	  my_move.column = column-1;
	        
	  addMove(move_count,my_move);

          move_count ++;
	  
	  //	  drawBoard();
	  //cin >> flip; 	  
	}
 
    }
  
  
  //check down
  if(row !=7)
    {
 
        
      flip =0;
      temp_row =row;
      temp_col= column;
      if(temp_row != 0)
	{
	  while( othello_field[temp_row][temp_col] != player)
	    {
	      if(  othello_field[temp_row][temp_col] == ' ' || (othello_field[temp_row][temp_col] >= (char)48 && othello_field[temp_row][temp_col] <= (char)57)
		   || (othello_field[temp_row][temp_col] >= (char)97 && othello_field[temp_row][temp_col] <= (char)122))

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
            
                       decToChar( move_count,tempChar);
		       othello_field[row+1][column] =  tempChar;

	  }
	  my_move.dir = DOWN;
	  my_move.flip_count = flip;
	  my_move.row = row +1;
	  my_move.column = column;
	        
	  addMove(move_count,my_move);

          move_count ++;
	  

	}

    }
  


  //check right
  if(column !=7)
    {
        
      flip =0;
      temp_row =row;
      temp_col= column;
        
      if(temp_col != 0)
	{
	  while( othello_field[temp_row][temp_col] != player)
	    {
	      if(  othello_field[temp_row][temp_col] == ' '  || (othello_field[temp_row][temp_col] >= (char)48 && othello_field[temp_row][temp_col] <= (char)57)
		|| (othello_field[temp_row][temp_col] >= (char)97 && othello_field[temp_row][temp_col] <= (char)122))
	
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
           
            decToChar( move_count,tempChar);
	    othello_field[row][column+1] = tempChar;


	  }
	  my_move.dir = RIGHT;
	  my_move.flip_count = flip;
	  my_move.row = row;
	  my_move.column = column+1;

	  addMove(move_count,my_move);
              
          move_count ++;
	
      

	}

    }
  



  //upLeft
  if(row != 0 || column != 0)
    {
        
      flip =0;
      temp_row = row;
      temp_col= column;
      if(temp_row != 7 || temp_col != 7)
	{
	  while( othello_field[temp_row][temp_col] != player)
	    {
	      if(  othello_field[temp_row][temp_col] == ' ' || (othello_field[temp_row][temp_col] >= (char)48 && othello_field[temp_row][temp_col] <= (char)57)
		|| (othello_field[temp_row][temp_col] >= (char)97 && othello_field[temp_row][temp_col] <= (char)122))

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
                     decToChar( move_count,tempChar);
		     othello_field[row-1][column - 1] =  tempChar;

	    }
	  my_move.dir = upLeft;
	  my_move.flip_count = flip;
	  my_move.row = row -1;
	  my_move.column = column - 1;
	        
	  addMove(move_count,my_move);

          move_count ++;
        

	}

    }




  //upRight
  if(row != 0 || column != 7)
    {
        
      flip =0;
      temp_row = row;
      temp_col= column;
        
      if(temp_row != 7 || temp_col != 0)
	{
	  while( othello_field[temp_row][temp_col] != player)
	    {
	        if(  othello_field[temp_row][temp_col] == ' ' || (othello_field[temp_row][temp_col] >= (char)48 && othello_field[temp_row][temp_col] <= (char)57)
		   || (othello_field[temp_row][temp_col] >= (char)97 && othello_field[temp_row][temp_col] <= (char)122))

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

            decToChar( move_count,tempChar);
	    othello_field[row-1][column + 1] = tempChar;
	   }  
	  my_move.dir = upRight;
	  my_move.flip_count = flip;
	  my_move.row = row -1;
	  my_move.column = column + 1;


	  addMove(move_count,my_move);

          move_count++;
        

	        
      	}

    }



  //downLeft
  if(row != 7 || column != 0)
    {
     
      flip =0;
      temp_row = row;
      temp_col= column;
        
      if(temp_row != 0 || temp_col != 7)
	{
	  while( othello_field[temp_row][temp_col] != player)
	    {
	      if(  othello_field[temp_row][temp_col] == ' '|| (othello_field[temp_row][temp_col] >= (char)48 && othello_field[temp_row][temp_col] <= (char)57)
		   || (othello_field[temp_row][temp_col] >= (char)97 && othello_field[temp_row][temp_col] <= (char)122))

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
	  if(othello_field[row+1][column-1] == ' ')
	  {
	   
            decToChar( move_count,tempChar);
	    othello_field[row+1][column - 1] =  tempChar;

	  }


	  my_move.dir = downLeft;
	  my_move.flip_count = flip;
	  my_move.row = row + 1;
	  my_move.column = column - 1;


	  addMove(move_count,my_move);
          move_count ++;	  
	

	  // drawBoard();
	  //cin >> flip; 	      
	}
     
    }



  //downRight
  if(row != 7 || column != 7)
    {     
        
      flip =0;
      temp_row = row;
      temp_col= column;
      if(temp_row != 0 || temp_col != 0)
	{
	  while( othello_field[temp_row][temp_col] != player)
	    {
	      if(  othello_field[temp_row][temp_col] == ' '|| (othello_field[temp_row][temp_col] >= (char)48 && othello_field[temp_row][temp_col] <= (char)57)
		   || (othello_field[temp_row][temp_col] >= (char)97 && othello_field[temp_row][temp_col] <= (char)122))

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

                         decToChar( move_count,tempChar);
			 othello_field[row+1][column + 1] =  tempChar;

	   }

	  my_move.dir = downRight;
	  my_move.flip_count = flip;
	  my_move.row = row + 1;
	  my_move.column = column + 1;

	  addMove(move_count,my_move);
	        
          move_count ++;
	

	}
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



//takes the move count and converts it to its ascii value 
void board::decToChar(int position, char& tempChar)
{


  //if the position is from 0-9 then add 48
  if(position <=9 && position >= 0)
  {
     tempChar = ((char) (position+48));
     
  }
  //now use lowercase numbers
  else  if(position >=10)
  {
    tempChar = ((char) (position+87));
  }


}



//this converts the char to a proper decimal poisition in the array
int board::charConvert(char choice)
{
     int typeCasted = (int)choice;
    
     //if from 0-9 return 48-their ascii value
     if(typeCasted >= 48 && typeCasted <=57)
          return  typeCasted-48; 
  
     //if from a-z then return typecast -87 which gives 10+
     if(typeCasted >= 97 && typeCasted <=122)
       return typeCasted - 87;
   
    
     //user messed up seg faults 
     return -1;

}



//finializes the move to the board clears all the numbers on the board
//updates black and white pieces
//update move count

void board::sendMove(char user_choice)
{

  int choice =charConvert(user_choice);
 
  if(choice == -1)
  {
      cout << "no move was selected" <<endl; 
  }
  else
  {

  Node  *n1 = new Node;
 
  cout << " choice : " << choice << endl;
  n1 =  possibleMoves[choice];

  do
  {


       //gets the move from the linked list
       
       move temp_move = n1->aMove;
 
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

       n1 = n1->Next;
  }while(n1 !=NULL);

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
    cout << "\n\n********Tie!********\n\n" <<endl;

}


//checks if the game is over
bool board::checkIfEnd()
{

    // one player cant move anymore
    if(white_pieces ==0 ||  black_pieces == 0)
      return true;


    return false;

}




//public AI CALL
void board::aiTurn(int depth)
{


    //copy board
    char othello[8][8];

    for(int i=0; i<8;i++)
    {
        for(int j=0; j<8; j++)
	{
           othello[i][j] =  othello_field[i][j];
	}
    }

    // find the best move possible via Alpha beta pruning
    char Ai_move = AI(othello, 4, black_pieces, white_pieces,0,0);

    //cout<< "Ai move selected: " << Ai_move << endl;

    sendMove(Ai_move);


}


//AI with hursitic function call and alpha beta pruning
char board::AI(char othello[][8], int depth, int black_best, int white_best, int alpha, int beta)
{

  
     int move_number;

     // min then max
    if (whosTurn() == 'B') 
       move_number = evaluate('0');
    else
       move_number = evaluate('M');


    //only goes down 3 levels
    if(depth == 0)
    {
       //if from 0-9 put it in format for send move
       if(move_number>=0 && move_number <= 9)
          return (char)(move_number +48);
  
       if(move_number >=10 && move_count <= 35)
          return (char)(move_number + 87);
    }

    cout << "max" << depth << endl; 
    if( black_best > white_best)
    {
      Node *n1 = new Node;
      n1 = possibleMoves[move_number];
      move temp_move = n1->aMove;
      int row = temp_move.row;
      int column = temp_move.column;
      if(whosTurn() == 'B')
	{
	  othello[row][column] = 'B';
	}
      else
	{
	  othello[row][column]= 'W';
	}
      
      return AI(othello,depth - 1,black_best,white_best,alpha,beta);
     
    }


    /*
    if(depth !=0)
    {

      if( 

         if(score > black_best)
	    break; 
         else
            white_best = *


	 /*

      if(alphabeta)then
         if(to_mov(white) and (the score> whites best)
             if(the score > blacks_ best)
                    break; /alpha beat cutoff

             else
                 white's best = the score

         end 
      end

        if (to move(black) and (the score < blacks best))
            if(the score < blacks best) 
                break //alpha beta cutt off
            else
                 blacks_best = the score
          end
      end
   end   
    */

}


//finds the best move 
int board::evaluate(char minORmax)
{

        //board weights created by team
        int weights[8][8] = 
       { {4, -3, 2, 2, 2, 2, -3, 4},
	{-3, -4, -1, -1, -1, -1, -4, -3},
	{2, -1, 1, 0, 0, 1, -1, 2},
        {2, -1, 0, 1, 1, 0, -1, 2},
        {2, -1, 0, 1, 1, 0, -1, 2},
	{2, -1, 1, 0, 0, 1, -1, 2},
        {-3, -4, -1, -1, -1, -1, -4, -3},
	{4, -3, 2, 2, 2, 2, -3, 4} };
     
	int best_score =0;
        int best_move_index =0;
        //generate moves to populate the move linked list
        generateMoves();

        Node  *n1 = new Node;       
       
        if(minORmax == 'M')
	{

            if(move_count >0)
            {
           
               //finds the move with the best move
	       int j =0;
	       while( j< move_count)
               {
	          //makes sure the move isnt null
	          if(possibleMoves[j] != NULL)
	          {
                     n1 =  possibleMoves[j];

                     //gets the move from the linked list
                     move temp_move = n1->aMove;
                     int flip = temp_move.flip_count;
		     int row = temp_move.row;
		     int column = temp_move.column;
		     int score=0;
               
		     //calculate the huristic
		     score = flip + weights[row][column];                  
		     // cout << "score: " << score << "  best_score" << best_score << "    for row = " << row << "  col= "<< column <<endl;
		     //if current move is better than best move
		     if(score > best_score)
		     {
		       best_score =score;
		       //cout <<" found at " << j<<endl;
   	   	       best_move_index = j;
		     }                                       
                   
		  }
		  j++;
	       }
	    }
	}
        else
	{
	  if(move_count >0)
            {

	      //finds the move with the best move
	      int j =0;
	      while( j< move_count)
		{
                  //makes sure the move isnt null
                  if(possibleMoves[j] != NULL)
		    {
		      n1 =  possibleMoves[j];

		      //gets the move from the linked list
		      move temp_move = n1->aMove;
		      int flip = temp_move.flip_count;
		      int row = temp_move.row;
		      int column = temp_move.column;
		      int score=0;

		      //calculate the huristic
		      score = flip + weights[row][column];
		      //cout << "score: " << score << "  best_score" << best_score << "    for row = " << row << "  col	\
		      //= "<< column <<endl;
		      //if current move is better than best move
		      if(score < best_score)
			{
			  best_score =score;
			  // cout <<" found at " << j<<endl;
			  best_move_index = j;
			}

		    }
                  j++;
		}
            }
      }

      
       //return best move index
       return best_move_index;
}

