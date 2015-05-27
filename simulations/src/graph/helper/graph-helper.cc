/*
 * graph.cc
 *
 *  Created on: Mar 3, 2014
 *      Author: Adrian Antunez <adriananve@gmail.com>
 */

#include "graph-helper.h"
//#include "vertex.h"

#include "ns3/simulator.h"
#include "ns3/trace-helper.h"

namespace ns3 {

GraphHelper* GraphHelper::m_instance = 0;

NS_LOG_COMPONENT_DEFINE ("GraphHelper");
	GraphHelper* GraphHelper::Get()
	{
		if (m_instance == 0)
		{
			m_instance = new GraphHelper();
		}
		return m_instance;
	}

	GraphHelper::GraphHelper ()
	{
		m_graph = new Graph();
		m_endSimulationTime = 0;
		m_numNodes = 0;
		m_relativePath = "./data/graphs/";
		m_filename = "default-graph";
	}

	GraphHelper::~GraphHelper ()
	{
		delete m_graph;
	}

	void GraphHelper::addVertex (uint32_t nodeId)
	{
		m_graph->addVertex(nodeId);
	}

	void GraphHelper::addContact (uint32_t origNode, uint32_t destNode, double activationTime, double duration)
	{
		Vertex::Attributes attrs;
		attrs.activationTime = activationTime;
		attrs.duration = duration;
		m_graph->addEdgeByLabel(attrs, origNode, destNode);
	}

	void GraphHelper::addEdgeByLabel (Vertex::Attributes attrs, uint32_t origNode, uint32_t destNode)
	{
		m_graph->addEdgeByLabel(attrs, origNode, destNode);
	}

	void GraphHelper::setEndSimulationTime (double endSimulation)
	{
		m_endSimulationTime = endSimulation;
	}

	void GraphHelper::setNumNodes (uint32_t numNodes)
	{
		m_numNodes = numNodes;
	}

	void GraphHelper::setRelativePath (std::string relPath)
	{
		m_relativePath = "./" + relPath;
	}

	void GraphHelper::setFileName (std::string filename)
	{
		if (filename.length() > 0)
		{
			m_filename = filename;
		}
	}

	void GraphHelper::exportToFile ()
	{
		getVectorOfVertices ();		//Get vector of vertices only one time and use it to export Vertices and Edges

		if (m_vertices.size() > 0)
		{
			std::stringstream ss;
			ss <<  m_relativePath << m_filename << "-" << m_endSimulationTime << "h-" << m_numNodes << "n" << EXTENSION; //complete filename
			AsciiTraceHelper ascii;
			Ptr<OutputStreamWrapper> filestr = ascii.CreateFileStream (ss.str(),std::ios_base::app);
			if (filestr == 0)
			{
				return;
			}
			printSimple(filestr);
			printHeader (filestr);
			printAttributes (filestr);
			printVertices (filestr);
			printEdges (filestr);
			printEndHeader (filestr);
		}
	}

	void GraphHelper::printSimple(Ptr<OutputStreamWrapper> filestr)
	{
		*filestr->GetStream() << "# hostId:neighborId:activationTime:duration" << std::endl;
		for (int i = 0; i < (int) m_vertices.size(); ++i)
		{
			Vertex::Neighbors neighbors = m_vertices[i]->getNeighbors();
			for (int j = 0; j < (int) neighbors.size(); ++j)
			{
				Vertex::Attributes attrs = neighbors[j].first;
				int label = neighbors[j].second->getLabel();
				*filestr->GetStream() << m_vertices[i]->getLabel() << ":" << label << ":" << attrs.activationTime << ":" << attrs.duration << std::endl;
			}
		}

	}

	void GraphHelper::printHeader (Ptr<OutputStreamWrapper> filestr)
	{
//		//Print the default header for *.gexf extension files
//		*filestr->GetStream() << "<gexf xmlns=\"http://www.gexf.net/1.2draft\"" << std::endl;
//		*filestr->GetStream() << "xmlns:viz=\"http://www.gexf.net/1.2draft/viz\"" << std::endl;
//		*filestr->GetStream() << "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" version=\"1.2\"" << std::endl;
//		*filestr->GetStream() << "xsi:schemaLocation=\"http://www.gexf.net/1.2draft http://www.gexf.net/1.2draft/gexf.xsd\">" << std::endl;
//		*filestr->GetStream() << "<meta lastmodifieddate=\"2014-03-02\"><creator>GraphHelper</creator><description/></meta>" << std::endl;
//		*filestr->GetStream() << "<graph defaultedgetype=\"undirected\" timeformat=\"double\" mode=\"dynamic\">" << std::endl;
	}

