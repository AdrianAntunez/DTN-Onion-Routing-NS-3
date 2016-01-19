/**
 * @copyright
 * Copyright (C) 2016 Universitat Autònoma de Barcelona
 * Department of Information and Communications Engineering
 * @file oracle-network.cpp
 * @author Adrian Antunez
 * @author Rubén Martinez <rmartinez@deic.uab.cat>
 * @date Created on: 26 May 2015
 */

#include "oracle-network.h"
#include <algorithm>

OracleNetwork::OracleNetwork() :
        GraphUtil()
{}

OracleNetwork::OracleNetwork(Nodes nodes, nodeid source, nodeid destination, uint32_t startTime, uint32_t numPaths, uint32_t numNodes, uint32_t transmissionTime, bool noCycles) :
        GraphUtil(nodes,source,numPaths,numNodes,transmissionTime,noCycles),
        m_targetNode(destination),
        m_startingTime(startTime)
{}

OracleNetwork::~OracleNetwork() {

}

PathVector OracleNetwork::getPaths()
{   
	m_globalPath = PathVector();

	Path path = Path();
    PathInfo info = PathInfo(m_sourceNode, m_startingTime);
	path.push_back(info);

    return getPathsRecursive(path, m_startingTime);
}

PathVector OracleNetwork::getPathsRecursive(Path currentPath, uint32_t currentTime)
{
	bool samePath = false;
    if ((int) currentPath.size() != m_maxNodes && (int) m_globalPath.size() < m_maxPaths)
	{
		nodeid source = currentPath[currentPath.size() - 1].first;
        NeighborsVector availableNeighbors = getAvailableNeighborsAtTime(m_nodes[source], currentTime);

		for (size_t  i = 0; i < availableNeighbors.size(); ++i)
		{
            std::shared_ptr<Neighbor> neighbor = availableNeighbors[i];
			Path oldPath = currentPath;
            PathInfo info = PathInfo(neighbor->getId(), std::max(neighbor->getActivationTime(), currentTime) + m_transmissionTime);
            if(m_noCycles && nodeInPath(currentPath, neighbor->getId()))
            {
              continue;
            }
			currentPath.push_back(info);
			samePath = equalPathOfNodesInPathVector(m_globalPath, currentPath);            
            if (neighbor->getId() == m_targetNode && currentPath.size() == (uint32_t) m_maxNodes && !samePath)
			{
				m_globalPath.push_back(currentPath);
			}
			else
			{
                getPathsRecursive(currentPath, std::max(neighbor->getActivationTime(), currentTime) + m_transmissionTime);
			}
			currentPath = oldPath;
		}
	}
	return m_globalPath;
}
