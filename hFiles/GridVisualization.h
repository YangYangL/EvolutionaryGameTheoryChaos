#include "DrawableGrid.h"

/*
 * This class contains the window for data visualization
 * Draws the DrawableGrid object to a window and updates it
 */
class GridVisualization
{
public:
	/*
	 * grid_type specifies the sub folder for the data
	 * mode specifies the distribution
	 * size specifies the size of one side of the grid e.g. 511 or 255
	 */
	GridVisualization(std::string grid_type, int mode, int size);

	//Runs the simulation
	void run();
private:
	/*
	 * Gets user input
	 * Contains functionality to pause, increment, and decrement the generations, as well as reset
	 * Needed to close the window
	 */
	void handleEvents();

	/*
	 * Updates the grid by calling the mapColors() method of the DrawableGrid object
	 * Does not perform this operation if paused field is true
	 */
	void update();

	/*
	 * Contains logic needed to display the grid on the window
	 * Further documentation on SFML windows can be found on sfml-dev.org
	 */
	void render();

	//Sets pause to true, suspending the operations performed in update()
	void pause();
private:
	bool paused;
	sf::RenderWindow mWindow;
	sf::Vector2f mWindowDimensions;
	DrawableGrid grid;
};