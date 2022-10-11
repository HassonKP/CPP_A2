#include "prog2.h"
/*Name: Killian Hasson		Date:0/03/2021		Class:CS202
 *
 * This is the main file for the calling and using of the actual program and its classes, I wish I would have implemeneted a play class
 * So that I didnt need to repeat so much code but the base of it is a simple do while loop and different functions are executed based on
 * the response of the player.
 *
 * */
int main()
{
	int win = 1;//Int to check if the player has won
	int check;//Verify the players moves before trying anything
	int resp;//Int for basiuc response form the playyer
	game * the_game = new game;
	the_game->display_board();	
	//Let the user know at the start how to win
	cout << "You need to traverse around the board and collect 3 points, traverse to the 'P' tiles to collect 1 point!" << endl << endl;	
	//Do while loop for playing the game
	do
	{
	//Check if the player has won without continuing the loop
	if(the_game->check_pts() == 0)
	{
		cout << "You won!";
		break;
	}
	//Check to see if the player had died before looping
	if(the_game->check_hp() == 0 || the_game->check_hp() < 0)
	{
		cout << "You died!";
		break;
	}
	cout << "Please enter a character to decide what to do (8 to move up, 4 to move left, 6 to move right, 2 to move down): ";
	cin >> resp;	
		if(resp == 4)
		{
		  int X = -1;
		  int Y = 0;
		  check = the_game->change_location(X,Y);
                  if(check != 0)
                  {
                    tile * temp = the_game->get_tile_location();
                    temp->player_enters(the_game);
                    the_game->display_location();
                    the_game->display_board();
                  }
                }

		if(resp == 8)
		{
		  int X = 0;
		  int Y = -1;
		  check = the_game->change_location(X,Y);
		  if(check != 0)
		  {
		    tile * temp = the_game->get_tile_location();
		    temp->player_enters(the_game);
		    the_game->display_location();
		    the_game->display_board();
		  }
		}
		if(resp == 6)
		{
		  int X = 1;
		  int Y = 0;
		  check = the_game->change_location(X,Y);
		  if(check != 0)
		  {
		    tile * temp = the_game->get_tile_location();
		    temp->player_enters(the_game);
		    the_game->display_location();
		    the_game->display_board();
		  }
		}
		if(resp == 2)
		{
		  int X = 0;
		  int Y = 1;
		  check = the_game->change_location(X,Y);
		  if(check != 0)
		  {
		    tile * temp = the_game->get_tile_location();
		    temp->player_enters(the_game);
		    the_game->display_location();
		    the_game->display_board();
		  }
		}
		
	
	}while(resp != 0);	
	//Game over!
	cout << "\nGame over!\n";
}
