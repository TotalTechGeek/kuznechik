#pragma once
#include "kuznechik.h"
#include <memory>
#include <cstring>
#include "ctr.h"

class KuzCipher : public CipherTemplate
{
	private:
	kuz_key_t* key;
    w128_t* x;
	public:

	KuzCipher() : key(new kuz_key_t), x(new w128_t)
	{

	}
    
    KuzCipher(KuzCipher* kc) : key(new kuz_key_t), x(new w128_t)
    {
        memcpy(key, kc->key, sizeof(kuz_key_t));
    }

    KuzCipher(const KuzCipher& kc) : key(new kuz_key_t), x(new w128_t)
    {
        memcpy(key, kc.key, sizeof(kuz_key_t));
    }

	~KuzCipher() 
	{
		delete key;
        delete x;
	}

	void setKey(const unsigned char* k, int size) override
	{
		kuz_init();
		kuz_set_encrypt_key(key, k);
	}

    void decrypt(const unsigned char* in, unsigned char* out, int size) override
    {
		memcpy(x->b, in, size);
		kuz_decrypt_block(key, x);
		memcpy(out, x->b, size);
    }

	void encrypt(const unsigned char* in, unsigned char* out, int size) override
	{
		memcpy(x->b, in, size);
		kuz_encrypt_block(key, x);
		memcpy(out, x->b, size);
	}

	inline int keysize() override
	{
		return 32;
	}

    inline int blocksize() override
	{
		return 16;
	}
};


typedef CounterMode<KuzCipher> KuzCtr;
