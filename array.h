#pragma once

// lang::CwC
#include "object.h"

/**
 * Mutable Array API.
 */
class Array : public Object {
public:

    // fields
    Object** data;
    size_t cap;
    size_t used;

    /**
     * Default Array constructor. Creates a new array.
     */
    Array() {
        data = new Object*[2];
        cap = 2;
        used = 0;
    }

    /**
     * Default array desctructor. Free any memory used.
     */
    virtual ~Array() {
        delete[](data);
        cap = 0;
        used = 0;
    }

    /**
     * Adds the given object `o` to the end of the Array.
     */
    virtual void append(Object* o) 
    {
        used++;
        // expand
        if(used > cap)
        {
            cap *= 2;
            Object** temp = new Object*[cap];
            memcpy(temp, data, (used - 1) * sizeof(Object*));
            delete[] data;
            data = temp;
        }
        data[used - 1] = o;
    }

    /**
     * Inserts the given object `o` at index `index` of the Array.
     * Throws an error if `index` is out of range.
     */
    virtual void insert(size_t index, Object* o) 
    {
        // push back
        used ++;

        // expand
        if(used > cap)
        {
            cap *= 2;
            Object** temp = new Object*[cap];
            memcpy(temp, data, (used - 1) * sizeof(Object*));
            delete[] data;
            data = temp;
        }

        Object* prev = o;
        for(int ii = index; ii < used; ii ++)
        {
            Object* temp;
            temp = data[ii];
            data[ii] = prev;
            prev = temp;
        }
    }


    /**
     * Combines two Arrays by adding all elements of `other` at index `index` of this Array.
     * Throws an error if `index` is out of range.
     */
    virtual void combine(size_t index, Array* other) 
    {
        if(index > used)
        {
            perror("index out of bound");
            return;
        }
        else
        {
            while (cap < used + other->size())
            {
                cap *= 2;
                Object** temp = new Object*[cap];
                memcpy(temp, data, used * sizeof(Object*));
                delete[] data;
                data = temp;
            }
            for(int ii = 0; ii < other->size(); ii ++)
            {
                insert(index, other->get(ii));
                index++;
            }
        }
    }

    /**
     * Removes and returns the element at index `index` of the Array.
     * Throws an error if `index` is out of range.
     */
    virtual Object* remove(size_t index) 
    {
        if(index >= used)
        {
            perror("index out of bound");
            return 0;
        }
        else
        {
            Object* ret = data[index];
            // push
            for(int ii = index; ii < used; ii++)
            {
                data[ii] = data[ii + 1];
            }
            used --;
            return ret;
        }
    }

    /**
     * Removes all elements from this array.
     */
    virtual void clear() 
    {
        for(int ii = 0; ii < used; ii++)
        {
            delete(data[ii]);
        }
        delete[](data);
        cap = 2;
        used = 0;
        data = new Object*[cap];
    }

    /**
     * Returns the element at index `index` of the Array.
     * Throws an error if `index` is out of range (i.e. 4 in a size 2 Array)
     * or less than 0.
     */
    virtual Object* get(size_t index) 
    {
        if(index >= used)
        {
            perror("index out of bound");
            return 0;
        }
        return data[index];
    }

    /**
     * Returns the index of the given Object `o`.
     * If it is not found in the Array, return length
     */
    virtual size_t index_of(Object* o) 
    {
        int index = 0;
        while(index < used)
        {
            if(o->equals(this->get(index)))
            {
                return index;
            }
            index++;
        }
        return -1;
    }

    /**
     * Returns whether the Array contains the given Object `o`.
     */
    virtual bool contains(Object* o) 
    {
        size_t index = 0;
        while(index < used)
        {
            if(o->equals(this->get(index)))
            {
                return true;
            }
            index++;
        }
        return false;
    }

    /**
     * Sets the element at index `index` of the Array to the given object `o`.
     * Returns the element that was overwritten.
     * Throws an error if `index` is out of range (i.e. 4 in a size 2 Array)
     * or less than 0.
     */
    virtual Object* set(size_t index, Object* o) 
    {
        Object* ret = data[index];
        data[index] = o;
        return ret;
    }

