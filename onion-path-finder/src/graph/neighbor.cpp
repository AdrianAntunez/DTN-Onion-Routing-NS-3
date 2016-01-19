/**
 * @copyright
 * Copyright (C) 2015 Universitat Autònoma de Barcelona
 * Department of Information and Communications Engineering
 * @file neighbor.cpp
 * @author Adrian Antunez
 * @date Created on:  26/5/2015
 */

#include "neighbor.h"

Neighbor::Neighbor() :
	m_hostId(0),
	m_id(0),
	m_activationTime(0),
	m_duration(0)
{}

Neighbor::Neighbor(nodeid hostId, nodeid id, uint32_t activationTime, uint32_t duration) :
	m_hostId(hostId),
	m_id(id),
	m_activationTime(activationTime),
	m_duration(duration)
{
}

std::ostream& Neighbor::operator<<(std::ostream& os)
{
    os << " " << m_id;
    return os;
}

Neighbor::~Neighbor()
{
}

