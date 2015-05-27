/*
 * Parser.cpp
 *
 *  Created on: 26 May 2015
 *      Author: Adrian Antunez
 */

#include "parser.h"

#include <iostream>
#include <fstream>
#include <sstream>



Nodes
Parser::getContactsFromTxt (std::string fileName)
{
	std::ifstream infile;
	std::string line;
	uint32_t hostId = 0, neighborId = 0;
	uint32_t activationTime = 0, duration = 0;

	Nodes nodes;


	infile.open(fileName.c_str());

	if (infile.is_open())
	{

		while (infile >> hostId >> neighborId >> activationTime >> duration)
		{
			Neighbor *neighbor = new Neighbor(hostId, neighborId, activationTime, duration);
			nodes[hostId][(uint32_t) activationTime].push_back(neighbor);
		}
	}
	else
	{
		std::cout << "Unable to open file" << std::endl;
	}

	return nodes;
}
