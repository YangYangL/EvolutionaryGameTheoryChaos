#include "GridVisualization.h"

GridVisualization::GridVisualization(std::string grid_type, int mode, int size) : mWindow(sf::VideoMode(size, size), "Game Window"), grid(grid_type,size,size,mode)
{
	paused = false;
	mWindowDimensions = sf::Vector2f(size, size);
	sf::Clock timer;
	grid.createData(1000,true);
	//std::cout << "Creating Grid took " << timer.getElapsedTime().asSeconds() / 60 << " minutes\n";
}
void GridVisualization::run()
{
	while (mWindow.isOpen())
	{
		handleEvents();

		update();
		//std::cout << "Finished Updating\n";
		render();
	}
}
void GridVisualization::handleEvents()
{
	sf::Event current_event;
	while (mWindow.pollEvent(current_event))
	{
		if (current_event.type == sf::Event::Closed)
		{
			mWindow.close();
		}
		if (current_event.type == sf::Event::KeyPressed)
		{
			switch (current_event.key.code)
			{
			case sf::Keyboard::R:
				grid.reset();
				break;
			case sf::Keyboard::P:
				pause();
				break;
			case sf::Keyboard::Left:
				grid.mapColors(grid.getGeneration() - 1);
				break;
			case sf::Keyboard::Right:
				grid.mapColors(grid.getGeneration() + 1);
				break;
			default:
				break;
			}
		}
	}
}
void GridVisualization::update()
{
	if (!paused)
	{
		grid.mapColors();
	}
}
void GridVisualization::render()
{
	mWindow.clear();

	mWindow.draw(grid);

	mWindow.display();
}
void GridVisualization::pause()
{
	paused = !paused;
}