    /**
     * Returns the size of the Array.
     */
    virtual size_t size() 
    {
        return used;
    }

    /**
     * Determines whether this Array and the other are equal.
     */
    virtual bool equals(Object* other) 
    {
        if(hash() == other->hash())
        {
            return true;
        }
        else
        {
            return false;
        }
        
    }

    /**
     * Generates a hash value based on the elements in the
     * Array and their associated indices.
     */
    virtual size_t hash() 
    {
        // physical address
        size_t ret = 0;
        for(int ii = 0; ii < used; ii++)
        {
            ret += data[ii]->hash();
        }
        return ret;
    }


};

class IntArray : public Object {
public:

    // fields
    int* data;
    size_t cap;
    size_t used;

    IntArray() 
    {
        data = new int[2];
        cap = 2;
        used = 0;
    }

    virtual ~IntArray() 
    {
        delete[](data);
        cap = 0;
        used = 0;
    }

    /**
     * Adds `val` to this array.
     */
    virtual void append(int val) 
    {
        used ++;
        if(used > cap)
        {
            cap*= 2;
            int* temp = new int[cap];
            memcpy(temp, data, sizeof(int) * (used - 1));
            delete[](data);
            data = temp;
        }
        data[used - 1] = val;
    }

    /**
     * Insert int `val` at index.
     */
    virtual void insert(int val, size_t index) 
    {
        used ++;
        if(used > cap)
        {
            cap*= 2;
            int* temp = new int[cap];
            memcpy(temp, data, sizeof(int) * (used - 1));
            delete[](data);
            data = temp;
        }

        int prev = val;
        for(int ii = index; ii < used; ii ++)
        {
            int temp;
            temp = data[ii];
            data[ii] = prev;
            prev = temp;
        }
    }

    /**
     * Combines this array and `other` at provided index.
     */
    virtual void combine(size_t index, IntArray* other) 
    {
        if(index > used)
        {
            perror("index out of bound");
            return;
        }
        else
        {
            while (cap < used + other->size())
            {
                cap *= 2;
                int* temp = new int[cap];
                memcpy(temp, data, used * sizeof(int));
                delete[] data;
                data = temp;
            }
            for(int ii = 0; ii < other->size(); ii ++)
            {
                insert(index, other->get(ii));
                index++;
            }
        }
    }

    /**
     * Removes int at provided index.
     */
    virtual int remove(size_t index) 
    {
        if(index >= used)
        {
            perror("index out of bound");
            return 0;
        }
        else
        {
            int ret = data[index];
            // push
            for(int ii = index; ii < used; ii++)
            {
                data[ii] = data[ii + 1];
            }
            used --;
            return ret;
        }
    }

    /**
     * Removes all elements from this array.
     */
    virtual void clear() 
    {
        delete[](data);
        used = 0;
        cap = 2;
        data = new int[cap];
    }

    /**
     * Returns the element at index `index` of the Array.
     * Throws an error if `index` is out of range (i.e. 4 in a size 2 Array)
     * or less than 0.
     */
    virtual int get(size_t index) 
    {
        return data[index];
    }

    /**
     * Returns the index of the given int `value`.
     * If it is not found in the Array, return length
     */
    virtual size_t index_of(int value) 
    {
        int index = 0;
        while(index < used)
        {
            if(value == data[index])
            {
                return index;
            }
            index ++;
        }
        return used;
    }

    /**
     * Returns whether the Array contains the given int `value`.
     */
    virtual bool contains(int value) 
    {
        int index = 0;
        while(index < used)
        {
            if(value == data[index])
            {
                return true;
            }
            index++;
        }
        return false;
    }

    /**
     * Sets the element at index `index` of the Array to the given int `value`.
     * Returns the element that was overwritten.
     * Throws an error if `index` is out of range (i.e. 4 in a size 2 Array)
     * or less than 0.
     */
    virtual int set(size_t index, int value) 
    {
        if(index >= used)
        {
            perror("index out of bound");
            return -1;
        }
        int ret = data[index];
        data[index] = value;
        return ret;
    }

    /**
     * Returns the size of the Array.
     */
    virtual size_t size() 
    {
        return used;
    }

