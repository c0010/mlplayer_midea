#ifndef ___UTF8NCPY_H___
#define ___UTF8NCPY_H___


char *utf8ncpy(char *dst, const char *src, size_t maxncpy);

#if defined(PLAT_AND)
//java原生是utf-16，自带的转换成cesu-8格式不支持emoji表情等cus4字段
//utf8->utf16
unsigned short* UTF8toUTF16(char* in, size_t* len);

//utf16->utf8
char* UTF16toUTF8(unsigned short* in, size_t* len);
#endif

#endif
