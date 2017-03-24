# SnakeGame
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

VARIABLE DEFINED FOR THE GAME (provided by instructors)

#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <ctype.h>
using namespace std;
#include "termfuncs.h"

//
// TERMFUNCS.CPP Version: 2015-07-09
//
static const string CSI = "\033[";

// -- NOTE TO COMP11 STUDENTS ----------------
//
//  DO NOT EDIT OR COPY CODE FROM THIS FILE
//  TO USE THESE FUNCTIONS:
//     at the top of your code put: #include "termfuncs.h"
//     when you compile:  g++ -Wall myprog.cpp termfuncs.cpp
//
//  DO NOT DO THIS:
//	#include "termfuncs.cpp"
//
//
// termfuncs.cpp -- some simple functions for using the terminal nicely
//
//   char getachar()     -- returns next char with no echo and no Enter needed
//   char getacharnow(ds)     -- only waits ds/10th seconds
//				 returns '\0' if no input by that time
//   NOTE: getachar and getacharnow handle arrow keys by returning
//	   KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
//
//   KLUDGE: if $TF_QUIT is defined then getachar will exit if that 
//	     key is entered (total hack, I know)
//
//   void screen_clear() -- clears the screen
//   void screen_home()  -- moves cursor to top of screen
//   void screen_fg(string color)
//   void screen_bg(string color)
//   void screen_attr(string attr)
//   void screen_bright()
//   void screen_reset()
//   void place_cursor(int, int);   -- move the cursor to row col
//   void place_char(char, int, int)  -- move and place
//   void hide_cursor()
//   void show_cursor()
//
//   int  random_int(int low, int high)
//		returns random int in [low, high]
//		note: if SNAKE_SEED is set then use that for srand
//		      if not, then call srand with time(0) at first call
//   void seed_random(s)
//
// hist: 2015-11-02 spcial TF_QUIT key for exit on a char
// hist: 2015-11-02 handle EOF for getachar
// hist: 2015-07-09 added arrow key handling
// hist: 2014-09-30 added flush to getachar* and also show_cursor sighandler
// hist: 2014-09-30 added hide/show cursor and random_int
// hist: 2014-07-20 getachar now uses read, not cin >> c which skipped blanks
// hist: 2014-07-01 merged screendraw and termfuncs
//
static string color_names[] = { "black", "red", "green", "yellow",
				"blue",  "magenta", "cyan", "white" };
static const int num_colors = 8;

static string attr_names[] = { 	"reset", "bright", "dim", "", 
				"underscore", "blink", "", 
				"reverse", "hidden" };
static const int num_attrs = 9;

static termios prev_tty_state;
static int prev_state_stored = 0;

static char handle_escape_seq();

//
// getachar
//  returns a char using noecho and -icanon unless not a tty
//
char getachar()
{
	char q_key = 0;
	char *qk = NULL;
	char c;
	int  nread;

	if ( ( qk = getenv("TF_QUIT") ) != NULL ){
		q_key = qk[0];
	}
	cout << std::flush;
	if ( isatty(0) ){
		struct termios	info, orig;
		// system("stty -echo -icanon");
		tcgetattr(0, &info);
		orig = info;
		prev_tty_state = orig;
		prev_state_stored = 1;

		info.c_lflag &= ~ECHO;
		info.c_lflag &= ~ICANON;
		tcsetattr(0, TCSANOW, &info);

		nread = read(0, &c, 1);
		if ( nread == 1 && c == ESCAPE )
			c = handle_escape_seq();

		// system("stty echo icanon");
		tcsetattr(0, TCSANOW, &orig);
	}
	else {
		if ( cin.get(c) )
			nread = 1;
		else
			nread = 0;
		// cout << "got " << nread << " chars [" << c << "]\n";
		if ( nread == 0 && qk != NULL )
			exit(0);
	}

	if ( nread == 1 && qk != NULL && c == q_key ){
		exit(0);
	}

	return ( nread > 0 ? c : 0 );
}
//
// getacharnow
//  returns a char using noecho and -icanon unless not a tty
//
char getacharnow(int decisecs)
{
	char c;

	cout << std::flush;
	if ( isatty(0) ) 
	{
		struct termios	info, orig;
		// system("stty -echo -icanon");
		tcgetattr(0, &info);
		orig = info;
		prev_tty_state = orig;
		prev_state_stored = 1;

		info.c_lflag &= ~ECHO;
		info.c_lflag &= ~ICANON;
		info.c_cc[VMIN] = 0;
		info.c_cc[VTIME] = decisecs;
		tcsetattr(0, TCSANOW, &info);

		if ( read(0, &c, 1) == 1 ){
			if ( c == ESCAPE )
				c = handle_escape_seq();
		}
		else
			c = '\0';

		tcsetattr(0, TCSANOW, &orig);
		// system("stty echo icanon");
	}
	else {
		if ( read(0, &c, 1) != 1 )
			c = '\0';
	}

	return (int) c;
}

