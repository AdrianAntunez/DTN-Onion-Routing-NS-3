/**
 * @copyright
 * Copyright (C) 2016 Universitat Autònoma de Barcelona
 * Department of Information and Communications Engineering
 * @file graph-util.h
 * @author Rubén Martínez <rmartinez@deic.uab.cat>
 * @date Created on:  6/1/2016
 */

#ifndef GRAPHUTIL_H
#define GRAPHUTIL_H

#include "graph/neighbor.h"

/**
 * @brief Defines information about a node of the path. Defined as an std::pair containing nodeId and node activation time.
 *
 */
typedef std::pair<nodeid, uint32_t> PathInfo;
/**
 * @brief Defines an std::vector of PathInfo
 *
 */
typedef std::vector<PathInfo> Path;
/**
 * @brief Defines an std::vector of Paths
 *
 */
typedef std::vector<Path> PathVector;

/**
 * @brief The GraphUtil class defines the basic interface for graph exploration tools.
 */
class GraphUtil
{
public:
    /**
     * @brief Default Constructor.
     *
     */
    GraphUtil();
    /**
     * @brief Parametized Constructor.
     *
     * @param Nodes: Graph representation
     */
    GraphUtil(Nodes);

    /**
     * @brief GraphUtil
     * @param destination
     * @param time
     * @param numPaths
     * @param numNodes
     * @param transmissionTime
     */
    GraphUtil(Nodes, nodeid destination, int numPaths, int numNodes, uint32_t transmissionTime, bool noCycles);
    /**
     * @brief Virtual Destructor.
     *
     */
    virtual ~GraphUtil();



    /**
     * @brief Check if given path already exists in path vector.
     *
     * @param pv: given path vector.
     * @param p: given path.
     * @return bool: true if path exists, false otherwise.
     */
    bool equalPathOfNodesInPathVector (PathVector pv, Path p);
    /**
     * @brief Check if two paths are equal (both in size and contained nodes)
     *
     * @param p1 first path
     * @param p2 second path
     * @return bool true if paths are equal, false otherwise
     */
    bool pathEqualNodes (Path p1, Path p2);
    /**
     * @brief Check wheter nodes is in path or not
     *
     * @param p given path
     * @param id given node id
     * @return bool return true if nodes is in path, false otherwise
     */
    bool nodeInPath(Path p, nodeid id);

    /**
     * @brief Print the list of nodes (in <nodeid, activationtime> form) of the given path.
     *
     * @param path to print.
     */
    void printPath (Path path);
     /**
     * @brief Print the list of nodes (in <nodeid, activationtime> form) of all paths found in vector.
     *
     * @param pv vector of paths to print.
     */
    void printPaths (PathVector pv);

    /**
     * @brief Extracts the neighbours of a given node from a contact list.
     *
     * @param contacts: List of contacts of the target node.
     * @return NeighborsVector: array of neighbors.
     */
    NeighborsVector getAvailableNeighbors (Contacts contacts);
    /**
     * @brief Extracts the neighbours of a given node at a given time from a contact list.
     *
     * @param contacts: List of contacts of the target node.
     * @param currentTime: Given time.
     * @return NeighborsVector: array of neighbors.
     */
    NeighborsVector getAvailableNeighborsAtTime (Contacts contacts, uint32_t currentTime);


    virtual PathVector getPaths() = 0;

protected:

    /**
     * @brief getPathsRecursive: recursive DFS exploration method.
     * @param currentPath: path being explored.
     * @param time: cumulative time taken during exploration.
     * @return array of all matching paths.
     */
    virtual PathVector getPathsRecursive(Path currentPath, uint32_t time) = 0;

    /**
     * @brief Adjacency list representation of the graph.
     */
    Nodes m_nodes;
    /**
     * @brief source of the search.
     */
    nodeid m_sourceNode;
    /**
     * @brief a memory safeguard that defines the maximum number of paths to explore.
     */
    uint32_t m_maxPaths;
    /**
     * @brief a memory safeguard that defines the maximum number of allowed nodes in a path.
     */
    uint32_t m_maxNodes;
    /**
     * @brief m_transmissionTime: transmission overhead in each hop.
     */
    uint32_t m_transmissionTime;
    /**
     * @brief noCycles: false to allow cycles in path (repeated nodes), true otherwise.
     */
    bool m_noCycles;
    /**
     * @brief m_globalPath: array of explored paths.
     */
    PathVector m_globalPath;
};

#endif // GRAPHUTIL_H