	void GraphHelper::printAttributes(Ptr<OutputStreamWrapper> filestr)
	{
//		//Print required attributes for a given node
//		*filestr->GetStream() << "<attributes class=\"node\" mode=\"static\">" << std::endl;
//		*filestr->GetStream() << "<attribute id=\"FlightCodeId\" title=\"FlightCodeId\" type=\"integer\"></attribute>" << std::endl;
//		*filestr->GetStream() << "<attribute id=\"FlightCodeIata\" title=\"FlightCodeIata\" type=\"string\"></attribute>" << std::endl;
//		*filestr->GetStream() << "<attribute id=\"Airline\" title=\"Airline\" type=\"string\"></attribute>" << std::endl;
//		*filestr->GetStream() << "<attribute id=\"Route\" title=\"Route\" type=\"string\"></attribute>" << std::endl;
//
//		*filestr->GetStream() << "<attribute id=\"Direction\" title=\"Direction\" type=\"boolean\"></attribute>" << std::endl;
//		*filestr->GetStream() << "<attribute id=\"aSource\" title=\"aSource\" type=\"string\"></attribute>" << std::endl;
//		*filestr->GetStream() << "<attribute id=\"aDestination\" title=\"aDestination\" type=\"string\"></attribute>" << std::endl;
//		*filestr->GetStream() << "<attribute id=\"CoordSource\" title=\"CoordSource\" type=\"string\"></attribute>" << std::endl;
//		*filestr->GetStream() << "<attribute id=\"CoordDest\" title=\"CoordDest\" type=\"string\"></attribute>" << std::endl;
//		*filestr->GetStream() << "<attribute id=\"Altitude\" title=\"Altitude\" type=\"double\"></attribute>" << std::endl;
//		*filestr->GetStream() << "<attribute id=\"PrioThres\" title=\"PrioThres\" type=\"double\"></attribute>" << std::endl;
//		*filestr->GetStream() << "</attributes>" << std::endl;
//		//Print required attributes for a given edge (contactTime and currentTime)
//		*filestr->GetStream() << "<attributes class=\"edge\" mode=\"static\">" << std::endl;
//		*filestr->GetStream() << "<attribute id=\"Longitude\" title=\"Longitude\" type=\"double\"></attribute>" << std::endl;
//		*filestr->GetStream() << "<attribute id=\"Latitude\" title=\"Latitude\" type=\"double\"></attribute>" << std::endl;
//		*filestr->GetStream() << "<attribute id=\"NodeFciS\" title=\"NodeFciS\" type=\"string\"></attribute>" << std::endl;
//		*filestr->GetStream() << "<attribute id=\"NodeFciD\" title=\"NodeFciD\" type=\"string\"></attribute>" << std::endl;
//		*filestr->GetStream() << "<attribute id=\"ContactTime(s)\" title=\"ContactTime(s)\" type=\"double\"></attribute>" << std::endl;
//		*filestr->GetStream() << "<attribute id=\"CurrentTime(s)\" title=\"CurrentTime(s)\" type=\"double\"></attribute>" << std::endl;
//		*filestr->GetStream() << "<attribute id=\"CurrentTime(h)\" title=\"CurrentTime(h)\" type=\"double\"></attribute>" << std::endl;
//		*filestr->GetStream() << "<attribute id=\"PrioContact\" title=\"PrioContact\" type=\"boolean\"></attribute>" << std::endl;
//		*filestr->GetStream() << "</attributes>" << std::endl;
	}

	void GraphHelper::printVertices (Ptr<OutputStreamWrapper> filestr)
	{
//		*filestr->GetStream() << "<nodes>" << std::endl;
//		for (int i = 0; i < (int) m_vertices.size(); ++i)
//		{
//			printSingleVertex(filestr, m_vertices[i]);
//		}
//		*filestr->GetStream() << "</nodes>" << std::endl;
	}

	void GraphHelper::printSingleVertex(Ptr<OutputStreamWrapper> filestr, Vertex *vertex)
	{
//		//gexf file format needs the boolean expressions as strings, not as 0 or 1.
//		std::string directionString = vertex->getDirection() ? "true" : "false";
//		*filestr->GetStream() << "<node id=\"" << vertex->getVertexId() << "\" label=\"" << vertex->getLabel().first << "-" << vertex->getLabel().second << "\">" << std::endl;
//		*filestr->GetStream() << "<attvalues>" << std::endl;
//		*filestr->GetStream() << "<attvalue for=\"FlightCodeId\" value=\"" << vertex->getFlightCodeIdentifier().first << "\"></attvalue>" << std::endl;
//		*filestr->GetStream() << "<attvalue for=\"FlightCodeIata\" value=\"" << vertex->getFlightCodeIdentifier().second << "\"></attvalue>" << std::endl;
//		*filestr->GetStream() << "<attvalue for=\"Airline\" value=\"" << vertex->getAirline() << "\"></attvalue>" << std::endl;
//		*filestr->GetStream() << "<attvalue for=\"Route\" value=\"" << vertex->getRoute() << "\"></attvalue>" << std::endl;
//		*filestr->GetStream() << "<attvalue for=\"Direction\" value=\"" << directionString << "\"></attvalue>" << std::endl;
//		*filestr->GetStream() << "<attvalue for=\"aSource\" value=\"" << vertex->getSource() << "\"></attvalue>" << std::endl;
//		*filestr->GetStream() << "<attvalue for=\"aDestination\" value=\"" << vertex->getDestination() << "\"></attvalue>" << std::endl;
//		*filestr->GetStream() << "<attvalue for=\"CoordSource\" value=\"" << vertex->getCoordSource() << "\"></attvalue>" << std::endl;
//		*filestr->GetStream() << "<attvalue for=\"CoordDest\" value=\"" << vertex->getCoordDest() << "\"></attvalue>" << std::endl;
//		*filestr->GetStream() << "<attvalue for=\"Altitude\" value=\"" << vertex->getAltitude() << "\"></attvalue>" << std::endl;
//		*filestr->GetStream() << "<attvalue for=\"PrioThres\" value=\"" << vertex->getPrioThreshold() << "\"></attvalue>" << std::endl;
//		*filestr->GetStream() << "</attvalues>" << std::endl;
////		Adrian TODO: After fix start and end issue, uncoment these lines
////		*filestr->GetStream() << "<spells>" << std::endl;
////		*filestr->GetStream() << "<spell start=\"" << vertex->getStart() << "\" end=\"" << vertex->getEnd() << ">" << std::endl;
////		*filestr->GetStream() << "</spells>" << std::endl;
//		*filestr->GetStream() << "</node>" << std::endl;
	}

