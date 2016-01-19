/**
 * @copyright
 * Copyright (C) 2016 Universitat Autònoma de Barcelona
 * Department of Information and Communications Engineering
 * @file object-factory.h
 * @author Rubén Martínez - <rmartinez@deic.uab.cat>
 * @date Created on: 14/1/2016
 * @brief ObjectFactory
 * \todo 4. Implementation pending: Global uniform object instantiation using ObjectFactory.
 */

#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <memory.h>

/**
 * @brief The ObjectFactory class provides a factory for uniform object instantiation.
 */
class ObjectFactory
{
public:
    ObjectFactory();
    ~ObjectFactory();
};

#endif // OBJECTFACTORY_H
