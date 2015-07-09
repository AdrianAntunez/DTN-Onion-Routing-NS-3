/*
 * graph.cc
 *
 *  Created on: Mar 2, 2014
 *      Author: Adrian Antunez <adriananve@gmail.com>
 */

#include "graph.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("Graph");

	Graph::Graph () :
		m_vertices(),
		m_vertexIdCount(0)
	{
	}

	Graph::~Graph()
	{
		//Each vertex pointer must be deleted
		NS_LOG_DEBUG("Deleting graph object..." << "m_vertices size: " << m_vertices.size());
		for (Vertices::iterator it = m_vertices.begin(); it != m_vertices.end(); ++it)
		{
			delete (*it).second;
		}
	}

	/*
	 * Will be used to add a new vertex to the graph
	 * If the given label doesn't exists, create a new vertex, otherwise do nothing
	 * We will avoid to raise  an error in order to be sure that the vertex will exist after this funtion call
	 */
	void Graph::addVertex(uint32_t nodeId)
	{
		Vertices::iterator it = m_vertices.find(nodeId);
		if (it == m_vertices.end()) //If iterator has been reached the end of the vertices map, it hasn't been found
		{
			Vertex *v = new Vertex(m_vertexIdCount, nodeId);
			m_vertices[nodeId]=v;
			m_vertexIdCount++;
		}
	}

	void Graph::addEdgeByLabel (Vertex::Attributes attrs,  uint32_t origNode, uint32_t destNode)
	{
		Vertex *originV = NULL;
		Vertex *destinationV = NULL;
		Vertices::iterator it = m_vertices.find(origNode);
		if ( it != m_vertices.end())
		{
			originV = it->second;
		}
		else
		{
			addVertex(origNode);

		}
		it = m_vertices.find(destNode);
		if (it != m_vertices.end())
		{
			destinationV = it->second;
		}
		else
		{
			addVertex(destNode);
		}

		Vertex::Edge edge = std::make_pair (attrs, m_vertices[destNode]);
		m_vertices[origNode]->addNeighbor(edge);
	}
}

