/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2015 Autonomous University of Barcelona
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Adrian Antunez <adrian.antunez@deic.uab.cat>
 */

#ifndef NEIGHBOR_DISCOVERY_H
#define NEIGHBOR_DISCOVERY_H

#include "ns3/application.h"
#include "ns3/ptr.h"
#include "ns3/event-id.h"
#include "ns3/traced-callback.h"
#include "ns3/vector.h"
#include "ns3/timer.h"
#include "neighbor-state.h"


#include <map>
#include <iostream>
#include <deque>

namespace ns3 {

class Address;
class Socket;

class NeighborDiscovery : public Application
{
public:
	/**
	 * \brief Get the type ID.
	 * \return the object TypeId
	 */
	static TypeId GetTypeId (void);

	NeighborDiscovery ();

	virtual ~NeighborDiscovery ();

	typedef uint32_t nodeid;
	  std::map<nodeid,Ptr<NeighborState> > Neighbours;

	void NeighborStatusHandler(NeighborReportCode, double, double);

protected:
	virtual void DoDispose (void);
private:
	// inherited from Application base class.
	virtual void StartApplication (void);    // Called at time specified by Start
	virtual void StopApplication (void);     // Called at time specified by Stop

	void HandleRead (Ptr<Socket> socket);
	void Send (void);
	void ReportNewContact(nodeid nid, nodeid neighbor);
	void ReportLostContact(nodeid neighborId, Time activationTime);

	/* Socket stuff */

	Ptr<Socket>     m_listening_socket;                             // Listening socket
	Ptr<Socket>     m_sender_socket;                                // Sender socket
	Address         m_local;                                      // Local address to bind to
	Address         m_remote;                                     // Remote address to send packets to
	uint16_t        m_port;                                       // Listener port


	/* Beaconing stuff */
	Time            m_interval;                                    // Time between packets
	Time            m_expirationTime;                              // How long a neighbor is considered active
	EventId         m_sendEvent;                                   // Sender event


};

} // namespace ns3

#endif /* NEIGHBOR_DISCOVERY_H */
