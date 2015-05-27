/*
 * vertex.cc
 *
 *  Created on: Mar 4, 2014
 *      Author: Adrian Antunez <adriananve@gmail.com>
 */

#include "vertex.h"
#include "ns3/node.h"
#include "ns3/node-list.h"
#include <algorithm>

namespace ns3 {

	Vertex::Vertex (int vertexId, uint32_t nodeId)
	{
		m_vertexId = vertexId;
		m_label = nodeId;
	}

	Vertex::~Vertex()
	{
	}

	void Vertex::addNeighbor(Edge edge)
	{
		m_neighbors.push_back(edge);
	}
} //namespace ns3
