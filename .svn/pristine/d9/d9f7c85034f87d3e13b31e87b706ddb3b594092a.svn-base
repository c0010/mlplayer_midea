//
//  DesEncrypt.m
//  MLPlayer
//
//  Created by sunjj on 13-7-8.
//  Copyright (c) 2013ๅนด w. All rights reserved.
//


#include "stdafx.h"
#include "cmcommon.h"
#include "desencrypt.h"
#import "base64.h"
#import "utf8ncpy.h"

#import <Foundation/Foundation.h>
#import <CommonCrypto/CommonCryptor.h>

@interface Des : NSObject


- (NSString*) doCipher:(NSString*)plainText encryptOrDecrypt:(CCOperation)encryptOrDecrypt UseKey:(NSString *)key;
@end



@implementation Des

- (NSString*) doCipher:(NSString*)plainText encryptOrDecrypt:(CCOperation)encryptOrDecrypt UseKey:(NSString *)key{
    [Base64 initialize];
    
    const void *vplainText;
    size_t plainTextBufferSize;
    
    if (encryptOrDecrypt == kCCDecrypt)
    {
        
        NSData *EncryptData = [Base64 decode:plainText];
        
        
        // NSData *EncryptData = [[NSData alloc] initWithContentsOfURL:url];
        //NSData *EncryptData = [[NSData alloc] initWithContentsOfFile:@"80C19F7026B1328D7908505E746F455997C17F8827A2D701C338FE663426B05111B9D01CAE10570D39B0FF0669B45059B9C4B93431F7F52D79BCDD537EC6491A08BFA738719FA521"];
        // NSString *plainText = @"80C19F7026B1328D7908505E746F455997C17F8827A2D701C338FE663426B05111B9D01CAE10570D39B0FF0669B45059B9C4B93431F7F52D79BCDD537EC6491A08BFA738719FA521";
        // NSData *EncryptData = [plainText dataUsingEncoding:NSUTF8StringEncoding];
        plainTextBufferSize = [EncryptData length];
        vplainText = [EncryptData bytes];
    }
    else
    {
        plainTextBufferSize = [plainText length];
        vplainText = (const void *) [plainText UTF8String];
    }
    
    CCCryptorStatus ccStatus;
    uint8_t *bufferPtr = NULL;
    size_t bufferPtrSize = 0;
    size_t movedBytes = 0;
    // uint8_t iv[kCCBlockSize3DES];
    
    // uint8_t iv[kCCBlockSize3DES] = {0x01, 0x02, 0x03, 0x05, 0x07, 0x0B, 0x0D, 0x11} ;
    
    
    //    NSString *key = @"361A6AA9";
    
    
    const void *vkey = (const void *) [key UTF8String];
    const void *iv = (const void *) [key UTF8String];
    
    // memset((void *) iv, 0x0, (size_t) sizeof(iv));
    // NSLog(@"%@",iv);
    bufferPtrSize = (plainTextBufferSize + kCCBlockSizeDES) & ~(kCCBlockSizeDES - 1);
    bufferPtr = (unsigned char *)malloc((bufferPtrSize * sizeof(uint8_t)));
    memset((void *)bufferPtr, 0x0, bufferPtrSize);
    // memset((void *) iv, 0x0, (size_t) sizeof(iv));
    
    //NSString *key = @"0x01, 0x02, 0x03, 0x05, 0x07, 0x0B, 0x0D, 0x11, 0x12, 0x11, 0x0D, 0x0B, 0x07, 0x02, 0x04, 0x08, 0x01, 0x02, 0x03, 0x05, 0x07, 0x0B, 0x0D, 0x11";
    // const void *vkey = (const void *) [key UTF8String];
    // uint8_t vkey[24] = {0x01, 0x02, 0x03, 0x05, 0x07, 0x0B, 0x0D, 0x11, 0x12, 0x11, 0x0D, 0x0B, 0x07, 0x02, 0x04, 0x08, 0x01, 0x02, 0x03, 0x05, 0x07, 0x0B, 0x0D, 0x11};
    
    
    ccStatus = CCCrypt(encryptOrDecrypt,
                       kCCAlgorithmDES,
                       kCCOptionPKCS7Padding,
                       vkey, //"123456789012345678901234", //key
                       kCCKeySizeDES,
                       iv, //"init Vec", //iv,
                       vplainText, //"Your Name", //plainText,
                       plainTextBufferSize,
                       (void *)bufferPtr,
                       bufferPtrSize,
                       &movedBytes);
    
    
    
    if (ccStatus == kCCSuccess)
    {
        
    }
    else
    {
        free(bufferPtr);
        
        switch (ccStatus) {
            case kCCParamError:
                return @"PARAM ERROR";
                break;
                
            case kCCBufferTooSmall:
                return @"BUFFER TOO SMALL";
                break;
                
            case kCCMemoryFailure:
                return @"MEMORY FAILURE";
                break;
                
            case kCCAlignmentError:
                return @"ALIGNMENT";
                break;
                
            case kCCDecodeError:
                return @"DECODE ERROR";
                break;
                
            case kCCUnimplemented:
                return @"UNIMPLEMENTED";
                break;
                
            default:
                return nil;
                
                break;
        }
        
        
    }
    
    //    else if (ccStatus == kCCParamError) return @"PARAM ERROR";
    //    else if (ccStatus == kCCBufferTooSmall) return @"BUFFER TOO SMALL";
    //    else if (ccStatus == kCCMemoryFailure) return @"MEMORY FAILURE";
    //    else if (ccStatus == kCCAlignmentError) return @"ALIGNMENT";
    //    else if (ccStatus == kCCDecodeError) return @"DECODE ERROR";
    //    else if (ccStatus == kCCUnimplemented) return @"UNIMPLEMENTED";
    
    NSString *result;
    
    if (encryptOrDecrypt == kCCDecrypt)
    {
        result = [[[NSString alloc] initWithData: [NSData dataWithBytes:(const void *)bufferPtr length:(NSUInteger)movedBytes] encoding:NSUTF8StringEncoding] autorelease] ;
        //NSASCIIStringEncoding
    }
    else
    {
        NSData *myData = [NSData dataWithBytes:(const void *)bufferPtr length:(NSUInteger)movedBytes];
        // result = [myData base64Encoding];
        
        result = [[Base64 encode:myData] autorelease];
    }
    
    free(bufferPtr);
    
    return result ;
}

