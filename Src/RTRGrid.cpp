#include "RTRGrid.h";

void RTRGrid::init() 
{
	rows = (20.0f + cell_size) / cell_size;
	cols = (20.0f + cell_size) / cell_size;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++) 
		{
			// Example Value bounds cell = { glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,0.0f,0.0f) };
			//grid.push_back(cell);
		}
	}
}

void RTRGrid::insert() 
{
	
}

void RTRGrid::remove() 
{
	
}