    /**
     * Determines whether this Array and the other are equal.
     */
    virtual bool equals(Object* other) 
    {
        return (other->hash() == hash());
    }

    /**
     * Generates a hash value based on the elements in the
     * Array and their associated indices.
     */
    virtual size_t hash() 
    {
        size_t ret = 0;
        for(int ii = 0; ii < used; ii++)
        {
            ret ++;
            ret *= 2;
            ret += data[ii];
        }
        return ret;
    }
};

class FloatArray : public Object {
public:
    
    // fields
    float* data;
    size_t cap;
    size_t used;

    FloatArray() 
    {
        data = new float[2];
        cap = 2;
        used = 0;
    }

    virtual ~FloatArray() 
    {
        delete[](data);
        cap = 0;
        used = 0;
    }

    /**
     * Adds `val` to this array.
     */
    virtual void append(float val) 
    {
        used ++;
        if(used > cap)
        {
            cap*= 2;
            float* temp = new float[cap];
            memcpy(temp, data, sizeof(float) * (used - 1));
            delete[](data);
            data = temp;
        }
        data[used - 1] = val;
    }

    /**
     * Insert this float at index.
     */
    virtual void insert(float val, size_t index) 
    {
        used ++;
        if(used > cap)
        {
            cap*= 2;
            float* temp = new float[cap];
            memcpy(temp, data, sizeof(float) * (used - 1));
            delete[](data);
            data = temp;
        }

        float prev = val;
        for(int ii = index; ii < used; ii ++)
        {
            float temp;
            temp = data[ii];
            data[ii] = prev;
            prev = temp;
        }
    }

    /**
     * Combines this array and `other` at provided index.
     */
    virtual void combine(size_t index, FloatArray* other) 
    {
        if(index > used)
        {
            perror("index out of bound");
            return;
        }
        else
        {
            while (cap < used + other->size())
            {
                cap *= 2;
                float* temp = new float[cap];
                memcpy(temp, data, used * sizeof(float));
                delete[](data);
                data = temp;
            }
            for(int ii = 0; ii < other->size(); ii ++)
            {
                insert(index, other->get(ii));
                index++;
            }
        }
    }

    /**
     * Removes float at provided index.
     */
    virtual float remove(size_t index) 
    {
        if(index >= used)
        {
            perror("index out of bound");
            return 0;
        }
        else
        {
            int ret = data[index];
            // push
            for(int ii = index; ii < used; ii++)
            {
                data[ii] = data[ii + 1];
            }
            used --;
            return ret;
        }
    }

    /**
     * Removes all elements from this array.
     */
    virtual void clear() 
    {
        delete[](data);
        cap = 2;
        used = 0;
        data = new float[cap];
    }

    /**
     * Returns the element at index `index` of the Array.
     * Throws an error if `index` is out of range (i.e. 4 in a size 2 Array)
     * or less than 0.
     */
    virtual float get(size_t index) 
    {
        return data[index];
    }

    /**
     * Returns the index of the given float `value`.
     * If it is not found in the Array, return length
     */
    virtual size_t index_of(float value) 
    {
        int ii = 0;
        while(ii < used)
        {
            if(data[ii] - value < 0.001)
            {
                return ii;
            }
            ii++;
        }
        return used;
    }

    /**
     * Returns whether the Array contains the given float `value`.
     */
    virtual bool contains(float value) 
    {
        int ii = 0; 
        while(ii < used)
        {
            if(data[ii] - value < 0.001)
            {
                return true;
            }
            ii++;
        }
        return false;
    }

    /**
     * Sets the element at index `index` of the Array to the given object `o`.
     * Returns the element that was overwritten.
     * Throws an error if `index` is out of range (i.e. 4 in a size 2 Array)
     * or less than 0.
     */
    virtual float set(size_t index, float value) 
    {
        float ret = data[index];
        data[index] = value;
        return ret;
    }

    /**
     * Returns the size of the Array.
     */
    virtual size_t size() 
    {
        return used;
    }

    /**
     * Determines whether this Array and the other are equal.
     */
    virtual bool equals(Object* other) 
    {
        return (hash() == other->hash());
    }

