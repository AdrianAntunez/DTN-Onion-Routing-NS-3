/**
 * @copyright
 * Copyright (C) 2015 Universitat Autònoma de Barcelona
 * Department of Information and Communications Engineering
 * @file basic-parser.cpp
 * @author Adrian Antunez
 * @date Created on:  26/5/2015
 */

#include "basic-parser.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <regex>
#include <string>

BasicParser::BasicParser()
{}
BasicParser::~BasicParser()
{}

Nodes
BasicParser::Parse (std::string fileName)
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
            std::shared_ptr<Neighbor> neighbor = std::make_shared<Neighbor>(hostId, neighborId, activationTime, duration);
			nodes[hostId][(uint32_t) activationTime].push_back(neighbor);
		}
	}
	else
	{
		std::cout << "Unable to open file" << std::endl;
	}

	return nodes;
}