	void GraphHelper::printEdges(Ptr<OutputStreamWrapper> filestr)
	{
//		*filestr->GetStream() << "<edges>" << std::endl;
//		//For each node, get his neigbors and print (export) them to a file
//		for (int i = 0; i < (int) m_vertices.size(); ++i)
//		{
//			Vertex *v = m_vertices[i];
//			m_edges = v->getNeighbors();
//			for (int j = 0; j < (int) m_edges.size(); ++j)
//			{
//				printSingleEdge(filestr, v, m_edges[j]);
//			}
//		}
//		*filestr->GetStream() << "</edges>" << std::endl;
	}

	void GraphHelper::printSingleEdge(Ptr<OutputStreamWrapper> filestr, Vertex *vertex, Vertex::Edge edge)
	{
//		Vertex::Attributes attr = edge.first;
//		//gexf file format needs the boolean expresions as strings, not as 0 or 1.
//		std::string prioContactString = attr.prioContact ? "true" : "false";
//
//		*filestr->GetStream() << "<edge source=\"" << vertex->getVertexId() << "\" target=\"" << edge.second->getVertexId() << "\" label=\"" << vertex->getVertexId() << "-" << edge.second->getVertexId() << "\">" << std::endl;
//		*filestr->GetStream() << "<attvalues>" << std::endl;
//		*filestr->GetStream() << "<attvalue for=\"Longitude\" value=\"" << attr.longitude << "\"></attvalue>" << std::endl;
//		*filestr->GetStream() << "<attvalue for=\"Latitude\" value=\"" << attr.latitude << "\"></attvalue>" << std::endl;
//
//		*filestr->GetStream() << "<attvalue for=\"NodeFciS\" value=\"" << vertex->getFlightCodeIdentifier().first<<"-"<<vertex->getFlightCodeIdentifier().second << "\"></attvalue>" << std::endl;
//		*filestr->GetStream() << "<attvalue for=\"NodeFciD\" value=\"" << edge.second->getFlightCodeIdentifier().first<<"-"<<edge.second->getFlightCodeIdentifier().second << "\"></attvalue>" << std::endl;
//		*filestr->GetStream() << "<attvalue for=\"CurrentTime(s)\" value=\"" << attr.currentTime << "\"></attvalue>" << std::endl;
//		*filestr->GetStream() << "<attvalue for=\"CurrentTime(h)\" value=\"" << attr.currentTime/3600 << "\"></attvalue>" << std::endl;
//		*filestr->GetStream() << "<attvalue for=\"ContactTime(s)\" value=\"" << attr.contactTime << "\"></attvalue>" << std::endl;
//		*filestr->GetStream() << "<attvalue for=\"PrioContact\" value=\"" << prioContactString << "\"></attvalue>" << std::endl;
//
//		*filestr->GetStream() << "</attvalues>" << std::endl;
//		*filestr->GetStream() << "</edge>" << std::endl;
	}

	void GraphHelper::printEndHeader (Ptr<OutputStreamWrapper> filestr)
	{
//		*filestr->GetStream() << "</graph>" << std::endl;
//		*filestr->GetStream() << "</gexf>" << std::endl;
	}

	void GraphHelper::getVectorOfVertices ()
	{
		Graph::Vertices verts = m_graph->getVertices();
		//Reserve enough space to save the number of given vertices
		m_vertices.reserve(verts.size());
		m_vertices.clear();
		//Get each Vertex and append it to vector of vertex
		Graph::Vertices::iterator it;
		for (it = verts.begin() ;it != verts.end(); ++it)
		{
			m_vertices.push_back(it->second);
		}
	}
}
