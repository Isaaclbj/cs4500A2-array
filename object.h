//lang::CwC
#pragma once

#include <cstdlib>
#include <stdio.h>
#include <string.h>

/**
 * A class that represents the top of the object hierarchy.
 * author: chasebish */
class Object
{
public:
    /** CONSTRUCTORS & DESTRUCTORS **/
    size_t hash__;
    /* Default Object constructor */
    Object()
    {
        hash__ = 0;
    }

    /* Default Object destructor, to be overriden by subclasses */
    virtual ~Object()
    {
        hash__ = 0;
    }


    /** VIRTUAL METHODS **/

    /* Returns whether two objects are equal, to be overriden by subclasses */
    virtual bool equals(Object* const obj)
    {
        return (hash() == obj->hash());
    };

    /* Returns an object's hash value. Identical objects should have identical hashes */
    virtual size_t hash()
    {
        return 0;
    }
};