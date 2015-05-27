/*
 * Neighbor.h
 *
 *  Created on: 26 May 2015
 *      Author: Adrian Antunez
 */

#ifndef NEIGHBOR_H_
#define NEIGHBOR_H_

//#include "types.h"
#include <stdint.h>
#include <map>
#include <vector>
#include <ostream>
#include <iostream>


class Neighbor;

typedef uint32_t nodeid;
typedef std::vector<Neighbor*> NeighborsVector;
typedef std::map<uint32_t, NeighborsVector> Contacts;
typedef std::map<nodeid, Contacts> Nodes;

template < class T >
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

class Neighbor {
public:
	Neighbor();
	Neighbor(nodeid hostId, nodeid id, uint32_t activationTime, uint32_t duration);
	virtual ~Neighbor();

	void setHostId (nodeid hostId) {m_hostId = hostId;}
	void setId (nodeid id) {m_id = id;}
	void setActivationTime (uint32_t activationTime) {m_activationTime = activationTime;}
	void setDuration (uint32_t duration) {m_duration = duration;}

	nodeid getHostId () {return m_hostId;}
	nodeid getId () {return m_id;}
	uint32_t getActivationTime () {return m_activationTime;}
	uint32_t getDuration () {return m_duration;}

	std::ostream& operator<<(std::ostream& os);
private:
	nodeid m_hostId;
	nodeid m_id;
	uint32_t m_activationTime;
	uint32_t m_duration;
};

#endif /* NEIGHBOR_H_ */
