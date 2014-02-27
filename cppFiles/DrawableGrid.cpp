#include "DrawableGrid.h"

DrawableGrid::DrawableGrid(std::string sub_folder, int width, int height, int distribution) : 
files(sub_folder, width, height, distribution), 
data(sub_folder, width, height)
{
	currentGenIndex = 0;
	maxGen = 0;
	dimensions.x = width;
	dimensions.y = height;
	points.resize(width*height);
	points.setPrimitiveType(sf::Points);
	for (int i = 0; i < dimensions.x; ++i)
	{
		for (int k = 0; k < dimensions.y; ++k)
		{
			points[(k*dimensions.x)+i].position = sf::Vector2f(i, k);
			lastColors.push_back(sf::Color::Black);
		}
	}
}
void DrawableGrid::createData(int generations)
{
	maxGen = generations;
	sf::Clock timer;
	for (int i = 0; i < generations; ++i)
	{
		files.writeToFile();
		files.advance();
	}
	for (int k = 0; k < generations; ++k)
	{
		data.extractData(k);
	}
	std::cout << "\nTime in minutes to create and extract data: " << timer.getElapsedTime().asSeconds() / 60 << "\n";
}
void DrawableGrid::createData(int generations, bool already_created)
{
	maxGen = generations;
	if (already_created)
	{
		for (int k = 0; k < generations; ++k)
		{
			data.extractData(k);
		}
	}
	else
	{
		for (int i = 0; i < generations; ++i)
		{
			files.writeToFile();
			files.advance();
		}
		for (int k = 0; k < generations; ++k)
		{
			data.extractData(k);
		}
	}
}
void DrawableGrid::mapColors()
{
	//sf::Clock timer;
	std::vector<int> genData = data.getData(currentGenIndex);
	for (int x = 0; x < dimensions.x; ++x)
	{
		for (int y = 0; y < dimensions.y; ++y)
		{
			switch (genData[(y*dimensions.y) + x])
			{
			case 0:
				if (lastColors[(y*dimensions.y) + x] == sf::Color::Blue)
				{
					points[(y*dimensions.y) + x].color = sf::Color::Blue;
					lastColors[(y*dimensions.y) + x] = sf::Color::Blue;
				}
				else if (lastColors[(y*dimensions.y) + x] == sf::Color::Red)
				{
					points[(y*dimensions.y) + x].color = sf::Color::Green;
					lastColors[(y*dimensions.y) + x] = sf::Color::Blue;
				}
				else
				{
					points[(y*dimensions.y) + x].color = sf::Color::Blue;
					lastColors[(y*dimensions.y) + x] = sf::Color::Blue;
				}
				break;
			case 1:
				if (lastColors[(y*dimensions.y) + x] == sf::Color::Blue)
				{
					points[(y*dimensions.y) + x].color = sf::Color::Yellow;
					lastColors[(y*dimensions.y) + x] = sf::Color::Red;
				}
				else if (lastColors[(y*dimensions.y) + x] == sf::Color::Red)
				{
					points[(y*dimensions.y) + x].color = sf::Color::Red;
					lastColors[(y*dimensions.y) + x] = sf::Color::Red;
				}
				else
				{
					points[(y*dimensions.y) + x].color = sf::Color::Red;
					lastColors[(y*dimensions.y) + x] = sf::Color::Red;
				}
				break;
			default:
				std::cout << "\nYou shouldn't see this!\n";
				break;
			}
		}
	}
	advance();
	//std::cout << "\nColor Mapping took: " << timer.getElapsedTime().asSeconds() << " seconds\n";
}
void DrawableGrid::mapColors(int generation)
{
	assert(generation > 0);
	if (generation > 999)
	{
		currentGenIndex = 0;
		reset();
	}
	currentGenIndex = generation;
	//sf::Clock timer;
	std::vector<int> genData = data.getData(generation);
	std::vector<int> lastGenData = data.getData(generation - 1);
	for (int i = 0; i < dimensions.x; ++i)
	{
		for (int k = 0; k < dimensions.y; ++k)
		{
			switch (lastGenData[(k*dimensions.y) + i])
			{
			case 0:
				lastColors[(k*dimensions.y) + i] = sf::Color::Blue;
				break;
			case 1:
				lastColors[(k*dimensions.y) + i] = sf::Color::Red;
				break;
			default:
				break;
			}
		}
	}
	for (int x = 0; x < dimensions.x; ++x)
	{
		for (int y = 0; y < dimensions.y; ++y)
		{
			switch (genData[(y*dimensions.y) + x])
			{
			case 0:
				if (lastColors[(y*dimensions.y) + x] == sf::Color::Blue)
				{
					points[(y*dimensions.y) + x].color = sf::Color::Blue;
					lastColors[(y*dimensions.y) + x] = sf::Color::Blue;
				}
				else if (lastColors[(y*dimensions.y) + x] == sf::Color::Red)
				{
					points[(y*dimensions.y) + x].color = sf::Color::Green;
					lastColors[(y*dimensions.y) + x] = sf::Color::Blue;
				}
				else
				{
					points[(y*dimensions.y) + x].color = sf::Color::Blue;
					lastColors[(y*dimensions.y) + x] = sf::Color::Blue;
				}
				break;
			case 1:
				if (lastColors[(y*dimensions.y) + x] == sf::Color::Blue)
				{
					points[(y*dimensions.y) + x].color = sf::Color::Yellow;
					lastColors[(y*dimensions.y) + x] = sf::Color::Red;
				}
				else if (lastColors[(y*dimensions.y) + x] == sf::Color::Red)
				{
					points[(y*dimensions.y) + x].color = sf::Color::Red;
					lastColors[(y*dimensions.y) + x] = sf::Color::Red;
				}
				else
				{
					points[(y*dimensions.y) + x].color = sf::Color::Red;
					lastColors[(y*dimensions.y) + x] = sf::Color::Red;
				}
				break;
			default:
				std::cout << "\nYou shouldn't see this!\n";
				break;
			}
		}
	}
	advance();
	//std::cout << "\nColor Mapping took: " << timer.getElapsedTime().asSeconds() << " seconds\n";
}
void DrawableGrid::advance()
{
	currentGenIndex++;
	if (reachedLastGen())
		reset();
}
void DrawableGrid::reset()
{
	currentGenIndex = 0;
	for (int i = 0; i < dimensions.x; ++i)
	{
		for (int k = 0; k < dimensions.y; ++k)
		{
			lastColors[(k*dimensions.y) + i] = sf::Color::Black;
		}
	}
}
int DrawableGrid::getGeneration()
{
	return currentGenIndex;
}
bool DrawableGrid::reachedLastGen()
{
	return currentGenIndex >= maxGen;
}