    /**
     * Generates a hash value based on the elements in the
     * Array and their associated indices.
     */
    virtual size_t hash() {
        size_t ret = 0;
        for(int ii = 0; ii < used; ii++)
        {
            ret ++;
            ret *= 2;
            ret += data[ii];
        }
        return ret;
    }
};

class BoolArray : public Object {
public:
    bool* data;
    size_t used;
    size_t cap;

    BoolArray() 
    {
        data = new bool[2];
        used = 0;
        cap = 2;
    }

    virtual ~BoolArray() 
    {
        delete[](data);
    }

    /**
     * Adds `val` to this array.
     */
    virtual void append(bool val) 
    {
        used ++;
        if(used > cap)
        {
            cap *= 2;
            bool* temp = new bool[cap];
            memcpy(temp, data, (used - 1));
            delete[](data);
            data = temp;
        }
        data[used - 1] = val;
    }

    /**
     * Insert this bool at index.
     */
    virtual void insert(bool val, size_t index) 
    {
        used ++;
        if(used > cap)
        {
            cap *= 2;
            bool* temp = new bool[cap];
            memcpy(temp, data, (used - 1));
            delete[](data);
            data = temp;
        }

        bool prev = val;
        for(int ii = index; ii < used; ii ++)
        {
            bool temp;
            temp = data[ii];
            data[ii] = prev;
            prev = temp;
        }
    }

    /**
     * Combines this array and `other` at provided index.
     */
    virtual void combine(size_t index, BoolArray* other) 
    {
        if(index > used)
        {
            perror("index out of bound");
            return;
        }
        else
        {
            while (cap < used + other->size())
            {
                cap *= 2;
                bool* temp = new bool[cap];
                memcpy(temp, data, used);
                delete[](data);
                data = temp;
            }
            for(int ii = 0; ii < other->size(); ii ++)
            {
                insert(other->get(ii), index);
                index++;
            }
        }
    }

    /**
     * Removes bool at provided index.
     */
    virtual bool remove(size_t index) 
    {
        if(index >= used)
        {
            perror("index out of bound");
            return 0;
        }
        else
        {
            int ret = data[index];
            // push
            for(int ii = index; ii < used; ii++)
            {
                data[ii] = data[ii + 1];
            }
            used --;
            return ret;
        }
    }

    /**
     * Removes all elements from this array.
     */
    virtual void clear() 
    {
        delete[](data);
        cap = 2;
        used = 0;
        data = new bool[cap];
    }

    /**
     * Returns the element at index `index` of the Array.
     * Throws an error if `index` is out of range (i.e. 4 in a size 2 Array)
     * or less than 0.
     */
    virtual bool get(size_t index) 
    {
        return data[index];
    }

    /**
     * Returns the index of the given bool `value`.
     * If it is not found in the Array, return length
     */
    virtual size_t index_of(bool value) 
    {
        int ii = 0;
        while(ii < used)
        {
            if(data[ii] == value)
            {
                return ii;
            }
            ii++;
        }
        return used;
    }

    /**
     * Returns whether the Array contains the given bool `value`.
     */
    virtual bool contains(bool value) 
    {
        int ii = 0;
        while(ii < used)
        {
            if(data[ii] == value)
            {
                return true;
            }
            ii++;
        }
        return false;
    }

    /**
     * Sets the element at index `index` of the Array to the given object `o`.
     * Returns the element that was overwritten.
     * Throws an error if `index` is out of range (i.e. 4 in a size 2 Array)
     * or less than 0.
     */
    virtual bool set(size_t index, bool value) 
    {
        bool ret = data[index];
        data[index] = value;
        return ret;
    }

    /**
     * Returns the size of the Array.
     */
    virtual size_t size() 
    {
        return used;
    }

    /**
     * Determines whether this Array and the other are equal.
     */
    virtual bool equals(Object* other) 
    {
        return (hash() == other->hash());
    }

    /**
     * Generates a hash value based on the elements in the
     * Array and their associated indices.
     */
    virtual size_t hash() 
    {
        size_t ret = 4096;
        for(int ii = 0; ii < used; ii++)
        {
            ii++;
            if(data[ii])
            {
                ret *= (ii * ii);
            }
        }
        return ret;
    }
};