//
// ignore signals, then set tty to read in up to 100 chars in 1/10 second
// examine sequence and return code
// Note: read until an alpha char or inactivity
//
char handle_escape_seq()
{
	struct termios	info, orig;
	char		buf[100];
	int		pos = 0;
	char		c;
	void		(*oldhand)(int);

	if ( !isatty(0) ) 
		return ESCAPE;

	oldhand = signal(SIGINT, SIG_IGN);

	// system("stty -echo -icanon");
	tcgetattr(0, &info);
	orig = info;

	info.c_lflag &= ~ECHO;
	info.c_lflag &= ~ICANON;
	info.c_cc[VMIN] = 0;
	info.c_cc[VTIME] = 1;			// 1/10 second
	tcsetattr(0, TCSANOW, &info);

	do
	{
		if ( read(0, &c, 1) == 1 )	// if got one
			buf[pos++] = c;		// store it
		else
			break;			// else timeout
	}
	while( !isalpha((int)c) && pos < 99 );	// until alpha or full

	if ( pos == 0 || (buf[0] != '[' && buf[0] != 'O' ) )
		c = ESCAPE;
	else 
		switch(buf[1]){
			case 'A':		c = KEY_UP;	break;
			case 'B':		c = KEY_DOWN;	break;
			case 'C':		c = KEY_RIGHT;	break;
			case 'D':		c = KEY_LEFT;	break;
			default :
						c = ESCAPE;
		}

	tcsetattr(0, TCSANOW, &orig);
	signal(SIGINT, oldhand);
	// system("stty echo icanon");
	return c;
}

static void restore_tty_state()
{
	if ( prev_state_stored )
		tcsetattr(0, TCSANOW, &prev_tty_state);
}
void screen_clear()
{
	cout << (CSI + "H");
	cout << (CSI + "2J");
}

void screen_home()
{
	cout << (CSI + "H");
}

static	void (*prev_handler)(int) = NULL;;

void hide_cursor()
{
	void on_sigint(int);

	prev_handler = signal(SIGINT, on_sigint);
	cout << (CSI + "?25l");
}

void show_cursor()
{
	cout << (CSI + "?25h");
}

void on_sigint(int s)
{
	cout << std::flush;
	show_cursor();
	if ( prev_handler ){
		prev_handler(s);
	}
	restore_tty_state();
	exit(SIGINT);
}
//
// lookup a string in an array
//   args: string to find, list of strings, len of list
//   rets: index of string or -1 for not found
//
static int lookup(string findme, string list[], int num)
{
	int	i;
	for(i=0;i<num;i++)
	{
		if ( list[i] == findme )
			return i;
	}
	return -1;
}
void screen_fg(string color)
{
	int	num = lookup(color, color_names, num_colors);
	if ( num >= 0 ){
		cout << CSI << ( 30 + num ) << "m";
	}
}
void screen_bg(string color)
{
	int	num = lookup(color, color_names, num_colors);
	if ( num >= 0 ){
		cout << CSI << ( 40 + num ) << "m";
	}
}
void screen_attr(string attr)
{
	int	num = lookup(attr, attr_names, num_attrs);

	if ( num >= 0 ) {
		cout << CSI << num  << "m";
	}
}
void screen_bright()
{
	screen_attr("bright");
}
void screen_reset()
{
	screen_attr("reset");
}
void place_cursor(int row, int col)
{
	cout << "\033[" << (row + 1) << ";" << (col + 1) << "H";
	flush(cout);
}
void place_char(char c, int row, int col)
{
	place_cursor(row, col);
	cout << c;
	flush(cout);
}

static int rand_seed = -1;

void seed_random(int s)
{
	if ( s > 0 ) {
		srand(s);
		rand_seed = s;
	}
}

int random_int(int lo, int hi)
{
	int	range = hi - lo + 1;
	char	*seed_str;

	if ( rand_seed == -1 ) {
		seed_str = getenv( "SNAKE_SEED" );
		if ( seed_str != NULL )
			seed_random( (unsigned) atoi(seed_str) );
		else 
			seed_random( (unsigned) time(NULL) );
	}
	if ( range <= 0 )
		return 17;		// add to function specs

	return lo + ( rand() % range );
}
