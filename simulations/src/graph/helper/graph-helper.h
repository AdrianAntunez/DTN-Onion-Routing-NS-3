/*
 * graph.cc
 *
 *  Created on: Mar 3, 2014
 *      Author: Adrian Antunez <adriananve@gmail.com>
 */

#ifndef GRAPH_HELPER_H
#define GRAPH_HELPER_H

#include "ns3/graph.h"
#include "ns3/output-stream-wrapper.h"
#include "ns3/log.h"

namespace ns3 {

const std::string EXTENSION = ".xml";

class GraphHelper
{
	public:
		static GraphHelper* Get();

		~GraphHelper ();
		void Start();

		void createGraph ();
		void exportToFile ();	//Export the final graph

		void addVertex (uint32_t label);
		void addContact (uint32_t hostId, uint32_t neighborId, double activationTime, double duration);
		void addEdgeByLabel (Vertex::Attributes attrs,  uint32_t origLabel, uint32_t destLabel);

		void setEndSimulationTime(double endSimulation);
		void setNumNodes (uint32_t numNodes);
		void setFileName (std::string filename);
		void setRelativePath (std::string relPath);	//Set the relative path to export the graph

	private:
		GraphHelper ();
		GraphHelper (double endSimulation, uint32_t numNodes);


		void getVectorOfVertices ();	///Will

		void printSimple (Ptr<OutputStreamWrapper> filestr);
		void printHeader (Ptr<OutputStreamWrapper> filestr);
		void printVertices (Ptr<OutputStreamWrapper> filestr);
		void printSingleVertex (Ptr<OutputStreamWrapper> filestr, Vertex *vertex);
		void printEdges (Ptr<OutputStreamWrapper> filestr);
		void printSingleEdge (Ptr<OutputStreamWrapper> filestr, Vertex *vertex, Vertex::Edge edge);
		void printEndHeader (Ptr<OutputStreamWrapper> filestr);
		void printAttributes (Ptr<OutputStreamWrapper> filestr);

		Graph *m_graph;
		double m_endSimulationTime;
		uint32_t m_numNodes;
		std::string m_relativePath;
		std::string m_filename;
		std::vector<Vertex*> m_vertices;
		std::vector<Vertex::Edge> m_edges;

		static GraphHelper* m_instance;
};

}

#endif /* GRAPH_HELPER_H */

