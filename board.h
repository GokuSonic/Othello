
#include <iostream>

using namespace std;


struct move
{
    enum direction {up,down,left,right, upLeft, upRight, downLeft, downRight};
    int flip_count; 
    int row;
    int column;
    
};

class board
{

    private:
    //needed for the start state of the program
    char othello_field[8][8];
    int possibleMove[2][64];
    int black_pieces;
    int white_pieces;
    int turnNumber;
    int black_array[31];
    int white_array[31];
    char player;
    char agent;


    //functions the user doesnt need to use

    bool checkPlacement(int,int);
    bool checkAcross();;
    bool checkRow();
    bool checkCol();
    bool isFull();

    bool isValidSpot(int,int);
    char whosTurn();
    void checker();    

     //functions the user and agent will use
     public:
     void drawBoard();
     void place(int,int, char);
     bool checkSpace(int,int);
     void generateMoves();

     board();
    ~board();
};
