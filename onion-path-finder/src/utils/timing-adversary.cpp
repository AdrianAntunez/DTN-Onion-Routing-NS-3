/**
 * @copyright
 * Copyright (C) 2016 Universitat Autònoma de Barcelona
 * Department of Information and Communications Engineering
 * @file timing-adversary.cpp
 * @author Rubén Martínez <rmartinez@deic.uab.cat>
 * @date Created on: 21/12/2015
 */

#include "timing-adversary.h"
#include <algorithm>

TimingBasedAdversary::TimingBasedAdversary() :
    GraphUtil(),
    m_endToEndDelay(0),
    m_dynamicGraph(false),
    m_ofSize(false),
    m_ofMaxTime(false)
{}

TimingBasedAdversary::TimingBasedAdversary(Nodes nodes, nodeid source, uint32_t numPaths, uint32_t numNodes, uint32_t transmissionTime,  uint32_t endToEndDelay, bool noCycles, bool dynamic, bool ofSize, bool maxTime) :
    GraphUtil(nodes,source,numPaths,numNodes,transmissionTime,noCycles),
    m_endToEndDelay(endToEndDelay),
    m_dynamicGraph(dynamic),
    m_ofSize(ofSize),
    m_ofMaxTime(maxTime)
{}

TimingBasedAdversary::~TimingBasedAdversary()
{

}

PathVector
TimingBasedAdversary::getPaths()
{
    m_globalPath = PathVector();

    Path path = Path();
    PathInfo info = PathInfo(m_sourceNode, m_endToEndDelay);
    path.push_back(info);

    return getPathsRecursive(path, m_endToEndDelay);
}

PathVector
TimingBasedAdversary::getPathsRecursive(Path currentPath, uint32_t currentTime)
{
    bool samePath = false;

    if ((int) currentPath.size() < m_maxNodes && (int) m_globalPath.size() < m_maxPaths)
    {
        nodeid source = currentPath[currentPath.size() - 1].first; // Last node in path
        uint32_t sourceTime = currentPath[currentPath.size() - 1].second;
        NeighborsVector availableNeighbors = getAvailableNeighbors(m_nodes[source]);

        for (size_t  i = 0; i < availableNeighbors.size(); ++i)
        {
             std::shared_ptr<Neighbor> neighbor = availableNeighbors[i];
             Path oldPath = currentPath;
             int32_t time = ( currentTime < m_transmissionTime) ? 0 : currentTime - m_transmissionTime;
             if (m_dynamicGraph)
             {
                // Source activation time is higher than neighbor activation skip this path
                if (sourceTime < neighbor->getActivationTime())
                    continue;
                // In other cases use neighbour activation time
                time = std::min(currentTime - m_transmissionTime, neighbor->getActivationTime());
             }

             PathInfo info = PathInfo(neighbor->getId(), time);
             if(m_noCycles && nodeInPath(currentPath, neighbor->getId()))
             {
               continue;
             }                      
             currentPath.push_back(info);
             samePath = equalPathOfNodesInPathVector(m_globalPath, currentPath);

             if (!time && !samePath)
             {  
                 if ( !m_ofSize || ( m_ofSize && (currentPath.size() == (uint32_t) m_maxNodes)))
                                m_globalPath.push_back(currentPath);
             }
             else
             {
                 if ( ((!m_ofSize) || ( m_ofSize && (currentPath.size() == (uint32_t) m_maxNodes)))
                         && (m_ofMaxTime))
                      m_globalPath.push_back(currentPath);

                 getPathsRecursive(currentPath, time);
             }
             currentPath = oldPath;
        }
    }
    return m_globalPath;
}
