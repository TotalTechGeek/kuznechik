#include "ctr.h"
#include <memory>
#include <cstring>

Counter::Counter() : _size(0), data(0)
{

}

Counter::Counter(const unsigned char* data, int size) : _size(size)
{
    this->data = new unsigned char[_size];
    memcpy(this->data, data, _size);
}

Counter::Counter(const Counter& counter) : _size(counter._size)
{
    this->data = new unsigned char[_size];
    memcpy(this->data, counter.data, _size);
}



Counter::~Counter()
{
    delete[] data;
}

// Simple increment.
void Counter::increment()
{
    bool carry = false;

    data[_size - 1]++; 
    if(!data[_size-1]) carry = true;
    for(int i = _size - 2; i >= 0 && carry; i--)
    {
        carry = false;
        data[i]++;
        if(!data[i]) carry = true;
    }
}

const unsigned char* Counter::get() const
{
    return data;
}

int Counter::size() const
{
    return _size;
}

void Counter::set(const unsigned char* data, int size)
{
    if(this->_size)
    {
        if(this->_size == size)
        {
            memcpy(this->data, data, size);
        }
        else
        {
            if(this->data) delete[] this->data;
            this->data = new unsigned char[size];
            memcpy(this->data, data, size);
        }
    }
    else
    {
        if(this->data) delete[] this->data;
        this->data = new unsigned char[size];
        memcpy(this->data, data, size);
    }

    this->_size = size;
}
