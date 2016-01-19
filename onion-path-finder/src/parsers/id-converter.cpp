/**
 * @copyright
 * Copyright (C) 2016 Universitat Autònoma de Barcelona
 * Department of Information and Communications Engineering
 * @file id-converter.cpp
 * @author Rubén Martínez - <rmartinez@deic.uab.cat>
 * @date Created on: 12/1/2016
 * @brief IdConverter
 */

#include "id-converter.h"
#include <iostream>

IdConverter::IdConverter():
    baseId(0),
    idToName(),
    nameToId()
{
}
IdConverter::~IdConverter()
{
}

uint32_t
IdConverter::getId(std::string name)
{
    std::map<std::string,uint32_t>::iterator it = nameToId.find(name);

    if (it == nameToId.end())
    {
        idToName[baseId]=name;
        nameToId[name]=baseId;
        return baseId++;
    }
    else
        return it->second;

}
std::string
IdConverter::getName(uint32_t id) const
{
    return idToName.at(id);
}
