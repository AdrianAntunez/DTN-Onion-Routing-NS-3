//============================================================================
// Name        : onion-path-finder.cpp
// Author      : Adrian Antunez
// Version     :
// Copyright   : 
// Description : Finds k paths from a given contact table
//============================================================================

#include <iostream>
#include <cstdlib>

#include "parser.h"
#include "oracleNetwork.h"

Nodes nodes;

int main(int argc, char *argv[])
{
	if (argc != 7)
	{
		std::cout << "Usage: " << argv[0] << " <source> <destination> <time> <numPaths> <numNodes> <transmissionTime>" << std::endl;
		return 1;
	}
	nodes = Parser::getContactsFromTxt("data/paper-example.txt");
	OracleNetwork on = OracleNetwork(nodes);

	nodeid source = atoi(argv[1]);			// Source node
	nodeid destination = atoi(argv[2]);		// Destination node
	uint32_t startingTime = atoi(argv[3]);	// Starting time
	int numPaths = atoi(argv[4]);			// Number of paths to be retrieved
	int numNodes = atoi(argv[5]);			// Number of nodes for each path
	uint32_t transmissionTime = atoi(argv[6]);	// Time spent sending the message over nodes

	PathVector pv = on.getPaths(source, destination, startingTime, numPaths, numNodes, transmissionTime);

	on.printPaths(pv);
	return 0;
}
