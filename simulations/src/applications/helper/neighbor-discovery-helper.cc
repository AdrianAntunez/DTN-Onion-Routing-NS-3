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

#include "neighbor-discovery-helper.h"

#include "ns3/log.h"
#include "ns3/config.h"
#include "ns3/trace-helper.h"
#include "ns3/inet-socket-address.h"
#include "ns3/packet-socket-address.h"
#include "ns3/string.h"
#include "ns3/names.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("NeighborDiscoveryHelper");

NS_OBJECT_ENSURE_REGISTERED (NeighborDiscoveryHelper);

TypeId
NeighborDiscoveryHelper::GetTypeId (void)
{
  static TypeId tid =
		  TypeId ("ns3::NeighborDiscoveryHelper")
		  .SetParent<Object> ()
		  .AddConstructor<NeighborDiscoveryHelper> ()
		  .AddAttribute ("ListenerPort","The port used for neighbor discovery applications.",
		                     TypeId::ATTR_CONSTRUCT | TypeId::ATTR_SET | TypeId::ATTR_GET,
		                     UintegerValue (0),
		                     MakeUintegerAccessor (&NeighborDiscoveryHelper::m_port),
		                     MakeUintegerChecker<uint16_t> ())
		  .AddAttribute ("Interval",
						 "Time interval between broadcasted messages.",
						 TypeId::ATTR_CONSTRUCT | TypeId::ATTR_SET | TypeId::ATTR_GET,
						 TimeValue (Seconds (0)),
						 MakeTimeAccessor (&NeighborDiscoveryHelper::m_interval),
						 MakeTimeChecker ())
		  .AddAttribute ("ExpirationTime",
						 "Cache expiration",
						 TypeId::ATTR_CONSTRUCT | TypeId::ATTR_SET | TypeId::ATTR_GET,
						 UintegerValue (0),
						 MakeTimeAccessor (&NeighborDiscoveryHelper::m_expiration),
						 MakeTimeChecker ());
  return tid;
}

NeighborDiscoveryHelper::NeighborDiscoveryHelper () :
		m_interval(0),
		m_port(0),
		m_expiration(0)
{
	Configure();
}

NeighborDiscoveryHelper::NeighborDiscoveryHelper (Time inter, uint16_t port, Time expiration) :
		m_interval(inter),
		m_port(port),
		m_expiration(expiration)
{
	Configure();
}

void
NeighborDiscoveryHelper::Configure()
{
	m_factory.SetTypeId ("ns3::NeighborDiscovery");
	m_factory.Set ("ListenerPort", UintegerValue (m_port));
	m_factory.Set ("Interval", TimeValue (m_interval));
	m_factory.Set ("ExpirationTime", TimeValue (m_expiration));
}

NeighborDiscoveryHelper::~NeighborDiscoveryHelper()
{}

void
NeighborDiscoveryHelper::SetAttribute (std::string name, const AttributeValue &value)
{
  m_factory.Set (name, value);
}

ApplicationContainer
NeighborDiscoveryHelper::Install (Ptr<Node> node) const
{
  return ApplicationContainer (InstallPriv (node));
}

ApplicationContainer
NeighborDiscoveryHelper::Install (std::string nodeName) const
{
  Ptr<Node> node = Names::Find<Node> (nodeName);
  return ApplicationContainer (InstallPriv (node));
}

ApplicationContainer
NeighborDiscoveryHelper::Install (NodeContainer c) const
{
  ApplicationContainer apps;
  for (NodeContainer::Iterator i = c.Begin (); i != c.End (); ++i)
    {
      apps.Add (InstallPriv (*i));
    }

  return apps;
}

Ptr<Application>
NeighborDiscoveryHelper::InstallPriv (Ptr<Node> node) const
{
  Ptr<Application> app = m_factory.Create<Application> ();
  node->AddApplication (app);

  return app;
}

} // namespace ns3
