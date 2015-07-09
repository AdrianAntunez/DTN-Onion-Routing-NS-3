/*
 * vertex.h
 *
 *  Created on: Mar 4, 2014
 *      Author: Adrian Antunez <adriananve@gmail.com>
 */

#ifndef VERTEX_H_
#define VERTEX_H_

#include <map>
#include <iostream>
#include <vector>

#include <ns3/uinteger.h>
#include "ns3/object-factory.h"

namespace ns3 {
	class Vertex : public Object
	{
		public:
			struct Attributes {
				double activationTime;
				double duration;

			};
			typedef std::pair <Attributes, Vertex *> Edge;	//attributes of the edge and destination vertex
			typedef std::vector <Edge> Neighbors;

			Vertex (int vertexId, uint32_t nodeId);
			~Vertex();

			void addNeighbor(Edge edge);

			int getVertexId() {return m_vertexId;}
			int getLabel() {return m_label;}
			Neighbors getNeighbors() {return m_neighbors;}
		private:
			int m_vertexId;	 //Id of the current vertex (starting at 0 to Inf)
			uint32_t m_label; //The label of the vertex will be the Id of the node that has been involved in a contact
			Neighbors m_neighbors;	//List of neighbours (adjacence list representation)
};

} //namespace ns3

#endif /* VERTEX_H_ */
