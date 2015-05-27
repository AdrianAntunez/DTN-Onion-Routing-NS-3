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


#include "neighbor-state.h"
#include "ns3/log.h"
#include "ns3/timer.h"
#include "ns3/uinteger.h"


namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("NeighborState");
NS_OBJECT_ENSURE_REGISTERED (NeighborState);

TypeId
NeighborState::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::NeighborState")
    .SetParent<Object> ()
    .AddConstructor<NeighborState> ()
    .AddAttribute ("ConfidenceInterval",
        "How long do we wait until being certain the node is inactive",
        TimeValue (Seconds (1.0)),
        MakeTimeAccessor (&NeighborState::m_confidenceInterval),
        MakeTimeChecker ())
  	.AddAttribute ("NodeId",
          "NodeId of the current neighbor",
		  TypeId::ATTR_CONSTRUCT | TypeId::ATTR_SET | TypeId::ATTR_GET,
		  UintegerValue (0),
		  MakeUintegerAccessor (&NeighborState::m_nodeId),
		  MakeUintegerChecker<uint32_t> ());
    return tid;
}

NeighborState::NeighborState() :
    m_nodeId(0),
    m_activationTime( Simulator::Now()),
    m_lastactivityTime ( Simulator::Now()),
    m_expirationTimer(Timer::CANCEL_ON_DESTROY),
    m_state(true),
    m_activationTimes(0),
	m_notifyLost(MakeNullCallback<void, uint32_t, Time> ()),
    m_confidenceInterval( Seconds (0))

{
  NS_LOG_FUNCTION(this);
}

NeighborState::~NeighborState()
{
  NS_LOG_FUNCTION(this);
}

void NeighborState::DoActivate()
{
  NS_LOG_FUNCTION(this);

  m_state = true;
  m_activationTime = Simulator::Now();

  ResetTimer();
}

void NeighborState::DoDeActivate()
{
  NS_LOG_FUNCTION(this);
  if (!m_notifyLost.IsNull())
  {
	  m_notifyLost(m_nodeId, m_activationTime);
  }
  m_state = false;
}

void NeighborState::ResetTimer()
{
  NS_LOG_FUNCTION(this);

  if (m_expirationTimer.IsRunning())
    m_expirationTimer.Cancel();

  m_lastactivityTime = Simulator::Now();

  m_expirationTimer.SetDelay(m_confidenceInterval);
  m_expirationTimer.SetFunction(&NeighborState::DoDeActivate, this);
  m_expirationTimer.Schedule();
}

void
NeighborState::StopTimer()
{
  NS_LOG_FUNCTION(this);

  if (m_expirationTimer.IsRunning())
    m_expirationTimer.Cancel();

  DoDeActivate();
}
bool
NeighborState::operator < (NeighborState const &o) const
{
  return (m_nodeId < o.m_nodeId);
}

bool
NeighborState::IsActive() const
{
  NS_LOG_FUNCTION(this);
  return m_state;
}

void NeighborState::SetNotificationCallback(Callback<void, uint32_t, Time> cb)
{
	m_notifyLost = cb;
}

} // namespace ns3
