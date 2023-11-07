#include "Levelmap.h"
#include <string>
#include <fstream>
#include <iostream>

Levelmap::Levelmap()
{}

 void Levelmap::getLevel(int i, int j, Levelmap &Level)
{;
	std::string lvl = "map";
	std::string lvl1 = lvl + std::to_string(lnr);
	std::string fileName = "maps/" + lvl1 + ".txt";

	std::ifstream file;
	file.open(fileName);
	if (file.fail())
	{
		perror(fileName.c_str());
		exit(1);
	}
	std::string row;

		for (int i = 0; i < 10; i++)
		{
			getline(file, row);
			for (int j = 0; j < 30; j++)
			{
				z[i][j] = row[j];
			}
		}
}

 int Levelmap::getPortalY()
 {
	 for (int i = 0; i < 10; i++)
	 {
		 for (int j = 0; j < 30; j++)
		 {
			 if (z[i][j] == 'P')
			 {
				 return i;
			 }
		 }
	 }
 }

 int Levelmap::getPortalX()
 {
	 for (int i = 0; i < 10; i++)
	 {
		 for (int j = 0; j < 30; j++)
		 {
			 if (z[i][j] == 'P')
			 {
				 return j;
			 }
		 }
	 }
 }