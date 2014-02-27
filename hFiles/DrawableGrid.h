#include "FileSystem.h"


/*
 * This class intereprets the data collected by a FileReader object
 * and converts it into data that can be drawn to the screen using SFML
 */
class DrawableGrid : public sf::Drawable
{
public:
	//Specify the subfolder of the data, as well as the width, height, and distribution of the grid
	DrawableGrid(std::string sub_folder, int width, int height, int distribution);

	/*
	 * FileWriter object writes a number of files specified by generations parameter
	 * FileReader object collects the data created
	 */
	void createData(int generations);

	/*
	 * Overloaded version of createData
	 * already_created parameter gives the option not to write
	 * data to files using the FileWriter object if
	 * the data has been written to a file before-hand
	 */
	void createData(int generations, bool already_created);

	/*
	 * Contains logic to set the color of each point in the vertex array
	 * generation parameter specifies which file to map the colors from
	 * sets the currentGenIndex field to generation and advances after all operations are finished
	 */
	void mapColors(int generation);

	/*
	 * Maps the colors based on the currentGenIndex field
	 * Advances generation once operation is finished
	 */
	void mapColors();

	/*
	 * Resets currentGenIndex to 0
	 * Maps all elements of lastColors field to Black
	 */
	void reset();

	//returns the currentGenIndex field
	int getGeneration();

private:
	/*
	 * Increments the currentGenIndex field
	 * calls reset() if end has been reached
	 */
	void advance();

	//determines if the last generation has been reached
	bool reachedLastGen();

	/*
	 * Needed to inherit from sf::Drawable
	 * documentation at www.sfml-dev.org
	 */
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		target.draw(points, states);
	}
private:
	int currentGenIndex;
	int maxGen;
	sf::VertexArray points;
	std::vector<sf::Color> lastColors;
	sf::Vector2i dimensions;
	FileWriter files;
	FileReader data;
};