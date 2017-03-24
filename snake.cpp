//
// snake.cpp
// Written by: J.A. Glover
//       date: 3/6/2016
//    Purpose: create a snake game that involves 2 snacks for the snake to
//              eat and also the snake continuously grows and uses 
//              energy units as it moves. 
//
#include <iostream>
#include "termfuncs.h"
using namespace std;

//global intergers used in numerous functions in the program
const int ROWS = 23;
const int COLS = 63;
const int start_row = 11;
const int start_col = 31;
int egg_row = 0;
int egg_col = 0;
int bug_row = 0;
int bug_col = 0;
int score = 0;
int energy = 60;

// the struct holds the head character plus the position of the head 
// and whether or not its dead
struct Snake{
        char head;
        int row;
        int col;
        bool dead;        
};

// Declerations of functions that will be used in the program
void intro(); //
void setup_board(char board[][COLS]); //
void egg(char board[][COLS]); //
void bug(char board[][COLS]); //
int play_game(char board[][COLS]); //
void report(int score); //
void print_board(char board[][COLS], int row, int col); //
char turn(Snake snake_pos, char input); //
Snake move(char board[][COLS], Snake snake_pos); //
Snake wrap(Snake snake_pos); //

// the main function will be used to call all the other functions
int main()
{
        string name;
        string answer;
        screen_clear();
        screen_home();

        cout << "Welcome to Snake Game!" << endl;
        cout << "What is your name participant?" << endl;
        cin >> name;
        cout << "Nice to meet you " << name << "!" << endl;
        cout << "Are you ready to play? (Yes/No?)" << endl;
        cin >> answer;

        if (answer == "No" or answer == "no")
        {
                cout << "Maybe next time then." << endl;
                return 1;
        }
        else
        {
                intro();
        }

        char board[ROWS][COLS];  // OR struct
        setup_board(board);
        score = play_game(board);
        report(score);

        return 0;
}

void intro()
{
        screen_clear();
        screen_home();

        string questions;
        char play;

        cout << "In the game hitting the f key moves the snake forward one ";
        cout << "space. With each space it moves you gain 1 point. Hitting the";
        cout << " l key turns the head to the left and the r key to the right.";
        cout << " The snakes tail grows with each movment forward. The board";
        cout << " wraps around so you can go off the edge. You start off with";
        cout << " 60 EU. Moving takes away 1 EU at a time. Eating an egg ,aka";
        cout << " the o, gives you 15 more EU. Eating a bug, aka the X, gives";
        cout << " you 25 more EU. If you run out of EU you die. Also if you";
        cout << " hit your own tail you die. Any questions? (Yes/No?)"
                << endl;
       cin >> questions;

        if (questions == "Yes" or questions == "yes")
        {
                cout << "No time for questions. Lets Play." << endl; 
                cout << "Enter any key to continue." << endl;
                getachar();       
        }
}

// the setup board function will be used to assign the boarer to the arry

void setup_board(char board[][COLS])
{
        int row = 0;
        int col = 0;
        screen_clear();

        do {
                for(row = 0; row < ROWS; row++){
                        if ((col == 0 or col == (COLS - 1))
                                        and (row == 0 or (row == (ROWS - 1)))){
                                board[row][col] = '+';}
                        else if ((col == 0 or col == (COLS - 1))
                                        and (row != 0 or (row != (ROWS - 1)))){
                                board[row][col] = '|';}
                        else {
                                if (row == 0 or row == (ROWS - 1)){
                                        board[row][col] = '-';}
                                else {
                                        board[row][col] = ' ';}
                        }
                }
                col++;
        }while (col < COLS);

        board[start_row][start_col] =  '^';
        egg(board);
        bug(board); 
        print_board(board, row, col); 
}

// the egg funtion is for the randomization and placement of the egg snack
//
void egg(char board[][COLS])
{
        char egg = 'o';
        int counter = 0;

        while (counter == 0){
                egg_col = random_int(1, COLS - 2);
                egg_row = random_int(1, ROWS - 2);
                counter = 1;

                //these two if statements keep things from being placed on top
                //of each other

                if (egg_row == bug_row and egg_col == bug_col)
                { 
                        counter = 0;
                }
                if (board[egg_row][egg_col] == '#')
                {
                        counter = 0;
                }
        }
        board[egg_row][egg_col] = egg;
}

