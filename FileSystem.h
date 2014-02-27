#include "Player.h"

/*
 * This class writes PlayerGrid data to files
 * The number of files is equal to the value of width*height
 * Distribution determines the starting layout of the player grid
 */
class FileWriter
{
public:
	FileWriter(std::string sub_folder, int width, int height, int distribution);

	//Writes the data of the grid's current state to the file
	void writeToFile();

	//Advances the generation of players
	void advance();
private:
	PlayerGrid grid;
	sf::Vector2i dimensions;
	std::string subFolder;
	int generations;
};

/*
 * This class reads data from the files created by a FileReader object
 * Stores the data of each file in a nested vector<int>
 * All files are stored in field vector< vector<int> > data
 */
class FileReader
{
public:
	FileReader(std::string sub_folder, int width, int height);

	/*
	 * Gets data from a file created by a FileReader object
	 * Stores data in data vector
	 */
	void extractData(int file_number);

	//Returns a vector<int> of the specified file data
	std::vector<int> getData(int file_number);

	//Returns the dimensions field
	sf::Vector2i getDimensions();
private:
	std::string subFolder;
	sf::Vector2i dimensions;
	std::vector< std::vector<int> > data;
};