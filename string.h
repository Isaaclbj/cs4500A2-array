//lang::CwC
#pragma once

#include "object.h"
/*
* Authors: Ryan Heminway (heminway.r@husky.neu.edu), David Tandetnik 
* CS4500 A1 Part 2 (String definition)
*/

class String : public Object
{
public:
    /** CONSTRUCTORS & DESTRUCTORS **/
    char* data;
    size_t data_size;

    /* Creates a String copying s */
    String(const char* s)
    {
        data_size = strlen(s);
        // null terminator
        data = new char[data_size];
        strcpy(data, s);
    }

    /* Copies a String copying the value from s */
    String(String* const s)
    {
        data_size = s->data_size;
        data = new char[data_size];
        strcpy(data, s->data);
    }

    /* Clears String from memory */
    ~String()
    {
        delete[] data;
        data_size = 0;
    }


    /** INHERITED METHODS **/

    /* Inherited from Object, generates a hash for a String */
    size_t hash()
    {
        size_t ret = 0;
        char* ptr = data;
        for(int ii = 0; ii < data_size; ii++)
        {
            ret += (size_t) *ptr;
            ptr++;
        }
        return ret;
    }

    /* Inherited from Object, checks equality between an String and an Object */
    bool equals(Object* const obj)
    {
        return (this->hash() == obj->hash());
    }


    /** STRING METHODS **/

    /** Compares strings based on alphabetical order
     * < 0 -> this String is less than String s
     * = 0 -> this String is equal to String s
     * > 0 -> this String is greater than String s
     */
    int cmp(String* const s)
    {
        return strcmp(data, s->data);
    }

    /* Creates a new String by combining two existing Strings */
    String* concat(String* const s)
    {
        size_t total = data_size + s->data_size;
        char *temp = new char[total];
        char *temp_ptr = temp;
        const char *data_ptr = data;
        for(int ii = 0; ii < data_size; ii++)
        {
            *temp_ptr = *data_ptr;
            temp_ptr ++;
            data_ptr ++;
        }

        data_ptr = s->data;
        for(int ii = 0; ii < s->data_size; ii++)
        {
            *temp_ptr = *data_ptr;
            temp_ptr ++;
            data_ptr ++;
        }
        
        String* ret = new String(temp);
        return ret;
    }

    /* Returns the current length of the String */
    size_t size()
    {
        return data_size;
    }
};