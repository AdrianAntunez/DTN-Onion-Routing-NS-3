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

#ifndef NEIGHBOR_DISCOVERY_HELPER_H
#define NEIGHBOR_DISCOVERY_HELPER_H

#include <stdint.h>
#include <string>
#include "ns3/uinteger.h"
#include "ns3/object-factory.h"
#include "ns3/address.h"
#include "ns3/attribute.h"
#include "ns3/attribute-helper.h"
#include "ns3/net-device.h"
#include "ns3/node-container.h"
#include "ns3/application-container.h"

namespace ns3 {

/**
 * \ingroup bulksend
 * \brief A helper to make it easier to instantiate an ns3::NeighborDiscovery
 * on a set of nodes.
 */
class NeighborDiscoveryHelper : public Object
{

public:
  static TypeId GetTypeId (void);
  /**
   * Create a NeighborDiscoveryHelper to make it easier to work with NeighborDiscovery
   */
  NeighborDiscoveryHelper (Time inter, uint16_t port, Time expiration);
  NeighborDiscoveryHelper ();
  ~NeighborDiscoveryHelper ();

  void Configure();

  /**
   * Helper function used to set the underlying application attributes, 
   * _not_ the socket attributes.
   *
   * \param name the name of the application attribute to set
   * \param value the value of the application attribute to set
   */
  void SetAttribute (std::string name, const AttributeValue &value);

  /**
   * Install an ns3::BulkSendApplication on each node of the input container
   * configured with all the attributes set with SetAttribute.
   *
   * \param c NodeContainer of the set of nodes on which an BulkSendApplication
   * will be installed.
   * \returns Container of Ptr to the applications installed.
   */
  ApplicationContainer Install (NodeContainer c) const;

  /**
   * Install an ns3::BulkSendApplication on the node configured with all the
   * attributes set with SetAttribute.
   *
   * \param node The node on which an NeighborDiscovery will be installed.
   * \returns Container of Ptr to the applications installed.
   */
  ApplicationContainer Install (Ptr<Node> node) const;

  /**
   * Install an ns3::BulkSendApplication on the node configured with all the
   * attributes set with SetAttribute.
   *
   * \param nodeName The node on which an NeighborDiscovery will be installed.
   * \returns Container of Ptr to the applications installed.
   */
  ApplicationContainer Install (std::string nodeName) const;

private:
  Time m_interval;
  Time m_expiration;
  uint16_t m_port;
  ObjectFactory m_factory;

  /**
   * Install an ns3::NeighborDiscoveryApplication on the node configured with all the
   * attributes set with SetAttribute.
   *
   * \param node The node on which an NeighborDiscovery will be installed.
   * \returns Ptr to the application installed.
   */
  Ptr<Application> InstallPriv (Ptr<Node> node) const;
};

} // namespace ns3

#endif /* NEIGHBOR_DISCOVERY_HELPER_H */

