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

#include "neighbor-discovery.h"

#include "ns3/trace-source-accessor.h"
#include "ns3/socket-factory.h"
#include "ns3/log.h"
#include "ns3/address.h"
#include "ns3/inet-socket-address.h"
#include "ns3/ipv4-address.h"
#include "ns3/ipv4.h"
#include "ns3/socket.h"
#include "ns3/packet.h"
#include "ns3/uinteger.h"
#include "ns3/simulator.h"
#include "ns3/config.h"
#include "ns3/random-variable-stream.h"

#include <iostream>
#include <math.h>
#include <map>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("NeighborDiscovery");

NS_OBJECT_ENSURE_REGISTERED (NeighborDiscovery);

TypeId
NeighborDiscovery::GetTypeId (void)
{
	static TypeId tid = TypeId ("ns3::NeighborDiscovery")
		.SetParent<Application> ()
		.AddConstructor<NeighborDiscovery> ()
		.AddAttribute ("ListenerPort",
			"Port on which we listen for incoming packets.",
			TypeId::ATTR_CONSTRUCT | TypeId::ATTR_SET | TypeId::ATTR_GET,
			UintegerValue (80),
			MakeUintegerAccessor (&NeighborDiscovery::m_port),
			MakeUintegerChecker<uint16_t> ())
		.AddAttribute ("Interval",
			"The time to wait between packets",
			TimeValue (Seconds (1.0)),
			MakeTimeAccessor (&NeighborDiscovery::m_interval),
			MakeTimeChecker ())
		.AddAttribute ("ExpirationTime", "Time a neighbor is considered valid",
			TimeValue (Seconds (100)),
			MakeTimeAccessor (&NeighborDiscovery::m_expirationTime),
			MakeTimeChecker ());

	return tid;
}


NeighborDiscovery::NeighborDiscovery ():
			m_listening_socket (0),
			m_sender_socket (0)
{

}

NeighborDiscovery::~NeighborDiscovery ()
{}

void
NeighborDiscovery::DoDispose (void)
{
	NS_LOG_FUNCTION (this);

	m_listening_socket = 0;
	m_sender_socket = 0;
	Application::DoDispose ();
}

// Application Methods
void NeighborDiscovery::StartApplication (void) // Called at time specified by Start
{
	NS_LOG_FUNCTION (this);
	TypeId tid = TypeId::LookupByName("ns3::UdpSocketFactory");

	// Create the socket if not already
	if (m_listening_socket == 0)
	{
		m_listening_socket = Socket::CreateSocket (GetNode(), tid);
		m_local = InetSocketAddress (GetNode ()->GetObject<Ipv4> ()->GetAddress (1,0).GetLocal (), m_port);
		m_listening_socket->Bind (m_local);
		m_listening_socket->SetRecvCallback (MakeCallback (&NeighborDiscovery::HandleRead, this));
	}

	if (m_sender_socket == 0)
	{
		m_sender_socket = Socket::CreateSocket (GetNode (), tid);
		m_remote = InetSocketAddress (Ipv4Address ("255.255.255.255"), m_port);
		m_sender_socket->SetAllowBroadcast (true);
		m_sender_socket->Connect (m_remote);
		m_sender_socket->SetRecvCallback (MakeNullCallback<void, Ptr<Socket> > ());
		m_sendEvent = Simulator::ScheduleNow (&NeighborDiscovery::Send, this);
	}
}

void NeighborDiscovery::StopApplication (void) // Called at time specified by Stop
{
	if (m_listening_socket)
	{
		m_listening_socket->Close();
		m_listening_socket->SetRecvCallback(MakeNullCallback<void, Ptr<Socket> > ());
	}

	if (m_sender_socket)
	{
		m_sender_socket->Close();
		m_sender_socket->SetRecvCallback(MakeNullCallback<void, Ptr<Socket> > ());
		Simulator::Cancel (m_sendEvent);
	}
}

void
NeighborDiscovery::Send (void)
{
	NS_ASSERT (m_sendEvent.IsExpired());

	uint8_t buffer[4];

	uint32_t id = GetNode ()->GetId ();

	buffer[3] = id >> 24;
	buffer[2] = id >> 16;
	buffer[1] = id >> 8;
	buffer[0] = id;

	Ptr<Packet> p = Create<Packet> (buffer,sizeof(uint32_t));

	if ((m_sender_socket->Send (p)) >= 0)
	{
	  Ptr<UniformRandomVariable> rnd = CreateObject<UniformRandomVariable> ();
	  m_sendEvent = Simulator::Schedule (m_interval + Seconds (rnd->GetValue (0.0, 0.05)), &NeighborDiscovery::Send, this);
	  NS_LOG_DEBUG ( "Node " << GetNode ()->GetId () << " send data to 255.255.255.255 Time: " << (Simulator::Now ()).GetSeconds ());
	}else
	{
	  NS_LOG_ERROR ("Error while sending data");
	}
}

void
NeighborDiscovery::HandleRead(Ptr<Socket> socket)
{
	Ptr<Packet> packet;
	Address from;

	std::map<nodeid, Ptr<NeighborState> >::iterator it;

	while ((packet = socket->RecvFrom(from)))
	{
		if (packet->GetSize() > 0)
		{
			uint8_t buff[4];
			packet->CopyData(buff, sizeof(uint32_t));

			uint32_t id = buff[0] | (buff[1] << 8) | (buff[2] << 16)
					| (buff[3] << 24);

			it = Neighbours.find(id);
			Ptr<NeighborState> neighbor = 0;

			if (it != Neighbours.end())   // Found
			{
				neighbor = it->second;

				if (neighbor->IsActive())
				{
					neighbor->ResetTimer();
				}
				else
				{
					neighbor->DoActivate();
					ReportContact(GetNode ()->GetId (), it->first);
				}
			}

			else     // Not found
			{
				neighbor = CreateObject<NeighborState>();
				neighbor->SetAttribute("ConfidenceInterval",
						TimeValue(m_expirationTime));
				neighbor->SetAttribute("NodeId", UintegerValue(id));

				std::pair<nodeid, Ptr<NeighborState> > entry(id, neighbor);
				Neighbours.insert(Neighbours.begin(), entry);

				ReportContact(GetNode ()->GetId (), id);
			}
		}
	}
}

void
NeighborDiscovery::ReportContact(nodeid hostId, nodeid neighId)
{
	std::cout << "Contact from node: " << hostId << " to node: " << neighId << " in: " << Simulator::Now ().GetSeconds () << "s." << std::endl;
}

} // Namespace ns3
