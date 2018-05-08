#pragma once
#include <memory>
#include <cassert>
#include "cipher_template.h"

class Counter
{
    private:
    unsigned char* data; 
    int _size;
    public:
    Counter(); 
    Counter(const unsigned char* data, int size);
    Counter(const Counter& counter);
    ~Counter();
    void increment();

    int size() const;
    const unsigned char* get() const;

    void set(const unsigned char* data, int size);
};

template<class T>
class CounterMode
{   
    private:
    Counter counter;
    T* cipher; 
    int position;
    unsigned char* current;

    void next()
    {
        assert(counter.size() == cipher->blocksize());                
        cipher->encrypt(counter.get(), current, cipher->blocksize());
        counter.increment();
        position = 0;
    }
    
    public:
    CounterMode() : position(-1), cipher(new T)
    {
        current = new unsigned char[cipher->blocksize()];
    }

    CounterMode(const Counter& counter) : position(-1), counter(counter), cipher(new T)
    {
        current = new unsigned char[cipher->blocksize()];
    }

    CounterMode(const Counter& counter, const unsigned char* key, int size) : position(-1), counter(counter), cipher(new T)
    {
        current = new unsigned char[cipher->blocksize()];
        setKey(key, size);
    }


    CounterMode(const CounterMode& cm) : counter(cm.counter), position(cm.position), cipher(new T(cm.cipher))
    {
        current = new unsigned char[cipher->blocksize()];
        memcpy(current, cm.current, cipher->blocksize());
    }

    ~CounterMode()
    {
        delete cipher;
        delete[] current;
    }

    void setKey(const unsigned char* key, int size)
    {
        assert(size == cipher->keysize());
        cipher->setKey(key, size);
        position = -1;
    }

    void setIV(const unsigned char* counter, int size)
    {
        this->counter.set(counter, size);
        position = -1;
    }

    void setIV(const Counter& counter)
    {
        this->counter = counter;
        position = -1;
    }

    void encrypt(const unsigned char* in, unsigned char* out, int size)
    {
        if(position == -1) next();

        for(int i = 0; i < size; i++)
        {
            if(position == cipher->blocksize()) next();
            out[i] = current[position] ^ in[i];
            position++;
        }
    }

    void decrypt(const unsigned char* in, unsigned char* out, int size)
    {
        encrypt(in, out, size);
    }
};