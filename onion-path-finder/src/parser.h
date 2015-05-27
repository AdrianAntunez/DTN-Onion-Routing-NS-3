/*
 * Parser.h
 *
 *  Created on: 26 May 2015
 *      Author: Adrian Antunez
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include "neighbor.h"

//#include "types.h"

//static const char DELIMITER = ':';

class Parser {
public:
	static Nodes getContactsFromTxt (std::string fileName);
};

#endif /* PARSER_H_ */
