/**
 * @copyright
 * Copyright (C) 2015 Universitat Autònoma de Barcelona
 * Department of Information and Communications Engineering
 * @file crawdad-parser.cpp
 * @author Rubén Martínez <rmartinez@deic.uab.cat>
 * @date Created on:  12/12/2015
 */

#include "crawdad-parser.h"
#include "id-converter.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <regex>
#include <string>

CrawdadParser::CrawdadParser()
{}
CrawdadParser::~CrawdadParser()
{}

Nodes
CrawdadParser::Parse (std::string fileName)
{
    std::ifstream infile;
    std::string host, neighbor;
    std::string date;
    double txData = 0, duration = 0, gps_x = 0, gps_y = 0;

    Nodes nodes;

    infile.open(fileName.c_str());   

    if (infile.is_open())
    {
        while (infile >> host >> neighbor >> date >> txData >> duration >> gps_x >> gps_y)
        {
            IdConverter& Converter = IdConverter::Instance();

            uint32_t hostId = Converter.getId(host);
            uint32_t neighborId = Converter.getId(neighbor);

            uint32_t activationTime = 0;
            std::regex time ("[\\:]+");
            std::sregex_token_iterator it(date.begin(), date.end(),time, -1);
            for (uint16_t unit = 3600; it != std::sregex_token_iterator(); ++it, unit/=60)
            {
                activationTime += ( std::stoi((it)->str()) * unit);
            }

            std::shared_ptr<Neighbor> neighbor = std::make_shared<Neighbor>(hostId, neighborId, activationTime, duration);
            nodes[hostId][(uint32_t) activationTime].push_back(neighbor);
        }
    }
    else
    {
        std::cout << "Unable to open file" << std::endl;
    }

    return nodes;
}
