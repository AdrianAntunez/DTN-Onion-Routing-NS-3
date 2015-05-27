/*
 * graph.h
 *
 *  Created on: Mar 2, 2014
 *      Author: Adrian Antunez <adriananve@gmail.com>
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <ns3/uinteger.h>
#include <ns3/log.h>
#include "vertex.h"


#include <map>
#include <iostream>
#include <vector>


namespace ns3 {

class Graph
{
	public:
		typedef std::map <uint32_t, Vertex*> Vertices; //Each vertex will have a label and a vertex object
		void addVertex (uint32_t nodeId);
		void addEdgeByLabel (Vertex::Attributes attrs,  uint32_t origNode, uint32_t destNode);
		Vertices getVertices() {return m_vertices;}

		Graph();
		~Graph();
	private:
		int m_vertexIdCount;
		Vertices m_vertices;
};

}

#endif /* GRAPH_H */

