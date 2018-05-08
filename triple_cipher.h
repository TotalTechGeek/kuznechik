#pragma once
#include "cipher_template.h"

template <class C>
class TripleCipher : public CipherTemplate
{
    private:
    C* a;
    C* b; 
    C* c;
    public:

    TripleCipher() : a(new C), b(new C), c(new C)
    {}

    TripleCipher(TripleCipher* tc) : a(new C(tc->a)), b(new C(tc->b)), c(new C(tc->c))
    {}

    TripleCipher(const TripleCipher& tc) : a(new C(tc.a)), b(new C(tc.b)), c(new C(tc.c))
    {}

    void encrypt(const unsigned char* in, unsigned char* out, int size) override
    {
        a->encrypt(in, out, size);
        b->decrypt(out, out, size);
        c->encrypt(out, out, size);
    }

    
    void decrypt(const unsigned char* in, unsigned char* out, int size) override
    {
        a->decrypt(in, out, size);
        b->encrypt(out, out, size);
        c->decrypt(out, out, size);
    }
    
    void setKey(const unsigned char* key, int size) override
    {
        a->setKey(key, a->keysize());
        b->setKey(key + a->keysize(), a->keysize());
        c->setKey(key + 2*a->keysize(), a->keysize());
    }
    
    int blocksize() override
    {
        return a->blocksize();
    }
    
    int keysize() override
    {
        return a->keysize() * 3;
    }


    ~TripleCipher()
    {
        delete a;
        delete b;
        delete c;
    }
};
