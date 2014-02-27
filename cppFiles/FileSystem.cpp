#include "FileSystem.h"

FileWriter::FileWriter(std::string sub_folder, int width, int height, int distribution) : grid(width,height,distribution)
{
	assert(distribution == 1 || distribution == 0);
	dimensions.x = width;
	dimensions.y = height;
	generations = 0;
	subFolder = sub_folder;
}
void FileWriter::advance()
{
	grid.nextGeneration();
	generations++;
}
void FileWriter::writeToFile()
{
	std::ofstream output_file;
	std::ostringstream int_convert;
	int_convert << generations;
	output_file.open(subFolder + int_convert.str() + ".txt");

	for (int x = 0; x < dimensions.x; ++x)
	{
		for (int y = 0; y < dimensions.y; ++y)
		{
			output_file << grid.getStrat(y, x) << " ";
		}
	}
	output_file.close();
}

FileReader::FileReader(std::string sub_folder, int width, int height)
{
	dimensions.x = width;
	dimensions.y = height;
	subFolder = sub_folder;
}
void FileReader::extractData(int file_number)
{
	std::ifstream out_file;
	std::ostringstream int_convert;
	std::vector<int> tempVect;
	int current;
	
	int_convert << file_number;
	
	out_file.open(subFolder + int_convert.str() + ".txt");
	while (out_file >> current)
	{
		tempVect.push_back(current);
	}
	out_file.close();
	data.push_back(tempVect);
}
std::vector<int> FileReader::getData(int file_number)
{
	if (file_number < data.size())
	{
		return data[file_number];
	}
	else
	{
		std::vector<int> empty;
		std::cout << "\nInvalid vector subscript in FileReader::getData(int file_number) returning empty vector<int>\n";
		return empty;
	}
}
sf::Vector2i FileReader::getDimensions()
{
	return dimensions;
}