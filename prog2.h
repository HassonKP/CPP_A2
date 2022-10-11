#include <iostream>
#include <cctype>
#include <cstring>
#include <time.h>
using namespace std;

/*Name: Killian Hasson		Date:05/02/2021		Class: CS202
 *
   This file is the .h file for the program we will have a game class which will be used to keep track of the players stats as well as the building of the
 board. Instead of a node class a tile class was used in the same way, this will assist in building an array of DLLs, the board is a pointer to a tile. 
 I used some simple inheirtance in this file with a game class having a relation ship with tiles, a tile has a relationship with tile features, and 
 tile features have a parent relationship to other types of tiles. Only used 1 .h file this time and I regret not splitting up this program more.
 * */

class tile;

//The following class will help manage a game which is an array of DLLs
class game
{
        public:
                game();//base Constructor for a game
                ~game();//Base destructor for a game
		int board_width();//Gets the width of the game board
		int board_height();//Gets the height of the game board
                int change_location(int X, int Y);//A function that will take in new coordinates on the board
                int change_status(int new_status);//A function to change the players status
                void display_location();//Display the players location on the board
                void display_board();//Displays the entirety of the board
		int change_hp(int Dmg);//Change the hp of the player
		void display_hp();//Display the hp of the player
		int change_pts(int Score);//Chaange the players points
		void display_pts();//Display the points
		int check_pts();//Check to see if we got all the points for a win
		int check_hp();//Check to see if the player is dead
		tile * get_tile_location();//Returns the tile the player is on
		tile * get_tile_location(int X, int Y);//Next call for the tile
		tile * get_tile_location(tile * head, int x);//Traversing in the correct index for correct tile
        private:
                int location_x;//Location will need two variables
                int location_y;//Second location variable
        	int board_size_x;//Size of board will be random
	  	int board_size_y;//Second variable for random size
		int status;//The players status will be 0, unless stuck
                int hp;//Player will have 20 hit points
		int points;//Player needs a way to win
		tile * board;//Board is a pointer to tile class will be an array
};

//Class tile feature will be the parent class for the various kinds of tiles
class tile_feature
{
        public:
                tile_feature();//Constructor for each tile on the board
                tile_feature(char Legend);//Constructor for the tile that will take in a legend character
                virtual ~tile_feature();//Destructor for a tile feature
                char get_legend();//Returns a tile features legend character
                virtual void process(game * thegame);//The process function to decide which specific tile traps process will need to be used

        protected:
                char legend;//Legend for telling the type of tile 
};




//The teleport trap should change the coordinates for the games player, is a derived class of a tile feature
class teleport: public tile_feature
{
	public:
		teleport();//Base constructor for a teleporter
		teleport(int X,int Y);//Coinstructor that will take in the location to change
		~teleport();//Destructor
		//void teleport_noop();//Testing
		void process(game * thegame);//The process of the teleporter tile
		void generate_target(int xmax, int ymax);//This function will generate the location the player is sent to
	protected:
		int y;//Location coordinate 1
		int x;//Location coordinate 2
};



//The sand trap should restrict a players movement for a set number of turns and subtract 1 from that number until they are freed at 0 to move again, derived class from a tile_feature
class sand_trap: public tile_feature
{
        public:
                sand_trap();//Base constructor
                sand_trap(int Length);//Constructor with a specific time trapped
                ~sand_trap();//Destructor for the trap
                void process(game * thegame);//This function causes the actual process of landing on a sand trap function, changes the status of the player
        protected:
                int length;//Needed an int to hold the number of turns youre stuck
};

//Spike trap will cause damage to the player anywhere from 0 damage to 10, if 0 should change read out message
class spike: public tile_feature
{
        public:
                spike();//Constructor
                ~spike();//Destructor
                void process(game * thegame);//Process of the spike trap should call the change HP function in game 
        protected:
                int dmg;//Hold the number of damage done to the player
};

//Goal will be the class for the player to have a way to win, make their way to 3 goal tiles to collect the points
class goal: public tile_feature
{
	public:
		goal();//Cosntructtor
		~goal();//Destructor
		void process(game * thegame);//Process of the goal tile, should just change the points of the game
	protected:
		int score;//Number of points you get per goal tile
};

//Tile is a node for the array of DLLs
class tile
{
        public:
                tile();//Constructor for the tiles
		tile(game * thegame);//Constructor for tiles taking in the game for use
                ~tile();//Destructor
                tile * get_next();//Navigating to the next tile
                tile * set_next(tile * new_tile);//Setting the next tile
                tile * get_prev();//Gets the previous tile
                tile * set_prev(tile * new_tile);//sets the previous tile 
                tile * add(tile * new_tile);//Will be needed to properly add tiles in the array of DLLs
		void make_feature(game * thegame);//This fucntion will properly assign tile features to each tile randomly
		void display_type();//Displays the types of tiles
		void player_enters(game * thegame);//A player needs to physically enter a tile and find out what happens upon entering
        protected:
                tile_feature * feature;//A feature points to a tile feature
                tile * next;//Next pointer
                tile * prev;//previous pointer
};







