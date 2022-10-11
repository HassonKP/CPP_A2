#include "prog2.h"
/*Name: Killian Hasson		Date:05/03/21		Class:CS202
 *
 *This file is the class functions and their implementations. These functions build off one another in order to properly build a game aswell as
 *the baord required to play on. There are a total of 4 classes for the types of tiles on the board that arent empty. Much of these functions
 *build off of one another but they were done in a ham fisted way arguably.
 * */
//CLASS FUNCTIONS FOR MANAGING GAME CLASS
//The game constructor should create the board the game is played on
game::game()
{ 
  //Generate a board with random sizes and let the player know the boards size
  srand(time(NULL));
  board_size_x = rand() % 12 + 3; 
  board_size_y = rand() % 12 + 3; 
  cout << "create board size: "<< board_size_x << " x " << board_size_y << endl;
  
  //Construct the board using the Randomly generated ints above
  board = new tile[board_size_y];//Board is a pointer to an array of tiles 'nodes'
  for (int i = 0; i < board_size_y; i++) 
  {
    tile * temp = &board[i];
    if (i > 0) 
    {
      temp->make_feature(this);
    }
    for (int j = 0; j < board_size_x; j++) 
    {
      temp = temp->add(new tile(this));
    }
  }
  
  // initialize player location
  location_x = 0;
  location_y = 0;
  //Intialize the player status 0 means can move
  status = 0;
  //Intialize the players HP
  hp = 20;
  //Intialize the points to 0
  points = 0;
}

//Destructor to delete the board
game::~game()
{
        delete board;
}

//We may need to return the tile we are attempting to access
tile * game::get_tile_location()
{
	return get_tile_location(location_x, location_y);//Pass in the location to get the correct tile
}

//This function was called in the first get_tile_location or can be called if we know the location later
tile * game::get_tile_location(int X, int Y)
{
	//Check to make sure the board index we are checking exists if not return NULL
	if(Y < 0 || Y > board_size_y)
	{
		return NULL;
	}
	return get_tile_location(&board[location_y], location_x);//Call the next function passing in the correct first pointer in the index
}

//We will need to traverse this index that was checked in the previous function
tile * game::get_tile_location(tile * head, int x)
{
	//Conditional to check if we have navigated as far down the DLL as required
	if(x <= 0 || head == NULL)
	{
		return head;//Return that tile
	}
	return get_tile_location(head->get_next(), x - 1);//Recursive call
}

//return the actual board width after it was randomly generated
int game::board_width()
{
	return board_size_x;
}

//Return the actual board height after it was randomly generated
int game::board_height()
{
	return board_size_y;
}

//The change location function will take in the new x and y values for where the player is located on the game
int game::change_location(int X, int Y)
{
	//Check if the player is stuck in a sand trap
	if(status != 0)
	{
		status = status - 1;//Decrement it should take 4 turns to climb out of the sand trap
		cout << "Youre stuck for " << status << " more turns!" << endl;
		return 0;
	}
	//Change players location
	location_x = location_x + X;
	location_y = location_y + Y;
	
	//This doesnt work as intended
	/*
	if(!get_tile_location())
	{
		cout << "\nYou made it out of the Dungeon!";
	}*/
}

//Update the players status
int game::change_status(int new_status)
{
	status = new_status;
}

//Display the players current location as coordinates
void game::display_location()
{

	cout << "You are located at column " << location_y << " and row " << location_x << endl;

}

//Update the players points
int game::change_pts(int Score)
{
	points = points + Score;

}

//Display the players correct points
void game::display_pts()
{
	cout << "You have " << points << " out of 3 points." << endl;
}

//Update the players hit points
int game::change_hp(int Dmg)
{
	hp = hp - Dmg;
}

//Display the players hit points
void game::display_hp()
{
	cout << "You have " << hp << " hit points!" << endl;
}

//We need to check the players hit points to tell if they have died
int game::check_hp()
{
	//If they reach 0 or lower HP they died to a trap
	if(hp == 0 || hp < 0)
	{
		return 0;//Dead
	}
	else
		return 1;//Alive
}

