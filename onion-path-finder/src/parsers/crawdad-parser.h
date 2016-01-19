/**
 * @copyright
 * Copyright (C) 2015 Universitat Autònoma de Barcelona
 * Department of Information and Communications Engineering
 * @file crawdad-parser.h
 * @author Rubén Martínez <rmartinez@deic.uab.cat>
 * @date Created on:  12/12/2015
 */

#ifndef CRAWDADPARSER_H
#define CRAWDADPARSER_H

#include "parser.h"

/**
 * @brief Defines a parser for CRAWDAD (www.crawdad.org) mobility traces.
 *
 */
class CrawdadParser : public Parser {
public:
    /**
     * @brief Default Constructor
     *
     */
    CrawdadParser();
    /**
     * @brief Default Destructor
     *
     */
    ~CrawdadParser();
    /**
     * @brief Parses the specified file and returns a graph representation.
     * @param fileName name of the file to parse.
     * @return Nodes representing the graph contained in the file.
     */
    Nodes Parse(std::string fileName);
};

#endif // CRAWDADPARSER_H
