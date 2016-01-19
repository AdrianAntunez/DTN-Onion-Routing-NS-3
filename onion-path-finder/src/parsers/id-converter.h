/**
 * @copyright
 * Copyright (C) 2016 Universitat Autònoma de Barcelona
 * Department of Information and Communications Engineering
 * @file id-converter.h
 * @author Rubén Martínez - <rmartinez@deic.uab.cat>
 * @date Created on: 12/1/2016
 * @brief IdConverter
 */

#ifndef IDCONVERTER_H
#define IDCONVERTER_H

#include <map>

/**
 * @brief Singleton ID generator that keeps track of assigned ids mapping them to node names.
 *
 */
class IdConverter
{
public:

   /**
    * @brief
    *
    * @return IdConverter
    */
   static IdConverter& Instance() {
       static IdConverter instance;
       return instance;
   }

   /**
    * @brief
    *
    * @param uint32_t
    * @return uint32_t
    */
   uint32_t getId(std::string);
   /**
    * @brief
    *
    * @param uint32_t
    * @return uint32_t
    */
   std::string getName(uint32_t) const;

   /**
    * @brief lastId
    * @return
    */
   uint32_t lastId() const { return baseId-1; }


private:

    /**
     * @brief
     *
     */
    IdConverter();
    /**
     * @brief
     *
     */
    ~IdConverter();

    std::map<uint32_t,std::string> idToName; /**< TODO */
    std::map<std::string,uint32_t> nameToId;
    uint32_t baseId; /**< TODO */

};

#endif // IDCONVERTER_H
