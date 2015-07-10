//
//  DesEncrypt.h
//  MLPlayer
//
//  Created by whf on 13-7-8.
//  Copyright (c) 2013 All rights reserved.
//

#ifndef MLPlayer_DesEncrypt_h
#define MLPlayer_DesEncrypt_h



class DesEncrypt{
        
public:
    static char* doEncrypt(const char* in, const char* key);
    static char* doDecrypt(const char* in, const char* key);
};


#endif
