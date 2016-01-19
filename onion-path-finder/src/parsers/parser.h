/**
 * @copyright
 * Copyright (C) 2015 Universitat Autònoma de Barcelona
 * Department of Information and Communications Engineering
 * @file parser.h
 * @author Adrian Antunez
 * @author Rubén Martínez <rmartinez@deic.uab.cat>
 * @date Created on:  01/1/2016
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include "graph/neighbor.h"

/** \class Parser
    \brief The Parser class defines the basic interface for file parsers.
    Requires subclassing to implement parsers for specific file formats.
*/
class Parser {
public:
    /**
     * @brief Parses the specified file and returns a graph representation.
     * @param fileName name of the file to parse.
     * @return Nodes representing the graph contained in the file.
     */
    virtual Nodes Parse(std::string fileName) = 0;
};

#endif /* PARSER_H_ */
