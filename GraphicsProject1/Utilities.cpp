#include "Utilities.h"
#include "cGameObject.h"
#include "cTriangle.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdlib>	// RAND_MAX
#include <map>	

void loadConfigFile(int& width, int& height, std::string& title) {
	std::ifstream infoFile("config.txt");
	if (!infoFile.is_open())
	{	// File didn't open...
		std::cout << "Can't find config file" << std::endl;
		std::cout << "Using defaults" << std::endl;
	}
	else
	{	// File DID open, so read it... 
		std::string a;

		infoFile >> a;	// "Game"	//std::cin >> a;
		infoFile >> a;	// "Config"
		infoFile >> a;	// "width"

		infoFile >> width;	// 1080

		infoFile >> a;	// "height"

		infoFile >> height;	// 768

		infoFile >> a;		// Title_Start

		std::stringstream ssTitle;		// Inside "sstream"
		bool bKeepReading = true;
		do
		{
			infoFile >> a;		// Title_End??
			if (a != "Title_End")
			{
				ssTitle << a << " ";
			}
			else
			{	// it IS the end! 
				bKeepReading = false;
				title = ssTitle.str();
			}
		} while (bKeepReading);


	}//if ( ! infoFile.is_open() )
}

glm::vec3 getTriangleCentroid(cPhysTriangle* theTriangle) {
	glm::vec3 theCenter(0.0f);

	theCenter.x = (theTriangle->vertex[0].x + theTriangle->vertex[0].x + theTriangle->vertex[0].x) / 3;
	theCenter.y = (theTriangle->vertex[1].y + theTriangle->vertex[1].y + theTriangle->vertex[1].y) / 3;
	theCenter.z = (theTriangle->vertex[2].z + theTriangle->vertex[2].z + theTriangle->vertex[2].z) / 3;

	return theCenter;
}

glm::vec3 getTriangleCentroid(glm::vec3 theTriangle[3]) {
	glm::vec3 theCenter(0.0f);

	theCenter.x = (theTriangle[0].x + theTriangle[0].x + theTriangle[0].x) / 3;
	theCenter.y = (theTriangle[1].y + theTriangle[1].y + theTriangle[1].y) / 3;
	theCenter.z = (theTriangle[2].z + theTriangle[2].z + theTriangle[2].z) / 3;

	return theCenter;
}

glm::vec3 getTriangleCentroid(glm::vec3* theTriangle[3]) {
	glm::vec3 theCenter(0.0f);

	theCenter.x = (theTriangle[0]->x + theTriangle[0]->x + theTriangle[0]->x) / 3;
	theCenter.y = (theTriangle[1]->y + theTriangle[1]->y + theTriangle[1]->y) / 3;
	theCenter.z = (theTriangle[2]->z + theTriangle[2]->z + theTriangle[2]->z) / 3;

	return theCenter;
}

void getXYFromRadiusAndAngle(float& x, float&y, float radius, float angle)
{
	x = radius * cos(angle);
	y = radius * sin(angle);
}

