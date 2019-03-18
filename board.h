
#include <iostream>

using namespace std;


class board
{

    private:
    //needed for the start state of the program
    char othello_field[8][8];
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
    void generateMoves(char);
    void isValidSpot(int,int);
    char whosTurn();
    

     //functions the user and agent will use
     public:
     void drawBoard();
     void place(int,int, char);
     bool checkSpace(int,int);


     board();
    ~board();
};
