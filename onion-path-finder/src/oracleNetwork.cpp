/*
 * oracleNetwork.cpp
 *
 *  Created on: 26 May 2015
 *      Author: Adrian Antunez
 */

#include "oracleNetwork.h"
#include <algorithm>

OracleNetwork::OracleNetwork() :
		m_nodes(),
		m_destination(0),
		m_transmissionTime(0),
		m_MaxPaths(0),
		m_maxNodes(0),
		m_globalPath()
{}

OracleNetwork::OracleNetwork(Nodes nodes) :
		m_nodes(nodes),
		m_destination(0),
		m_transmissionTime(0),
		m_MaxPaths(0),
		m_maxNodes(0),
		m_globalPath()
{}

OracleNetwork::~OracleNetwork() {

}

PathVector OracleNetwork::getPaths(nodeid source, nodeid destination, uint32_t startingTime, int numPaths, int numNodes, uint32_t transmissionTime)
{
	PathVector pv;

	m_destination = destination;
	m_MaxPaths = numPaths;
	m_maxNodes = numNodes;
	m_transmissionTime = transmissionTime;
	m_globalPath = PathVector();

	Path path = Path();
	PathInfo info = PathInfo(source, startingTime);
	path.push_back(info);

	getPathsRecursive(path, startingTime);

	return m_globalPath;



//	NeighborsVector availableNeighbors = getAvailableNeighbors(??, ??, transmissionTime);

	return pv;
}

PathVector OracleNetwork::getPathsRecursive(Path currentPath, uint32_t currentTime)
{
	if ((int) currentPath.size() < m_maxNodes && (int) m_globalPath.size() < m_MaxPaths)
	{
		nodeid source = currentPath[currentPath.size() - 1].first;
		NeighborsVector availableNeighbors = getAvailableNeighbors(m_nodes[source], currentTime);

		for (size_t  i = 0; i < availableNeighbors.size(); ++i)
		{
			Neighbor* neighbor = availableNeighbors[i];
			Path oldPath = currentPath;
			PathInfo info = PathInfo(neighbor->getId(), neighbor->getActivationTime());
			currentPath.push_back(info);
			bool samePath = equalPathOfNodesInPathVector(m_globalPath, currentPath);
			if (neighbor->getId() == m_destination && currentPath.size() == (uint32_t) m_maxNodes && !samePath)
			{
				m_globalPath.push_back(currentPath);
			}
			else
			{
				getPathsRecursive(currentPath, neighbor->getActivationTime() + m_transmissionTime);
				currentPath = oldPath;
			}
		}
	}
	return m_globalPath;
}

NeighborsVector OracleNetwork::getAvailableNeighbors (Contacts contacts, uint32_t currentTime)
{
	NeighborsVector availableNeighbors = NeighborsVector();
	Contacts::iterator it = contacts.lower_bound(currentTime);
	while (it != contacts.end()) {
		NeighborsVector nv = it->second;
		for (size_t i = 0; i < nv.size(); ++i)
		{
			if (nv[i]->getActivationTime() >= currentTime && nv[i]->getDuration() >= m_transmissionTime)
			{
				availableNeighbors.push_back(nv[i]);
			}
		}
		++it;
	}
	return availableNeighbors;
}

void
OracleNetwork::printPaths (PathVector pv)
{
	for (size_t i = 0; i < pv.size(); ++i)
	{
		std::cout << "Path: " << i << std::endl;
		Path path = pv[i];
		for (size_t j = 0; j < path.size() - 1; ++j)
		{
			std::cout << "(" << path[j].first << ":" << path[j].second << "), ";
		}
		std::cout << "(" << path[path.size() - 1].first << ":" << path[path.size() - 1].second << ")" << std::endl;
	}
	std::cout << std::endl << "(n, t): Means send to node n at time t" << std::endl;
}

bool
OracleNetwork::equalPathOfNodesInPathVector (PathVector pv, Path p)
{
	if (pv.size() == 0 || p.size() == 0)
	{
		return false;
	}

	for (size_t i = 0; i < pv.size(); ++i)
	{
		if (pathEqualNodes(pv[i], p))
		{
			return true;
		}
	}
	return false;
}

bool
OracleNetwork::pathEqualNodes (Path p1, Path p2)
{
	if (p1.size() != p2.size())
	{
		return false;
	}
	else
	{
		for (size_t i = 0; i < p1.size(); ++i)
		{
			if (p1[i].first != p2[i].first)
			{
				return false;
			}
		}
	}
	return true;
}
