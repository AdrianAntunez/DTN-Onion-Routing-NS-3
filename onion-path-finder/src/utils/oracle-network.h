/**
 * @copyright
 * Copyright (C) 2016 Universitat Autònoma de Barcelona
 * Department of Information and Communications Engineering
 * @file oracle-network.h
 * @author Adrian Antunez
 * @date Created on: 26 May 2015
 */

#ifndef ORACLENETWORK_H_
#define ORACLENETWORK_H_

#include "graph-util.h"

/**
 * @brief The OracleNetwork class Implements the exploration methods used by a communication source to find multiple possible paths to destination according
 * to characteristics given as parameters.
 */
class OracleNetwork : public GraphUtil {

public:
    /**
     * @brief Default Constructor.
     */
	OracleNetwork();
    /**
     * @brief Parametized Constructor.
     * @param nodes: Graph representation.
     */
    OracleNetwork(Nodes nodes, nodeid source, nodeid destination, uint32_t startTime, uint32_t numPaths, uint32_t numNodes, uint32_t transmissionTime, bool noCycles);
    /**
     * @brief Destructor
     */
    virtual ~OracleNetwork();

    /**
     * @brief getPaths: iteraritve search of multiple paths meeting specified conditions given by parameters.
     *
     * @param source: source node.
     * @param destination: destination node.
     * @param time: starting time.
     * @param numPaths: number of paths to return.
     * @param numNodes: number of nodes per path (path length).
     * @param transmissionTime: time spent
     * @return PathVector
     */
    virtual PathVector getPaths();

private:

    /**
     * @brief getPathsRecursive: Recursively explore paths increasing time at each hop
     * @param currentPath: explored nodes up to this point.
     * @param time: time left for path exploration.
     * @return array with explored paths meeting conditions.
     */
    virtual PathVector getPathsRecursive(Path currentPath, uint32_t time);

    /**
     * @brief m_targetNode
     */
    nodeid m_targetNode;
    /**
     * @brief m_startingTime
     */
    uint32_t m_startingTime;




};

#endif /* ORACLENETWORK_H_ */
