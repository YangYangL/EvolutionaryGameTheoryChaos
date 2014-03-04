#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <string>

#include <iostream>
#include <sstream>
#include <fstream>

#include <cassert>
#include <ctime>
#include <cstdlib>

/*
Finds the highest of eight values
Returns -1 if self parameter is higher than all other values
Otherwise returns the highest value as an index: 0 - 7
*/
int findHighest8(double self, double p1, double p2, double p3, double p4, double p5, double p6, double p7, double p8);

/*
Finds the highest of five values
Returns -1 if self parameter is higher than all other values
Otherwise returns the highest value as an index: 0 - 4
*/
int findHighest5(double self, double p1, double p2, double p3, double p4, double p5);

/*
Finds the highest of three values
Returns -1 if self parameter is higher than all other values
Otherwise returns the value as an index: 0 - 2
*/
int findHighest3(double self, double p1, double p2, double p3);


class Player
{
public:
	/*
	Strategy represents the pure strategy **Must be 0 or 1, other values will cause unexpected problems**
	x and y parameters represent coordinates on the cartesian plane
	*/
	Player(int strategy, int x, int y);
	/*
	Reconstruction method
	Performs same operations as constructor
	*/
	void setVals(int strategy, int x, int y);

	/*
	Sets the next strategy to be changes upon calling changeStrat()
	*/
	void setNextStrat(int strategy);
	/*
	Changes the currentStrat field to the value set in setNextStrat(int strategy)
	if setNextStrat was not called before calling this method, it will not do anything
	*/
	void changeStrat();
	/*
	Sets genSum to 0
	*/
	void resetSum();
	/*
	Plays a Prisoner's Dilemma with another player, modifying the value of genSum
	based on the currentStrategy fields of both objects
	*/
	void playGame(Player other);
	/*
	Plays the game with itself
	*/
	void playGame();

	/*
	Returns the value of genSum
	*/
	double getSum();

	/*
	Returns the previous strategy
	*/
	int getLastStrat();
	/*
	Returns the current strategy
	*/
	int getStrat();
	/*
	Returns the x coordinate of this object
	*/
	int getX();
	/*
	Returns the y coordinate of this object
	*/
	int getY();

	/*
	Returns the position as a vector of float values
	*/
	sf::Vector2f getPositionf();

	/*
	Returns true if the other object's genSum field is greater than the calling object
	*/
	bool otherIsGreater(Player other);
private:
	/*
	Adds val to genSum field
	*/
	void addToSum(double val);
private:
	int currentStrat;
	int lastStrat;
	int nextStrat;
	bool setNext;
	double genSum;
	sf::Vector2i position;
};

class PlayerGrid
{
public:
	/*
	Initializes the grid of players with set dimensions width and height
	strat_dist_mode variable specifies the distribution of player strategies
	0 - Random
	1 - Defector in middle (if dimensions are not odd, it will be the value of the dimensions/2)
	*/
	PlayerGrid(int width, int height, int strat_dist_mode);

	/*
	 * Returns the strategy of the player at position (x,y)
	 */
	int getStrat(int x, int y);

	/*
	 * Returns the last strategy of the player at position (x,y)
	 */
	int getLastStrat(int x, int y);

	/*
	 * Returns the generation sum of the player at position (x,y)
	 */
	double getSum(int x, int y);

	/*
	Advances all players to next generation
	*/
	void nextGeneration();
private:
	/*
	Returns the first player found with coordinates equal to x and y
	*/
	Player &findPlayer(int x, int y);
	/*
	player object plays game against all neightbors and itself
	*/
	void play(Player &player);
	/*
	player object compares generation sums against all of its neighbors
	*/
	void compareTo(Player &player);
	/*
	Updates the strategies of all players
	Will have no effect if play and compareTo have not been called
	*/
	void update();
private:
	std::vector<Player> players;
	sf::Vector2i dimensions;
};