//We need to check the points to see if they have gotten 3 points
int game::check_pts()
{
	//If the player has 3 ppoints they won
	if(points == 3)
	{
		return 0;//Win
	}
	else
		return 1;//Not yet
}

//This function will display the board that was built
void game::display_board()
{ 
  tile * temp = NULL; //temp will assist with traversing the board
  	for (int i = 0; i < board_size_y; i++) 
  	{
    	  temp = &board[i];//Temp gets assigned to the tile at the front of each index 
    	  for (int j = 0; j < board_size_x; j++) 
    	  {
      	    cout << " _ ";//Build the edge of the board
      	    temp = temp->get_next();
    	  }
    	  cout << endl;

    	  temp = &board[i]; //Repeat the same process above but we need to do the walls
    	  for (int j = 0; j < board_size_x; j++) 
    	  {
      	    cout << "|";//wall of tile
	    //For marking the players location on the baord
      	    if (j == location_x && i == location_y) 
      	    {
        	// the player location
        	cout << 'x';
      	    }	 
	    else 
      	    {
        	temp->display_type();//Display the type of the tile
      	    }
      	    cout << "|";//Wall of the tile
      	    temp = temp->get_next();//traverse
    	  }
    
	  cout << endl;
  	}
  
  	temp = &board[0];//Build the edge of the baord
  	for (int j = 0; j < board_size_x; j++) 
  	{
    	  cout << " ¯ ";
    	  temp = temp->get_next();
  	}
  
	cout << "\n";
	display_hp();//Display players hp each time we view the board
	display_pts();//display the pts each time baord is viewed
}

//CLASS FUNCTIONS FOR MANAGING "TILES" THEY SHOULD ACT AS NODES IN THEORY
//base constructor for a tile
tile::tile()
{
	next = NULL;
	prev = NULL;
	feature = NULL;
}

//Tile constructor passing in a game
tile::tile(game * thegame)
{
  feature = NULL;
  next = NULL;
  prev = NULL;
  make_feature(thegame);//Call the make feature function to assign specific tile types to the board
}

//Destructor for the tiles
tile::~tile()
{
        if(next)
                next = NULL;
        if(prev)
                prev = NULL;
}

//Return next tile
tile * tile::get_next()
{
        return next;
}

//Set the next tile
tile * tile::set_next(tile * new_tile)
{
        next = new_tile;
}

//Return the prev tile
tile * tile::get_prev()
{
        return prev;
}

//Set the previous tile
tile * tile::set_prev(tile * new_tile)
{
        prev = new_tile;
}

//Add tiles to the DLL
tile * tile::add(tile * new_tile)
{
        if(next != NULL)
        {
                return next->add(new_tile);
        }
        next = new_tile;
        new_tile->prev = this;
}

//Display the "legend" of the tile for the building of the baord
void tile::display_type()
{
	//Check if the feature exists
	if(feature)
	{
		cout << feature->get_legend();//Call the get legend function
	}
}

//Player eneters a tile and based on the feature of that tile the correct process will be called
void tile::player_enters(game * thegame)
{
	feature->process(thegame);//Based on the feature of the tile the correct process is called
//	teleport * temp = dynamic_cast<teleport*>(feature);
}

//Assigns the features for the tiles randomly
void tile::make_feature(game * thegame)
{
    //Delete feature if it exists since this gets called in the constructor check memory
    if(feature)
    {
	    delete feature;
    }
    //Random int for the type of tile we will use to keep it random
    int random_num = rand() % 10;
    //Should allow for 10% of the tiles to be of teleporter 
    if (random_num == 9)
    {
      if (thegame)
      {
        feature = new teleport(thegame->board_width(), thegame->board_height());
      }
      else
      {
        feature = new teleport();
      }
  //feature = dynamic_cast<teleport*>(feature);
  // other features...
    }
  else if(random_num == 8)
  {
          feature = new sand_trap();//contructos a sand trap in tile
  }
  else if(random_num == 7 || random_num == 3)
  {
  	  feature = new spike();//Sets a spike trap on this tile
  }
  else if(random_num == 4)
  {
	  feature = new goal();//constructs Goals on tiles
  }
  else
  {
    feature = new tile_feature();//Empty tiles to avoid making game impossible
  }
}

