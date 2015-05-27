/*
 * oracleNetwork.h
 *
 *  Created on: 26 May 2015
 *      Author: Adrian Antunez
 */

#ifndef ORACLENETWORK_H_
#define ORACLENETWORK_H_

#include "neighbor.h"

typedef std::pair<nodeid, uint32_t> PathInfo;
typedef std::vector<PathInfo> Path;
typedef std::vector<Path> PathVector;

class OracleNetwork {
public:
	OracleNetwork();
	OracleNetwork(Nodes nodes);
	virtual ~OracleNetwork();

	PathVector getPaths(nodeid source, nodeid destination, uint32_t time, int numPaths, int numNodes, uint32_t transmissionTime);
	NeighborsVector getAvailableNeighbors (Contacts contacts, uint32_t currentTime);
	void printPaths (PathVector pv);
	bool equalPathOfNodesInPathVector (PathVector pv, Path p);
	bool pathEqualNodes (Path p1, Path p2);

private:

	PathVector getPathsRecursive(Path currentPath, uint32_t time);

	Nodes m_nodes;
	nodeid m_destination;
	uint32_t m_transmissionTime;
	int m_MaxPaths;
	int m_maxNodes;
	PathVector m_globalPath;

};

#endif /* ORACLENETWORK_H_ */
