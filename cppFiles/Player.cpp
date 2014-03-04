#include "Player.h"

int findHighest8(double self, double p1, double p2, double p3, double p4, double p5, double p6, double p7, double p8)
{
	double arr[] = { p1, p2, p3, p4, p5, p6, p7, p8 };
	int index = 0;
	double highest = arr[0];
	for (int i = 0; i < 8; ++i)
	{
		for (int k = 0; k < 8; ++k)
		{
			if (arr[k] > arr[i])
			{
				if (highest < arr[k])
				{
					highest = arr[k];
					index = k;
				}
			}
		}
	}
	if (self < highest)
		return index;
	else
		return -1;
}


int findHighest5(double self, double p1, double p2, double p3, double p4, double p5)
{
	double arr[] = { p1, p2, p3, p4, p5 };
	int index = 0;
	double highest = arr[0];
	for (int i = 0; i < 5; ++i)
	{
		for (int k = 0; k < 5; ++k)
		{
			if (arr[k] > arr[i])
			{
				if (highest < arr[k])
				{
					highest = arr[k];
					index = k;
				}
			}
		}
	}
	if (self < highest)
		return index;
	else
		return -1;
}


int findHighest3(double self, double p1, double p2, double p3)
{
	double arr[] = { p1, p2, p3 };
	int index = 0;
	double highest = arr[0];
	for (int i = 0; i < 3; ++i)
	{
		for (int k = 0; k < 3; ++k)
		{
			if (arr[k] > arr[i])
			{
				if (highest < arr[k])
				{
					highest = arr[k];
					index = k;
				}
			}
		}
	}
	if (self < highest)
		return index;
	else
		return -1;
}

Player::Player(int strategy, int x, int y)
{
	currentStrat = strategy;
	lastStrat = strategy;
	genSum = 0;
	setNext = false;
	position.x = x;
	position.y = y;
}

void Player::setVals(int strategy, int x, int y)
{
	currentStrat = strategy;
	lastStrat = strategy;
	genSum = 0;
	setNext = false;
	position.x = x;
	position.y = y;
}

void Player::setNextStrat(int strategy)
{
	nextStrat = strategy;
	setNext = true;
}

void Player::changeStrat()
{
	if (setNext)
	{
		lastStrat = currentStrat;
		currentStrat = nextStrat;
		setNext = false;
	}
}

void Player::addToSum(double val)
{
	genSum += val;
}

void Player::resetSum()
{
	genSum = 0;
}