//the bug function is for the randomization and placement of the bug snack
//
void bug(char board[][COLS])
{
        char bug = 'X';
        int counter = 0;

        while (counter == 0){
                bug_col = random_int(1, COLS - 2);
                bug_row = random_int(1, ROWS - 2);
                counter = 1;

                if (bug_row == egg_row and bug_col == egg_col)
                { 
                        counter = 0;
                }
                if (board[bug_row][bug_col] == '#')
                {
                        counter = 0;
                }
        }
        board[bug_row][bug_col] = bug;
}

//play game is the loop the controls the state of the game
int play_game(char board[][COLS])
{
        int row = 0;
        int col = 0;
        char input; 
        Snake snake_pos;
        snake_pos.head = '^';
        snake_pos.dead = false;
        snake_pos.row = start_row;
        snake_pos.col = start_col;

        while (snake_pos.dead == false){
                input = getachar();
                if (input == 'l' or 'r'){
                        snake_pos.head = turn(snake_pos, input);
                        board[snake_pos.row][snake_pos.col] = snake_pos.head;
                        print_board(board, row, col);
                }
                if (input == 'f'){
                        snake_pos = move(board, snake_pos);
                        score += 1;
                        energy--;
                        print_board(board, row, col);
                }
                // terminates the game if energy hits 0
                if (energy == 0){
                        snake_pos.dead = true;
                }
        }
        return score;
}

//controls the head turning of the snake
char turn(Snake snake_pos, char input)
{
        if (snake_pos.head == '^'){ 
                if (input == 'l'){
                        snake_pos.head = '<';}
                else if (input == 'r'){
                        snake_pos.head = '>';}
        }
        else if (snake_pos.head == '<'){
                if (input == 'l'){
                        snake_pos.head = 'v';}
                else if (input == 'r'){
                        snake_pos.head = '^';}
        }
        else if (snake_pos.head == 'v'){
                if (input == 'l'){
                        snake_pos.head = '>';}
                else if (input == 'r'){
                        snake_pos.head = '<';}
        }
        else if (snake_pos.head == '>'){
                if (input == 'l'){
                        snake_pos.head = '^';}
                else if (input == 'r'){
                        snake_pos.head = 'v';}
        }
        return snake_pos.head;
}

//controls the forward movment of the snake
Snake move(char board[][COLS], Snake snake_pos)
{

        board[snake_pos.row][snake_pos.col] = '#';

        if (snake_pos.head == '^'){
                snake_pos.row --;}
        else if (snake_pos.head == '>'){
                snake_pos.col ++;}
        else if (snake_pos.head == 'v'){
                snake_pos.row ++;}
        else if (snake_pos.head == '<'){
                snake_pos.col --;}
        if (board[snake_pos.row][snake_pos.col] == '#'){
                snake_pos.dead = true;
        }

        if (snake_pos.row == bug_row and snake_pos.col == bug_col){
                energy += 25;
                bug(board);
        }
        if (snake_pos.row == egg_row and snake_pos.col == egg_col){
                energy += 15;
                egg(board);
        }
        snake_pos = wrap(snake_pos);

        board[snake_pos.row][snake_pos.col] = snake_pos.head;

        return snake_pos;
}

//this funtion wraps the snake around to the other side when 
//it moves off the board
Snake wrap(Snake snake_pos)
{
        if (snake_pos.col == 0){
                snake_pos.col = COLS - 2;}
        else if (snake_pos.col == COLS - 1){
                snake_pos.col = 1;}
        else if (snake_pos.row == 0){
                snake_pos.row = ROWS - 2;}
        else if (snake_pos.row == ROWS - 1){
                snake_pos.row = 1;}

        return snake_pos;
}

//at the end of the game this reports this final score
void report(int score)
{
        cout << "Game Over. Final Score:  " << score << endl;
}

// actually prints out the board, the score, and the energy
void print_board(char board[][COLS], int row, int col)
{
        screen_clear();

        for (row = 0; row < ROWS; row++)
        {
                for (col = 0; col < COLS; col++)
                {
                        cout << board[row][col];
                }
                cout << endl;
        }

        cout << "EU: " << energy << " " << "Score: " << score << endl;
}
