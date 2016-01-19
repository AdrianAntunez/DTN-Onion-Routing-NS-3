/**
 * @copyright
 * Copyright (C) 2016 Universitat Autònoma de Barcelona
 * Department of Information and Communications Engineering
 * @file graph-util.cpp
 * @author Rubén Martínez <rmartinez@deic.uab.cat>
 * @date Created on:  6/1/2016
 */

#include "graph-util.h"

GraphUtil::GraphUtil():
    m_nodes(),
    m_sourceNode(0),
    m_maxPaths(0),
    m_maxNodes(0),
    m_transmissionTime(0),
    m_noCycles(false),
    m_globalPath()
{
}

GraphUtil::GraphUtil(Nodes nodes) :
        m_nodes(nodes),
        m_sourceNode(0),
        m_maxPaths(10),
        m_maxNodes(10),
        m_transmissionTime(1),
        m_noCycles(false),
        m_globalPath()
{}

GraphUtil::GraphUtil(Nodes nodes, nodeid source, int numPaths, int numNodes, uint32_t time, bool noCycles):
    m_nodes(nodes),
    m_sourceNode(source),
    m_maxPaths(numPaths),
    m_maxNodes(numNodes),
    m_transmissionTime(time),
    m_noCycles(noCycles),
    m_globalPath()
{

}
GraphUtil::~GraphUtil()
{
}
bool
GraphUtil::equalPathOfNodesInPathVector (PathVector pv, Path p)
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
GraphUtil::pathEqualNodes (Path p1, Path p2)
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

bool
GraphUtil::nodeInPath(Path p, nodeid id)
{
    for (size_t i = 0; i < p.size(); ++i)
    {
        if (p[i].first == id)
        {
            return true;
        }
    }
    return false;
}


void
GraphUtil::printPaths (PathVector pv)
{
    for (size_t i = 0; i < pv.size(); ++i)
    {
        std::cout << "Path: " << i << std::endl;
        printPath(pv[i]);
    }
    std::cout << std::endl << "(n, t): Means node n received the message at time t" << std::endl;
}

void
GraphUtil::printPath (Path path)
{
    for (size_t j = 0; j < path.size() - 1; ++j)
    {
        std::cout << "(" << path[j].first << ":" << path[j].second << "), ";
    }
    std::cout << "(" << path[path.size() - 1].first << ":" << path[path.size() - 1].second << ")" << std::endl;
}


NeighborsVector
GraphUtil::getAvailableNeighbors (Contacts contacts)
{
    NeighborsVector availableNeighbors = NeighborsVector();
    Contacts::iterator it = contacts.begin();
    while (it != contacts.end())
    {
        NeighborsVector nv = it->second;
        for (size_t i = 0; i < nv.size(); ++i)
        {
           availableNeighbors.push_back(nv[i]);
        }
        ++it;
    }
    return availableNeighbors;
}



NeighborsVector
GraphUtil::getAvailableNeighborsAtTime (Contacts contacts, uint32_t currentTime)
{
    NeighborsVector availableNeighbors = NeighborsVector();
    Contacts::iterator it = contacts.begin();
    while (it != contacts.end()) {
        NeighborsVector nv = it->second;
        for (size_t i = 0; i < nv.size(); ++i)
        {            
            uint32_t timeSum = nv[i]->getActivationTime() + nv[i]->getDuration();
            uint32_t compTime = (timeSum < m_transmissionTime) ? 0 : timeSum - m_transmissionTime;
            if ( compTime >= currentTime)
            {
                availableNeighbors.push_back(nv[i]);
            }
        }
        ++it;
    }
    return availableNeighbors;
}