void Player::playGame(Player other)
{
	switch (getStrat())
	{
	case 0:
		switch (other.getStrat())
		{
		case 0:
			addToSum(1);
			break;
		case 1:
			break;
		default:
			break;
		}
		break;
	case 1:
		switch (other.getStrat())
		{
		case 0:
			addToSum(1.9);
			break;
		case 1:
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void Player::playGame()
{
	switch (getStrat())
	{
	case 0:
		addToSum(1);
		break;
	case 1:
		break;
	default:
		break;
	}
}

int Player::getLastStrat()
{
	return lastStrat;
}

int Player::getStrat()
{
	return currentStrat;
}

double Player::getSum()
{
	return genSum;
}

int Player::getX()
{
	return position.x;
}

int Player::getY()
{
	return position.y;
}

sf::Vector2f Player::getPositionf()
{
	return sf::Vector2f(getX(), getY());
}

bool Player::otherIsGreater(Player other)
{
	return other.getSum() > genSum;
}

//TODO: Add more distributions
PlayerGrid::PlayerGrid(int width, int height, int strat_dist_mode)
{
	//Initialize the random seed
	srand(time(NULL));
	
	//Reserve enough space for all players in vector
	players.reserve(width*height);
	
	//Set the dimensions of the obect
	dimensions.x = width;
	dimensions.y = height;
	
	//Determines the layour of the grid
	switch (strat_dist_mode)
	{
		//Randomly distributes cooperators and defectors
	case 0:
		for (int i = 0; i < width; ++i)
		{
			for (int k = 0; k < height; ++k)
			{
				Player tempPlayer(rand() % 2, i, k);
				players.push_back(tempPlayer);
			}
		}
		break;
		//One defector in the middle
		//Rest are cooperators
	case 1:
		for (int i = 0; i < width; ++i)
		{
			for (int k = 0; k < height; ++k)
			{
				Player tempPlayer(0, 0, 0);
				if (width % 2 == 0 || height % 2 == 0)
				{
					if (i == width/2 && k == height/2)
						tempPlayer.setVals(1, i, k);
					else
						tempPlayer.setVals(0, i, k);
				}
				else
				{
					if (i == (width+1)/2 && k == (height+1)/2)
						tempPlayer.setVals(1, i, k);
					else
						tempPlayer.setVals(0, i, k);
				}
				players.push_back(tempPlayer);
			}
		}
		break;
		//Uses random distribution if any other value is used as input
	default:
		for (int i = 0; i < width; ++i)
		{
			for (int k = 0; k < height; ++k)
			{
				Player tempPlayer(rand() % 2, i, k);
				players.push_back(tempPlayer);
			}
		}
		break;
	}
	
}
int PlayerGrid::getStrat(int x, int y)
{
	return findPlayer(x, y).getStrat();
}
int PlayerGrid::getLastStrat(int x, int y)
{
	return findPlayer(x, y).getLastStrat();
}
double PlayerGrid::getSum(int x, int y)
{
	return findPlayer(x, y).getSum();
}
void PlayerGrid::nextGeneration()
{
	for (int i = 0; i < dimensions.x; ++i)
	{
		for (int k = 0; k < dimensions.y; ++k)
		{
			//Every player plays the game against their neighbors
			play(findPlayer(k, i));
		}
	}
	for (int i = 0; i < dimensions.x; ++i)
	{
		for (int k = 0; k < dimensions.y; ++k)
		{
			//The generation sums of each player is compares to their neighbors
			compareTo(findPlayer(k, i));
		}
	}
	//The players update their strategies and reset their sums
	update();
}
Player &PlayerGrid::findPlayer(int x, int y)
{
	return players[(dimensions.y*y) + x];
}
void PlayerGrid::play(Player &player)
{
	//Check if the player is on an edge or corner
	if (player.getX() == 0 || player.getX() == dimensions.x - 1 || player.getY() == 0 || player.getY() == dimensions.y - 1)
	{
		//Top-left corner
		if (player.getX() == 0 && player.getY() == 0)
		{
			player.playGame();
			player.playGame(findPlayer(player.getX(), player.getY() + 1));

			player.playGame(findPlayer(player.getX() + 1, player.getY()));
			player.playGame(findPlayer(player.getX() + 1, player.getY() + 1));
		}
		//Bottom-lef corner
		else if (player.getX() == 0 && player.getY() == dimensions.y - 1)
		{
			player.playGame();
			player.playGame(findPlayer(player.getX(), player.getY() - 1));

			player.playGame(findPlayer(player.getX() + 1, player.getY()));
			player.playGame(findPlayer(player.getX() + 1, player.getY() - 1));
		}
		//Top-right corner
		else if (player.getX() == dimensions.x - 1 && player.getY() == 0)
		{
			player.playGame();
			player.playGame(findPlayer(player.getX(), player.getY() + 1));

			player.playGame(findPlayer(player.getX() - 1, player.getY()));
			player.playGame(findPlayer(player.getX() - 1, player.getY() + 1));
		}
		//Bottom-right corner
		else if (player.getX() == dimensions.x - 1 && player.getY() == dimensions.y - 1)
		{
			player.playGame();
			player.playGame(findPlayer(player.getX(), player.getY() - 1));

			player.playGame(findPlayer(player.getX() - 1, player.getY()));
			player.playGame(findPlayer(player.getX() - 1, player.getY() - 1));
		}
		//Left edge(no corners)
		else if (player.getX() == 0 && (player.getY() > 0 && player.getY() < dimensions.y - 1))
		{
			player.playGame();
			player.playGame(findPlayer(player.getX(), player.getY() + 1));
			player.playGame(findPlayer(player.getX(), player.getY() - 1));

			player.playGame(findPlayer(player.getX() + 1, player.getY()));
			player.playGame(findPlayer(player.getX() + 1, player.getY() + 1));
			player.playGame(findPlayer(player.getX() + 1, player.getY() - 1));
		}
		//Right edge(no corners)
		else if (player.getX() == dimensions.x - 1 && (player.getY() > 0 && player.getY() < dimensions.y - 1))
		{
			player.playGame();
			player.playGame(findPlayer(player.getX(), player.getY() + 1));
			player.playGame(findPlayer(player.getX(), player.getY() - 1));

			player.playGame(findPlayer(player.getX() - 1, player.getY()));
			player.playGame(findPlayer(player.getX() - 1, player.getY() + 1));
			player.playGame(findPlayer(player.getX() - 1, player.getY() - 1));
		}
		//Top edge(no corners)
		else if (player.getY() == 0 && (player.getX() > 0 && player.getX() < dimensions.x - 1))
		{
			player.playGame();
			player.playGame(findPlayer(player.getX(), player.getY() + 1));

			player.playGame(findPlayer(player.getX() + 1, player.getY()));
			player.playGame(findPlayer(player.getX() + 1, player.getY() + 1));

			player.playGame(findPlayer(player.getX() - 1, player.getY()));
			player.playGame(findPlayer(player.getX() - 1, player.getY() + 1));
		}
		//Bottom edge(no corners)
		else if (player.getY() == dimensions.y - 1 && (player.getX() > 0 && player.getX() < dimensions.x - 1))
		{
			player.playGame();
			player.playGame(findPlayer(player.getX(), player.getY() - 1));

			player.playGame(findPlayer(player.getX() + 1, player.getY()));
			player.playGame(findPlayer(player.getX() + 1, player.getY() - 1));

			player.playGame(findPlayer(player.getX() - 1, player.getY()));
			player.playGame(findPlayer(player.getX() - 1, player.getY() - 1));
		}

	}
	//All players that are not in corners or on edges
	else
	{
		player.playGame();
		player.playGame(findPlayer(player.getX(), player.getY() + 1));
		player.playGame(findPlayer(player.getX(), player.getY() - 1));

		player.playGame(findPlayer(player.getX() + 1, player.getY()));
		player.playGame(findPlayer(player.getX() + 1, player.getY() + 1));
		player.playGame(findPlayer(player.getX() + 1, player.getY() - 1));

		player.playGame(findPlayer(player.getX() - 1, player.getY()));
		player.playGame(findPlayer(player.getX() - 1, player.getY() + 1));
		player.playGame(findPlayer(player.getX() - 1, player.getY() - 1));
	}
}
void PlayerGrid::compareTo(Player &player)
{
	//Same position checking as PlayerGrid::Play(Player &player)
	if (player.getX() == 0)
	{
		//Top-left corner
		if (player.getY() == 0)
		{
			switch (findHighest3(player.getSum(),
				findPlayer(player.getX(), player.getY() + 1).getSum(),
				findPlayer(player.getX() + 1, player.getY()).getSum(),
				findPlayer(player.getX() + 1, player.getY() + 1).getSum()))
			{
			case -1:
				player.setNextStrat(player.getStrat());
				break;
			case 0:
				player.setNextStrat(findPlayer(player.getX(), player.getY() + 1).getStrat());
				break;
			case 1:
				player.setNextStrat(findPlayer(player.getX() + 1, player.getY()).getStrat());
				break;
			case 2:
				player.setNextStrat(findPlayer(player.getX() + 1, player.getY() + 1).getStrat());
				break;
			default:
				break;
			}
		}
		//Bottom-left corner
		else if (player.getY() == dimensions.y - 1)
		{
			switch (findHighest3(player.getSum(),
				findPlayer(player.getX(), player.getY() - 1).getSum(),
				findPlayer(player.getX() + 1, player.getY()).getSum(),
				findPlayer(player.getX() + 1, player.getY() - 1).getSum()))
			{
			case -1:
				player.setNextStrat(player.getStrat());
				break;
			case 0:
				player.setNextStrat(findPlayer(player.getX(), player.getY() - 1).getStrat());
				break;
			case 1:
				player.setNextStrat(findPlayer(player.getX() + 1, player.getY()).getStrat());
				break;
			case 2:
				player.setNextStrat(findPlayer(player.getX() + 1, player.getY() - 1).getStrat());
				break;
			default:
				break;
			}
		}
		//left edge
		else
		{
			switch (findHighest5(player.getSum(),
				findPlayer(player.getX(), player.getY() + 1).getSum(),
				findPlayer(player.getX(), player.getY() - 1).getSum(),
				findPlayer(player.getX() + 1, player.getY()).getSum(),
				findPlayer(player.getX() + 1, player.getY() + 1).getSum(),
				findPlayer(player.getX() + 1, player.getY() - 1).getSum()))
			{
			case -1:
				player.setNextStrat(player.getStrat());
				break;
			case 0:
				player.setNextStrat(findPlayer(player.getX(), player.getY() + 1).getStrat());
				break;
			case 1:
				player.setNextStrat(findPlayer(player.getX(), player.getY() - 1).getStrat());
				break;
			case 2:
				player.setNextStrat(findPlayer(player.getX() + 1, player.getY()).getStrat());
				break;
			case 3:
				player.setNextStrat(findPlayer(player.getX() + 1, player.getY() + 1).getStrat());
				break;
			case 4:
				player.setNextStrat(findPlayer(player.getX() + 1, player.getY() - 1).getStrat());
				break;
			default:
				break;
			}
		}
	}
	else if (player.getX() == dimensions.x - 1)
	{
		//Top-right corner
		if (player.getY() == 0)
		{
			switch (findHighest3(player.getSum(),
				findPlayer(player.getX(), player.getY() + 1).getSum(),
				findPlayer(player.getX() - 1, player.getY()).getSum(),
				findPlayer(player.getX() - 1, player.getY() + 1).getSum()))
			{
			case -1:
				player.setNextStrat(player.getStrat());
				break;
			case 0:
				player.setNextStrat(findPlayer(player.getX(), player.getY() + 1).getStrat());
				break;
			case 1:
				player.setNextStrat(findPlayer(player.getX() - 1, player.getY()).getStrat());
				break;
			case 2:
				player.setNextStrat(findPlayer(player.getX() - 1, player.getY() + 1).getStrat());
				break;
			default:
				break;
			}
		}
		//Bottom-right corner
		else if (player.getY() == dimensions.y - 1)
		{
			switch (findHighest3(player.getSum(),
				findPlayer(player.getX(), player.getY() - 1).getSum(),
				findPlayer(player.getX() - 1, player.getY()).getSum(),
				findPlayer(player.getX() - 1, player.getY() - 1).getSum()))
			{
			case -1:
				player.setNextStrat(player.getStrat());
				break;
			case 0:
				player.setNextStrat(findPlayer(player.getX(), player.getY() - 1).getStrat());
				break;
			case 1:
				player.setNextStrat(findPlayer(player.getX() - 1, player.getY()).getStrat());
				break;
			case 2:
				player.setNextStrat(findPlayer(player.getX() - 1, player.getY() - 1).getStrat());
				break;
			default:
				break;
			}
		}
		//Right edge
		else
		{
			switch (findHighest5(player.getSum(),
				findPlayer(player.getX(), player.getY() + 1).getSum(),
				findPlayer(player.getX(), player.getY() - 1).getSum(),
				findPlayer(player.getX() - 1, player.getY()).getSum(),
				findPlayer(player.getX() - 1, player.getY() + 1).getSum(),
				findPlayer(player.getX() - 1, player.getY() - 1).getSum()))
			{
			case -1:
				player.setNextStrat(player.getStrat());
				break;
			case 0:
				player.setNextStrat(findPlayer(player.getX(), player.getY() + 1).getStrat());
				break;
			case 1:
				player.setNextStrat(findPlayer(player.getX(), player.getY() - 1).getStrat());
				break;
			case 2:
				player.setNextStrat(findPlayer(player.getX() - 1, player.getY()).getStrat());
				break;
			case 3:
				player.setNextStrat(findPlayer(player.getX() - 1, player.getY() + 1).getStrat());
				break;
			case 4:
				player.setNextStrat(findPlayer(player.getX() - 1, player.getY() - 1).getStrat());
				break;
			default:
				break;
			}
		}
	}
	//Top edge
	else if (player.getY() == 0 && ((player.getX() > 0 && player.getX() < dimensions.x - 1)))
	{
		switch (findHighest5(player.getSum(),
			findPlayer(player.getX(), player.getY() + 1).getSum(),
			findPlayer(player.getX() + 1, player.getY()).getSum(),
			findPlayer(player.getX() + 1, player.getY() + 1).getSum(),
			findPlayer(player.getX() - 1, player.getY()).getSum(),
			findPlayer(player.getX() - 1, player.getY() + 1).getSum()))
		{
		case -1:
			player.setNextStrat(player.getStrat());
			break;
		case 0:
			player.setNextStrat(findPlayer(player.getX(), player.getY() + 1).getStrat());
			break;
		case 1:
			player.setNextStrat(findPlayer(player.getX() + 1, player.getY()).getStrat());
			break;
		case 2:
			player.setNextStrat(findPlayer(player.getX() + 1, player.getY() + 1).getStrat());
			break;
		case 3:
			player.setNextStrat(findPlayer(player.getX() - 1, player.getY()).getStrat());
			break;
		case 4:
			player.setNextStrat(findPlayer(player.getX() - 1, player.getY() + 1).getStrat());
			break;
		default:
			break;
		}
	}
	//Bottom edge
	else if (player.getY() == dimensions.y - 1 && ((player.getX() > 0 && player.getX() < dimensions.x - 1)))
	{
		switch (findHighest5(player.getSum(),
			findPlayer(player.getX(), player.getY() - 1).getSum(),
			findPlayer(player.getX() + 1, player.getY()).getSum(),
			findPlayer(player.getX() + 1, player.getY() - 1).getSum(),
			findPlayer(player.getX() - 1, player.getY()).getSum(),
			findPlayer(player.getX() - 1, player.getY() - 1).getSum()))
		{
		case -1:
			player.setNextStrat(player.getStrat());
			break;
		case 0:
			player.setNextStrat(findPlayer(player.getX(), player.getY() - 1).getStrat());
			break;
		case 1:
			player.setNextStrat(findPlayer(player.getX() + 1, player.getY()).getStrat());
			break;
		case 2:
			player.setNextStrat(findPlayer(player.getX() + 1, player.getY() - 1).getStrat());
			break;
		case 3:
			player.setNextStrat(findPlayer(player.getX() - 1, player.getY()).getStrat());
			break;
		case 4:
			player.setNextStrat(findPlayer(player.getX() - 1, player.getY() - 1).getStrat());
			break;
		default:
			break;
		}
	}
	//Everything else
	else
	{
		switch (findHighest8(player.getSum(),
				findPlayer(player.getX(), player.getY() + 1).getSum(),
				findPlayer(player.getX(), player.getY() - 1).getSum(), 
				findPlayer(player.getX() + 1, player.getY()).getSum(),
				findPlayer(player.getX() + 1, player.getY() + 1).getSum(),
				findPlayer(player.getX() + 1, player.getY() - 1).getSum(),
				findPlayer(player.getX() - 1, player.getY()).getSum(),
				findPlayer(player.getX() - 1, player.getY() + 1).getSum(),
				findPlayer(player.getX() - 1, player.getY() - 1).getSum()))
		{
		case -1:
			player.setNextStrat(player.getStrat());
			break;
		case 0:
			player.setNextStrat(findPlayer(player.getX(), player.getY() + 1).getStrat());
			break;
		case 1:
			player.setNextStrat(findPlayer(player.getX(), player.getY() - 1).getStrat());
			break;
		case 2:
			player.setNextStrat(findPlayer(player.getX() + 1, player.getY()).getStrat());
			break;
		case 3:
			player.setNextStrat(findPlayer(player.getX() + 1, player.getY() + 1).getStrat());
			break;
		case 4:
			player.setNextStrat(findPlayer(player.getX() + 1, player.getY() - 1).getStrat());
			break;
		case 5:
			player.setNextStrat(findPlayer(player.getX() - 1, player.getY()).getStrat());
			break;
		case 6:
			player.setNextStrat(findPlayer(player.getX() - 1, player.getY() + 1).getStrat());
			break;
		case 7:
			player.setNextStrat(findPlayer(player.getX() - 1, player.getY() - 1).getStrat());
			break;
		default:
			break;
		}
	}
}
//Updates the strategies of all players and resets their sums for the next generation
void PlayerGrid::update()
{
	/*
	for (int x = 0; x < dimensions.x; ++x)
	{
		for (int y = 0; y < dimensions.y; ++y)
		{
			std::cout << getStrat(y,x) << " ";
		}
		std::cout << "\n";
	}
	*/
	std::vector<Player>::iterator p_it;
	for (p_it = players.begin(); p_it != players.end(); ++p_it)
	{
		p_it->changeStrat();
		p_it->resetSum();
	}
}
