/**
 * @copyright
 * Copyright (C) 2015 Universitat Autònoma de Barcelona
 * Department of Information and Communications Engineering
 * @file parser-factory.cpp
 * @author Rubén Martínez <rmartinez@deic.uab.cat>
 * @date Created on:  05/1/2016
 */

#include "parser-factory.h"
#include "basic-parser.h"
#include "crawdad-parser.h"
#include <regex>


ParserFactory::ParserFactory()
{}
ParserFactory::ParserFactory(std::string file)
{
  type = getType(file);
  if (type == Unkwown) throw fileExc;
}

std::shared_ptr<Parser> ParserFactory::GetParser()
{
    switch(type)
    {
        case Basic:
            return std::shared_ptr<Parser> (new BasicParser());
        case Crawdad:
            return std::shared_ptr<Parser> (new CrawdadParser());
        case Unkwown:
        default:
            throw fileExc;
    }
}

ParserType ParserFactory::getType(std::string file) const
{
    std::regex basicFolder ("^data/basic/.*", std::regex_constants::ECMAScript);
    std::regex crawdadFolder ("^data/crawdad/.*", std::regex_constants::ECMAScript);

    if (std::regex_search(file, basicFolder))
            return Basic;
    else if (std::regex_search(file, crawdadFolder))
            return Crawdad;
    else    return Unkwown;
}
