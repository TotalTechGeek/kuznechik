#pragma once 
class CipherTemplate
{
    public:
    virtual ~CipherTemplate() {}

    virtual void encrypt(const unsigned char* in, unsigned char* out, int size) = 0;
    virtual void decrypt(const unsigned char* in, unsigned char* out, int size) = 0;
    virtual void setKey(const unsigned char* key, int size) = 0;
    virtual int blocksize() = 0;
    virtual int keysize() = 0;
};