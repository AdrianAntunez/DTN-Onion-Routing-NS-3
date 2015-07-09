/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) Sep 15, 2014
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
 * Author: rmartinez 
 */
#ifndef NEIGHBOR_STATE_H_
#define NEIGHBOR_STATE_H_


#include "ns3/timer.h"
#include "ns3/object.h"
#include "ns3/callback.h"

namespace ns3 {

  enum NeighborReportCode
  {
     Active = 0,
     Inactive = 1
  };

class NeighborState : public Object
{
public:


  /**
   * Default constructor
   * At creation time the neighbor is active
   */
  NeighborState();
  ~NeighborState();

  static TypeId GetTypeId (void);


  void DoActivate();
  void DoDeActivate();

  bool IsActive() const;

  void ResetTimer();
  void StopTimer();

  bool operator < (NeighborState const &o) const;

  void SetNotificationCallback( Callback<void, uint32_t, Time > cb);

  uint32_t getNodeId() {return m_nodeId;}


private:

  uint32_t m_nodeId;
  Time m_activationTime;
  Time m_lastactivityTime;
  Timer m_expirationTimer;

  bool m_state;

  uint32_t m_activationTimes;
  Time m_confidenceInterval; // Confidence interval to decide whether a connection has been lost or not.

  Callback<void, uint32_t, Time> m_notifyLost;

};

} // namespace ns3

#endif /* NEIGHBOR_STATE_H_ */
