/**
 * @copyright
 * Copyright (C) 2015 Universitat Autònoma de Barcelona
 * Department of Information and Communications Engineering
 * @file basic-parser.h
 * @author Adrian Antunez
 * @date Created on:  26/5/2015
 */


#ifndef PARSERBASIC_H
#define PARSERBASIC_H

#include "parser.h"

/**
 * @brief The BasicParser class Defines a basic parser for four-column (node neighbor contactTime contactDuration) txt graph representations.
 *
 */
class BasicParser : public Parser {
public:
    /**
     * @brief Default Constructor
     *
     */
    BasicParser();
    /**
     * @brief Default Destructor
     *
     */
    ~BasicParser();
    /**
     * @brief Parses the specified file and returns a graph representation.
     * @param fileName name of the file to parse.
     * @return Nodes representing the graph contained in the file.
     */
    Nodes Parse(std::string fileName);
};

#endif // PARSERBASIC_H
