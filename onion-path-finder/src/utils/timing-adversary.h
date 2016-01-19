/**
 * @copyright
 * Copyright (C) 2016 Universitat Autònoma de Barcelona
 * Department of Information and Communications Engineering
 * @file timing-adversary.h
 * @author Rubén Martínez <rmartinez@deic.uab.cat>
 * @date Created on: 21/12/2015
 */

#ifndef TIMING_ADVERSARY_H_
#define TIMING_ADVERSARY_H_

#include "graph/neighbor.h"
#include "graph-util.h"

/**
 * @brief The TimingBasedAdversary class implements the exploration methods used by an adversary trying to guess the source of a communication using only message timing information.
 *
 * The adversary knows limited information:
 * - end-to-end time: end-to-end communication time between source and destination (reception time - start of transmission).
 *
 * The adversary makes the following assumptions:
 * - no cyles.
 * - dynamic graph activation time of the previous node in path must be smaller than current one.
 * - return paths of fixed size.
 * - return paths of max time or less.
 * \todo 2. Pending feature: asume that nodes allways forward data to the first contact.
 * \todo 1. Optimization : remove endToendTime and use startingTime.
 */
class TimingBasedAdversary : public GraphUtil {
public:
    /**
     * @brief Adversary default Constructor
     */
    TimingBasedAdversary();
    /**
     * @brief Adversary parametized Constructors
     * @param nodes Graph representation
     * @param noCycles: flag, false to allow repeated nodes in path.
     * @param dynamic: flag, true if activation time of nodes is considered when choosing paths.
     */
    TimingBasedAdversary(Nodes nodes, nodeid adversary, uint32_t numPaths, uint32_t numNodes, uint32_t transmissionTime, uint32_t endToEndDelay, bool noCycles, bool dynamic, bool ofSize, bool maxTime);

    /**
     * @brief Default destructor
     */
    virtual ~TimingBasedAdversary();
	
    /**
     * @brief getPaths: iteraritve search of all paths meeting specified conditions : start point and time.
     * @param adversary: NodeId of the attacker node, starting point for path exploration.
     * @param totalTime: Search for paths with the specified transmission time.
     * @return array with all explored paths meeting conditions.
     */
    virtual PathVector getPaths();

private:
    /**
     * @brief getPathsRecursive: Recursively explore paths in reverse order substracting time
     * @param currentPath: explored nodes up to this point.
     * @param time: time left for path exploration.
     * @return array with explored paths meeting conditions.
     */
    virtual PathVector getPathsRecursive(Path currentPath, uint32_t time);

    /**
     * @brief m_endToEndDelay: time required from source to reach destination.
     */
    uint32_t m_endToEndDelay;
    /**
     * @brief noCycles: flag, true if activation time of nodes is considered when choosing paths.
     */
    bool m_dynamicGraph;
    /**
     * @brief m_ofSize: flag, true if m_numNodes specifies the desired length of path, otherwise specifies maximum allowed length.
     */
    bool m_ofSize;

    /**
     * @brief m_ofMaxTime: flag, true if m_endToEndDelay specifies maximum time, return all paths smaller than provided time.
     */
    bool m_ofMaxTime;

};

#endif /* TIMING_ADVERSARY_H_ */
