//
//  DesEncrypt.m
//  MLPlayer
//
//  Created by whf on 13-7-8.
//  Copyright (c) 2013 All rights reserved.
//


#include "stdafx.h"
#include "desencrypt.h"
#include "utf8ncpy.h"
#include <openssl/des.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

// http://www.ajanicij.info/content/openssl-sample-code-using-bio
char* DesEncrypt::doEncrypt(const char* in, const char* key)
{
    BIO *cipher, *b64, *bmem;
	int len, tol, write;
	char* out;
    
    len = strlen(in);

    cipher = BIO_new(BIO_f_cipher());
    BIO_set_cipher (cipher, EVP_des_cbc (),(const unsigned char *)key, (const unsigned char *)key, 1);
    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bmem = BIO_new(BIO_s_mem());
    
    BIO_push(cipher, b64);
    BIO_push(b64, bmem);

    for (tol = 0; tol < len; tol += write)
    {
        if ((write = BIO_write(cipher, in + tol, len - tol)) <= 0)
        {
            if (BIO_should_retry(cipher))
            {
                write = 0;
                continue;
            }
            break;
        }
    }

    
    if (!BIO_flush (cipher))
    {
        printf("Bad encrypt!\n");
        BIO_free_all(cipher);
        return NULL;
    }

	BUF_MEM* bptr;
	BIO_get_mem_ptr(bmem, &bptr);
	out = new char[bptr->length+1];
	memset(out, 0, bptr->length+1);
	memcpy(out, bptr->data, bptr->length);

    BIO_free_all(cipher);

    return out;
}

char* DesEncrypt::doDecrypt(const char* in, const char* key)
{
	BIO *cipher, *b64, *bmem;
	int len, tol, read, status;
	char* out, *ptr;

	len = strlen(in);
	out = new char[len + 1];
	memset(out, 0, len + 1);

	cipher = BIO_new(BIO_f_cipher());
	BIO_set_cipher (cipher, EVP_des_cbc (), (const unsigned char *)key, (const unsigned char *)key, 0);
	b64 = BIO_new(BIO_f_base64());
	BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
	bmem = BIO_new_mem_buf((void*)in, len);

	BIO_push(cipher, b64);
	BIO_push(b64, bmem);

	ptr = out;
	for (tol = 0;; tol += read)
	{
		if ((read = BIO_read(cipher, ptr, len - tol)) <= 0)
		{
			if (BIO_should_retry(cipher))
			{
				read = 0;
				continue;
			}
			break;
		}
//		CM_ERRP("Got %d bytes", read);
		ptr += read;
	}
	out[tol] = '\0';

    status = BIO_get_cipher_status(cipher);
    if (!status)
    {
    	CM_ERR("doDecrypt failure!");
    	out[0] = '\0';
    }

	BIO_free_all(cipher);

	return out;
}





	
	
    
    

  


