//Testing commit and push -- Chaz Lambert
#include <iostream>

using namespace std;

typedef enum {UP,DOWN,LEFT,RIGHT,upLeft,upRight, downLeft, downRight} direction;


struct move
{
    direction dir;
    int flip_count; 
    int row;
    int column;
    
};





struct Node
{
    move aMove;
    Node *Next;
};





class board
{

    private:
    //needed for the start state of the program
    move possible_moves[70];


    //this is the new PM array 
    Node* possibleMoves[20];


    char othello_field[8][8];
    int move_count;
    int black_pieces;
    int white_pieces;
    int turnNumber;
    int black_array[31];
    int white_array[31];
    char player;
    char agent;


    //functions the user doesnt need to use

     bool checkPlacement(int,int);
     bool isFull();
     void updatePieces();
     void isValidSpot(int,int,char);
     char whosTurn();
     void addMove();

     //functions the user and agent will use
     public:
     void drawBoard();
     void place(int,int, char);
     bool checkSpace(int,int);
     void generateMoves();
     void sendMove(int);

     board();
    ~board();
};