//CLASS FUCNTIONS FOR TILE FEATURES
//A base tile feature constructor, sets legend blank for basic tiles to be blank
tile_feature::tile_feature()
{
        legend = ' ';
}

//Based on the kind of tile made the correct legend will be past into the constructor
tile_feature::tile_feature(char Legend)
{
	legend = Legend;
}

//Destructor
tile_feature::~tile_feature()
{
	if(legend)
		legend = 0;
}

//Returns the legend of the tile feature probably only gonna be sued in the display board function
char tile_feature::get_legend()
{
        return legend;
}

//Empty process the derived classes will have specific processes
void tile_feature::process(game * thegame)
{}


//CLASS FUNCTIONS FOR TELEPORTING
//Base teleport constructor 
teleport::teleport(): tile_feature('T')//Pass the character to the tile feature to ensure the legend is correct
{
	x = 0;
	y = 0;	
}

//Constructor with the target you will be teleported to
teleport::teleport(int X, int Y): tile_feature('T')//Pass the character to the tile feature to ensure the legend is correct
{
	generate_target(X, Y);//Call the generate target function would be better for random location
}

//Destructor
teleport::~teleport()
{
	x = 0;
	y = 0;
}

//Generates random location to teleport to
void teleport::generate_target(int xmax, int ymax)
{
	x = rand() % xmax;
	y = rand() % ymax;
}
/*
void teleport::teleport_noop()
{
  cout << : "TEST";	
}*/

//The actual process that the player 'goes through' when stepping on a teleporter
void teleport::process(game * thegame)
{
	thegame->change_location(x, y);//We pass in the target location of the teleporter
	cout << "Teleporting to " << x << "," << y << "!" << endl;//Tell the user where they are going
}


//CLASS FUNCTIONS FOR SAND TRAP
//Base constructor for a sand trap
sand_trap::sand_trap(): tile_feature('S')//Pass the correct character to the legend for labeling correct tile
{
	length = 4;//Player will be stuck for this length of turns
}

//Constructor if we pass in a length of time diff than 4
sand_trap::sand_trap(int Length): tile_feature('S')//Pass the correct character to the legend for labeling correct tile)
{
	length = Length;//set length to Length
}

//Destructor
sand_trap::~sand_trap()
{
	length = 0;
}

//The specific process a player goes through when stepping on a sand trap tile
void sand_trap::process(game * thegame)
{
	thegame->change_status(length);//Set the status to a number greater than 0
	cout << "You fell into a sand trap!" << endl;//Display to the player a message
}

//CLASS FUNCTION FOR SPIKE TRAP
//Constructor for a spike trap
spike::spike(): tile_feature('D')
{
	dmg = rand() % 10;//This spike trap will deal a random number 0-10
	 
}

//destructor
spike::~spike()
{
	dmg = 0;
}

//The specific process a player goes through when stepping on a spike trap tile
void spike::process(game * thegame)
{
	thegame->change_hp(dmg);//Change the players hp, they should take damage
	//For fun sometimes they manage to dodge the trap!
	if(dmg == 0)
	{
		cout << "A spike shoots from the floor and you manage to dodge it taking no damage!" << endl;
	}
	else
	//If they dont dodge they take damage and we should let them know
	cout << "A spike shot from the floor dealing " << dmg << " points of damage!" << endl;
}


//CLASS FUNCTIONS FOR THE POINTS
//Constructor for the points you want to pick up
goal::goal(): tile_feature('P')
{
	score = 1;//1 point per tile
}

//destructor
goal::~goal()
{
	score = 0;
}

//The process the player goes through stepping on a goal tile
void goal::process(game * thegame)
{
	thegame->change_pts(score);//Change the players score
	thegame->display_pts();//display the players score
}






