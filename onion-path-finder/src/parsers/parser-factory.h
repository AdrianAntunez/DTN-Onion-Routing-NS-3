/**
 * @copyright
 * Copyright (C) 2015 Universitat Autònoma de Barcelona
 * Department of Information and Communications Engineering
 * @file parser-factory.h
 * @author Rubén Martínez <rmartinez@deic.uab.cat>
 * @date Created on:  05/1/2016
 */

#ifndef PARSERFACTORY_H
#define PARSERFACTORY_H

#include "parser.h"
#include <exception>
#include <memory>

/**
 * @brief Defines parser types
 *
 */
enum ParserType { Basic, Crawdad, Unkwown};

/**
 * @brief The ParserFactory class defines the API used to create Parser instances.
 *
 */
class ParserFactory
{
public:
    /**
     * @brief Default constructor
     *
     */
    ParserFactory();
    /**
     * @brief Parametized constructor.
     *
     * @param std::string path to file.
     */
    ParserFactory(std::string);
    /**
     * @brief Returns a parser instance based on the type set during the construction of the object.
     *
     * @return Parser instance.
     */
    std::shared_ptr<Parser> GetParser();

    /**
     * @brief Get Parser Type, as of now the type of parser is decided by looking at the directory where the file is placed (data/basic or data/crawdad). This may be changed in the future.
     * @param std::string Full path to file.
     * @return return the type of parser.
     */
    ParserType getType(std::string file) const;

private:
    /**
     * @brief internal parser type
     */
    ParserType type;

    /**
     * @brief The UnsuportedParserException class defines a custom exception to throw in case of unsuported file format.
     *
     */
    class UnsuportedParserException : public std::exception
    {
      /**
       * @brief Provides the error message to display.
       *
       * @return const char
       */
      virtual const char* what() const throw()
      {
        return "No parser avaliable for specified file format\0";
      }
    };
    /**
     * @brief exception to throw on failure.
     */
    UnsuportedParserException fileExc;
};

#endif // PARSERFACTORY_H
