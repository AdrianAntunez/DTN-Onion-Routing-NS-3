/**
 * @copyright
 * Copyright (C) 2015 Universitat Autònoma de Barcelona
 * Department of Information and Communications Engineering
 * @file neighbor.h
 * @author Adrian Antunez
 * @date Created on:  26/5/2015
 */


#ifndef NEIGHBOR_H_
#define NEIGHBOR_H_

//#include "types.h"
#include <stdint.h>
#include <map>
#include <vector>
#include <ostream>
#include <iostream>
#include <memory>

class Neighbor;

/**
 * @brief Defines a type identificator for nodes
 *
 */
typedef uint32_t nodeid;
/**
 * @brief Defines a type describing node activation time
 *
 */
typedef uint32_t activationtime;
/**
 * @brief Defines an array of neighbors type
 *
 */
typedef std::vector<std::shared_ptr<Neighbor>> NeighborsVector;
/**
 * @brief Maps activation times to Neighbors
 *
 */
typedef std::map<activationtime, NeighborsVector> Contacts;
/**
 * @brief Maps node id with the list of neighbours mapped according to activation times.
 *
 */
typedef std::map<nodeid, Contacts> Nodes;

template < class T >
/**
 * @brief output operator overload
 *
 * @param os
 * @param v
 * @return std::ostream &operator
 */
std::ostream& operator << (std::ostream& os, const std::vector<T>& v)
{
    os << "[";
    for (typename std::vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        os << " " << *ii;
    }
    os << "]";
    return os;
}

/**
 * @brief Defines the basic relationship between a node and one of its neighbors in the graph.
 *
 */
class Neighbor {
public:
    /**
     * @brief Default Constructor
     */
	Neighbor();
    /**
     * @brief Parametized Constructor
     *
     * @param hostId: id of the current node.
     * @param id: id of the neighbor node.
     * @param activationTime: time at which the neighbor becomes available (i.e the contact is produced or it becomes a neighbor)
     * @param duration: duration of the contact (i.e how long it stays as a neighbor or how long the contact lasts).
     */
    Neighbor(nodeid hostId, nodeid id, uint32_t activationTime, uint32_t duration);
    /**
     * @brief Default destructor
     *
     */
    virtual ~Neighbor();

    /**
     * @brief Id of the current node setter method.
     *
     * @param node id to assign.
     */
    void setHostId (nodeid hostId) {m_hostId = hostId;}
    /**
     * @brief Id of the neighbor node setter method.
     *
     * @param node id to assign.
     */
    void setId (nodeid id) {m_id = id;}
    /**
     * @brief Activation time setter method.
     *
     * @param activationTime to assign.
     */
    void setActivationTime (uint32_t activationTime) {m_activationTime = activationTime;}
    /**
     * @brief Duration time setter method.
     *
     * @param duration time to assign.
     */
    void setDuration (uint32_t duration) {m_duration = duration;}

    /**
     * @brief Node Id getter method.
     *
     * @return nodeid of the current node.
     */
    nodeid getHostId () {return m_hostId;}
    /**
     * @brief Neighbor id getter method.
     *
     * @return nodeid of the neighbor node.
     */
    nodeid getId () {return m_id;}
    /**
     * @brief Activation time getter method
     *
     * @return activation time of the neighbor
     */
    uint32_t getActivationTime () {return m_activationTime;}
    /**
     * @brief Duration time getter method
     *
     * @return duration of the contact
     */
    uint32_t getDuration () {return m_duration;}

    /**
     * @brief output operator
     *
     * @param os
     * @return std::ostream &operator
     */
    std::ostream& operator<<(std::ostream& os);
private:
    /**
     * @brief m_hostId id of the current node
     */
    nodeid m_hostId;
    /**
     * @brief m_id id of the neighbor node
     */
    nodeid m_id;
    /**
     * @brief m_activationTime time at which the neighbor becomes available (i.e the contact is produced or it becomes a neighbor)
     */
    uint32_t m_activationTime;
    /**
     * @brief m_duration duration of the contact (i.e how long it stays as a neighbor or how long the contact lasts).
     */
    uint32_t m_duration;
};

#endif /* NEIGHBOR_H_ */