@end

/////////////////////////////////////////////////////////////////////////////////////////////////

//int
//doEncryt(str, null, len);
//if (len > 0) {
//    char* out = new char[len];
//    doEncryt(str, out, len);
//
//}
//
//char* out;
//doEncryt(str, out);
//
//delete out
//void DesEncrypt::doEncrypt(const char* in, char ** out)
//{
//
//
//
//}
//
//void DesEncrypt::doEncrypt(const char* in, char * out, INT& length)

void DesEncrypt::doEncrypt(const char* in, char ** out, const char* key)
{
    
    
    Des* des= [[Des alloc]init];
    
    //    NSString *temp=[NSString stringWithUTF8String:in];
    
    //    NSLog(@"%@ ",temp);
    //
    //
    //    NSString* str1=[des doCipher:[NSString stringWithUTF8String:in] encryptOrDecrypt:kCCEncrypt];
    //
    //    NSLog(@"%@ ",str1);
    //
    //    const char * str= [[des doCipher:[NSString stringWithUTF8String:in] encryptOrDecrypt:kCCEncrypt] UTF8String];
    //
    //    printf("%s",str);
    
    
    const char * str= [[des doCipher:[NSString stringWithUTF8String:in] encryptOrDecrypt:kCCEncrypt UseKey:[NSString stringWithUTF8String:key]] UTF8String];
    
    *out = new char[strlen(str)+1];
    
    strcpy(*out, str);
    
    
    
    //    utf8ncpy(out, str, strlen(in));
    
    [des release];
    
}

void DesEncrypt::doDecrypt(const char* in, char ** out,const char* key)
{
    
    
    Des* des= [[Des alloc]init];
    
    const char * str= [[des doCipher:[NSString stringWithUTF8String:in] encryptOrDecrypt:kCCDecrypt UseKey:[NSString stringWithUTF8String:key]] UTF8String];
    
    if(str == NULL){
        return;
    }
    
    *out = new char[strlen(str)+1];
    
    strcpy(*out, str);
    //    utf8ncpy(out, str, strlen(in));
    
    [des release];
    
}
